#include "transaction_add.h"

#include <stdlib.h>
#include <cjson/cJSON.h>

#include "menu/menu.h"
#include "transaction.h"
#include "input/input.h"
#include "utils/date_util.h"
#include "utils/string_util.h"
#include "core/console/console.h"
#include "core/console/console_color.h"

enum menu_option {
    HELP_MENU = 0,
    ADD_TRANSACTION = 1,
    ADD_OLDER_TRANSACTION = 2,
    BACK_TO_MAIN_MENU = 9
};

/**
 * @brief Displays the "Add transaction" menu with options for user actions.
 *
 * @author Almighty-Shogun
 */
static void show_menu() {
    menu_show_header("Adding a transaction");
    console_write_line(nullptr);

    menu_show_option(HELP_MENU, "Help menu");
    console_write_line(nullptr);

    menu_show_option(ADD_TRANSACTION, "Add a transaction");
    menu_show_option(ADD_OLDER_TRANSACTION, "Add an older transaction");
    menu_show_option(BACK_TO_MAIN_MENU, "Go back to the main menu");
    console_write_line(nullptr);
}

/**
 * @brief Adds a new transaction for a given year and month.
 *
 * @param year Year of transaction.
 * @param month Month name.
 *
 * @author Almighty-Shogun
 */
static void add_transaction(int year, const char* month) {
    if (year <= 0) {
        console_write_line(CONSOLE_COLOR_YELLOW "Invalid year. Using current year.");
        year = date_util_get_current_year();
    }

    if (!month) {
        console_write_line(CONSOLE_COLOR_YELLOW "Invalid month. Using current month.");
        month = date_util_get_current_month_name();
    }

    console_write_line("Adding transaction to " CONSOLE_COLOR_CYAN "%s %d", month, year);
    console_write_line(nullptr);

    transaction_t transaction = {};

    cJSON* json = transaction_get_file(year, month);

    transaction.id = transaction_get_last_id(json) + 1;

    transaction.date = input_ask_date(year, month, true);

    char* type = input_ask_type(true);
    string_util_copy_string(transaction.type, type, sizeof(transaction.type));
    free(type);

    char* category = input_ask_category(true);
    string_util_copy_string(transaction.category, category, sizeof(transaction.category));
    free(category);

    transaction.amount = input_ask_amount(true);

    char* description = input_ask_description(true);
    string_util_copy_string(transaction.description, description, sizeof(transaction.description));
    free(description);

    cJSON* json_transaction = transaction_to_json(transaction);

    if (!json_transaction) {
        console_write_line(CONSOLE_COLOR_RED "Failed to convert the transaction to JSON.");

        cJSON_Delete(json);
        return;
    }

    const bool is_added = cJSON_AddItemToArray(json, json_transaction);

    if (!is_added) {
        console_write_line(CONSOLE_COLOR_RED "Failed to add the transaction to the JSON array.");

        cJSON_Delete(json);
        return;
    }

    char* rendered = cJSON_Print(json);

    if (!rendered) {
        console_write_line(CONSOLE_COLOR_RED "Failed to render the transaction to JSON.");

        cJSON_Delete(json);
        return;
    }

    transaction_save_file(year, month, rendered);

    cJSON_Delete(json);
    cJSON_free(rendered);

    console_write_line(nullptr);
    console_write_line(CONSOLE_COLOR_GREEN "Transaction added successfully.");
}

/**
 * @brief Displays the help menu for the "Adding a transaction" section.
 *
 * @param year The current year in context.
 * @param month The current month in context.
 *
 * @author Almighty-Shogun
 */
static void handle_help_option(const int year, const char* month) {
    menu_show_header("Adding a transaction - Help menu");
    console_write_line(nullptr);

    menu_show_option(ADD_TRANSACTION, "Add a transaction");
    console_write_line("Adds a transaction to " CONSOLE_COLOR_CYAN "%s %d", month, year);
    console_write_line(nullptr);

    menu_show_option(ADD_OLDER_TRANSACTION, "Add an older transaction");
    console_write_line("Adds a transaction to an earlier year and/or month.");
    console_write_line("You'll be asked to enter the year and month.");
    console_write_line(nullptr);

    menu_show_option(BACK_TO_MAIN_MENU, "Go back to the main menu");
    console_write_line("Returns you to the main menu.");
}

/**
 * @brief Handles the "Add a transaction" option.
 *
 * @param year The year for the transactions.
 * @param month The month name for the transactions.
 *
 * @author Almighty-Shogun
 */
static void handle_add_transaction_option(const int year, const char* month) {
    const bool add_multiple = input_ask_yes_or_no("Do you want to add multiple transactions?", true);

    if (add_multiple) {
        const int amount = input_ask_number("How many transaction do you want to add?", 1, 10, true);

        for (int i = 0; i < amount; i++) {
            console_clear();

            add_transaction(year, month);

            console_read_key("Press any key to add the next transaction...");
        }
    } else {
        console_clear();
        add_transaction(year, month);
    }
}

/**
 * @brief Handles the "Adding an older transaction" option.
 *
 * @author Almighty-Shogun
 */
static void handle_add_older_transaction_option() {
    int year = 0;
    char* month = nullptr;

    const bool add_multiple = input_ask_yes_or_no("Do you want to add multiple transactions?", true);

    if (add_multiple) {
        const int amount = input_ask_number("How many transaction do you want to add?", 1, 10, true);
        const bool same_month = input_ask_yes_or_no("Do you want to add all transactions to the same month and year?", true);

        if (same_month) {
            year = input_ask_year(true);
            month = input_ask_month(true);
        }

        for (int i = 0; i < amount; i++) {
            console_clear();

            if (!same_month) {
                year = input_ask_year(true);
                month = input_ask_month(true);
            }

            add_transaction(year, month);

            if (!same_month) {
                free(month);
                month = nullptr;
            }

            console_read_key("Press any key to add the next transaction...");
        }
    } else {
        year = input_ask_year(true);
        month = input_ask_month(true);

        console_clear();
        add_transaction(year, month);
    }

    if (month) {
        free(month);
    }
}

void transaction_add_menu() {
    int choice;

    const int current_year = date_util_get_current_year();
    const char* current_month = date_util_get_current_month_name();

    do {
        console_clear();
        show_menu();

        choice = input_ask_number("Enter your choice:", HELP_MENU, BACK_TO_MAIN_MENU, false);

        console_clear();

        switch (choice) {
            case HELP_MENU: {
                handle_help_option(current_year, current_month);
                break;
            }
            case ADD_TRANSACTION: {
                handle_add_transaction_option(current_year, current_month);
                break;
            }
            case ADD_OLDER_TRANSACTION: {
                handle_add_older_transaction_option();
                break;
            }
            case BACK_TO_MAIN_MENU: break;
            default: {
                console_write_line("Invalid option");
                break;
            }
        }

        if (choice != BACK_TO_MAIN_MENU) {
            console_write_line(nullptr);
            console_read_key("Press any key to return to the menu...");
        }
    } while (choice != BACK_TO_MAIN_MENU);
}