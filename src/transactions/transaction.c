#include "transaction.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <cjson/cJSON.h>

#ifdef _WIN32
    #include <direct.h>
#else
    #include <sys/types.h>
#endif

#include "utils/date_util.h"
#include "utils/string_util.h"
#include "core/console/console.h"
#include "core/console/console_color.h"

static int create_directory(const char* path, mode_t mode) {
#ifdef _WIN32
    return _mkdir(path);
#else
    return mkdir(path, mode);
#endif
}

/**
 * @brief Ensures the "data" directory and current year subdirectory exist, creating them if needed.
 *
 * @author Almighty-Shogun
 */
static void ensure_path_exists() {
    char path[256];

    snprintf(path, 256, "data/%d", date_util_get_current_year());

    struct stat st;

    if (stat("data", &st) == -1) {
        create_directory("data", 0755);
    }

    if (stat(path, &st) == -1) {
        create_directory(path, 0755);
    }
}

/**
 * @brief Constructs a file path for a given year and month within the application's data directory.
 *
 * @param year The year for the path.
 * @param month The month for the path.
 * @return Pointer to the constructed file path string.
 *
 * @author Almighty-Shogun
 */
static const char* get_path(const int year, const char *month) {
    static char path[256];

    snprintf(path, sizeof(path), "data/%d/%s.json", year, month);

    string_util_to_lower(path);

    return path;
}

void transaction_ensure_files_exists() {
    ensure_path_exists();

    const int year = date_util_get_current_year();

    for (int i = 0; i < 12; i++) {
        const char* path = get_path(year, date_util_get_month_name(i + 1));

        FILE* file = fopen(path, "r");

        if (!file) {
            file = fopen(path, "w");

            if (file) {
                fputs("[]", file);
            } else {
                console_write_line(CONSOLE_COLOR_RED "Failed to create the " CONSOLE_COLOR_CYAN "%s" CONSOLE_COLOR_RED " file.", path);
            }
        }

        if (file) {
            fclose(file);
        }
    }
}

cJSON* transaction_get_file(const int year, const char* month) {
    const char* path = get_path(year, month);

    FILE* file = fopen(path, "r");

    if (!file) {
        return cJSON_CreateArray();
    }

    fseek(file, 0, SEEK_END);
    const long length = ftell(file);
    rewind(file);

    char* data = malloc(length + 1);

    if (!data) {
        fclose(file);
        return cJSON_CreateArray();
    }

    fread(data, 1, length, file);
    data[length] = '\0';
    fclose(file);

    cJSON* json = cJSON_Parse(data);
    free(data);

    if (!json) {
        json = cJSON_CreateArray();
    }

    return json;
}

void transaction_save_file(const int year, const char* month, const char* json) {
    const char* path = get_path(year, month);

    FILE* file = fopen(path, "w");

    if (!file) {
        console_write_line(CONSOLE_COLOR_RED "Failed to write to the " CONSOLE_COLOR_CYAN "%s" CONSOLE_COLOR_RED " file.", path);
        return;
    }

    fputs(json, file);
    fclose(file);
}

bool transaction_is_valid_type(char* type) {
    const char* types[] = {
        "income", "expense", "saving", "repayment"
    };

    string_util_to_lower(type);

    constexpr size_t total_types = sizeof(types) / sizeof(types[0]);

    for (size_t i = 0; i < total_types; i++) {
        if (string_util_is_equal(type, types[i])) {
            return true;
        }
    }

    return false;
}

cJSON* transaction_to_json(const transaction_t transaction) {
    cJSON* json = cJSON_CreateObject();

    if (!json) {
        return nullptr;
    }

    cJSON_AddNumberToObject(json, "id", transaction.id);
    cJSON_AddNumberToObject(json, "date", transaction.date);
    cJSON_AddNumberToObject(json, "amount", transaction.amount);
    cJSON_AddStringToObject(json, "type", transaction.type);
    cJSON_AddStringToObject(json, "category", transaction.category);
    cJSON_AddStringToObject(json, "description", transaction.description);

    return json;
}

transaction_t* transaction_from_json(const cJSON* json) {
    transaction_t* transaction = calloc(1, sizeof(transaction_t));

    if (!cJSON_IsObject(json) || !transaction) {
        return nullptr;
    }

    const cJSON* id = cJSON_GetObjectItem(json, "id");
    const cJSON* type = cJSON_GetObjectItem(json, "type");
    const cJSON* date = cJSON_GetObjectItem(json, "date");
    const cJSON* amount = cJSON_GetObjectItem(json, "amount");
    const cJSON* category = cJSON_GetObjectItem(json, "category");
    const cJSON* description = cJSON_GetObjectItem(json, "description");

    if (cJSON_IsNumber(id)) {
        transaction->id = id->valueint;
    }

    if (cJSON_IsString(type)) {
        string_util_copy_string(transaction->type, type->valuestring, sizeof(transaction->type));
    }

    if (cJSON_IsString(category)) {
        string_util_copy_string(transaction->category, category->valuestring, sizeof(transaction->category));
    }

    if (cJSON_IsNumber(amount)) {
        transaction->amount = (double)amount->valuedouble;
    }

    if (cJSON_IsString(description)) {
        string_util_copy_string(transaction->description, description->valuestring, sizeof(transaction->description));
    }

    if (cJSON_IsNumber(date)) {
        transaction->date = date->valueint;
    }

    return transaction;
}

int transaction_get_last_id(const cJSON* json) {
    if (!json) {
        json = cJSON_CreateArray();
    }

    if (!cJSON_IsArray(json)) {
        return -1;
    }

    const int size = cJSON_GetArraySize(json);

    if (size <= 0) {
        return 0;
    }

    const cJSON* last_transaction = cJSON_GetArrayItem(json, size - 1);

    if (!cJSON_IsObject(last_transaction)) {
        return -1;
    }

    const cJSON* id = cJSON_GetObjectItem(last_transaction, "id");

    if (!cJSON_IsNumber(id)) {
        return -1;
    }

    return id->valueint;
}

double transaction_get_total_amount(const cJSON* json, const char* type) {
    cJSON* item;
    double total = 0;

    cJSON_ArrayForEach(item, json) {
        transaction_t* transaction = transaction_from_json(item);

        if (string_util_is_equal(transaction->type, type)) {
            total += transaction->amount;
        }

        free(transaction);
    }

    return total;
}

int transaction_find_index(const cJSON* json, const int id) {
    if (!cJSON_IsArray(json)) {
        return -1;
    }

    cJSON* item;
    int index = 0;

    cJSON_ArrayForEach(item, json) {
        const cJSON* item_id = cJSON_GetObjectItem(item, "id");

        if (cJSON_IsNumber(item_id) && item_id->valueint == id) {
            return index;
        }

        index++;
    }

    return -1;
}