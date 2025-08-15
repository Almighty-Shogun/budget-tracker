#include "string_util.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void string_util_to_lower(char* string) {
    if (!string) {
        return;
    }

    for (; *string; ++string) {
        const unsigned char current_char = (unsigned char)*string;
        *string = (char)tolower(current_char);
    }
}

void string_util_trim(char* string) {
    if (!string) {
        return;
    }

    char* start = string;

    while (isspace(*start)) {
        start++;
    }

    char* end = start + strlen(start) - 1;

    while (end > start && isspace(*end)) {
        *end-- = '\0';
    }

    if (start != string) {
        memmove(string, start, strlen(start) + 1);
    }
}

void string_util_trim_new_line(char* string) {
    if (!string) {
        return;
    }

    size_t length = strlen(string);

    while (length > 0 && (string[length - 1] == '\n' || string[length - 1] == '\r')) {
        string[length - 1] = '\0';
        length--;
    }
}

char* string_util_repeat_character(const char character, const size_t amount) {
    char* result = malloc(amount + 1);

    if (!result) {
        return nullptr;
    }

    for (size_t i = 0; i < amount; i++) {
        result[i] = character;
    }

    result[amount] = '\0';

    return result;
}

void string_util_copy_string(char* destination, const char* source, const size_t size) {
    if (!destination || !source || size == 0) {
        return;
    }

    strncpy(destination, source, size - 1);
    destination[size - 1] = '\0';
}

bool string_util_is_equal(const char* string_one, const char* string_two) {
    if (!string_one || !string_two) {
        return false;
    }

    if (string_one == string_two) {
        return true;
    }

    return strcmp(string_one, string_two) == 0;
}

void string_util_uc_first(char* string) {
    if (!string) {
        return;
    }

    char* p = string;

    while (*p && isspace((unsigned char)*p)) {
        p++;
    }

    if (*p) {
        *p = (char)toupper((unsigned char)*p);
    }
}