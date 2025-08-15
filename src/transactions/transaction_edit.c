#include "transaction_edit.h"

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
    EDIT_TRANSACTION = 1,
    EDIT_OLDER_TRANSACTION = 2,
    BACK_TO_MAIN_MENU = 9
};

/**
 * @brief Displays the "Edit transaction" menu with options for user actions.
 *
 * @author Almighty-Shogun
 */
static void show_menu() {
    menu_show_header("Edit a transaction");
    console_write_line(nullptr);

    menu_show_option(HELP_MENU, "Help menu");
    console_write_line(nullptr);

    menu_show_option(EDIT_TRANSACTION, "Edit a transaction");
    menu_show_option(EDIT_OLDER_TRANSACTION, "Edit an older transaction");
    menu_show_option(BACK_TO_MAIN_MENU, "Go back to the main menu");
    console_write_line(nullptr);
}

/**
 * @brief Edits an existing transaction for a given year and month.
 *
 * @param year Year of transaction.
 * @param month Month name.
 *
 * @author Almighty-Shogun
 */
static void edit_transaction(int year, const char* month) {
    if (year <= 0) {
        console_write_line(CONSOLE_COLOR_YELLOW "Invalid year. Using current year.");
        year = date_util_get_current_year();
    }

    if (!month) {
        console_write_line(CONSOLE_COLOR_YELLOW "Invalid month. Using current month.");
        month = date_util_get_current_month_name();
    }

    console_write_line("Editing a transaction of " CONSOLE_COLOR_CYAN "%s %d", month, year);
    console_write_line(nullptr);

    cJSON* json = transaction_get_file(year, month);

    const int transaction_id = input_ask_number("What is the ID of the transaction?", 1, 100, true);

    const int transaction_index = transaction_find_index(json, transaction_id);

    if (transaction_index == -1) {
        console_write_line(CONSOLE_COLOR_RED "No transaction with the given ID was found.");
        return;
    }

    cJSON* transaction_json = cJSON_GetArrayItem(json, transaction_index);

    if (!transaction_json) {
        console_write_line(CONSOLE_COLOR_RED "Failed to get the transaction from the JSON array.");
        return;
    }

    transaction_t* transaction = transaction_from_json(transaction_json);

    if (!transaction) {
        console_write_line(CONSOLE_COLOR_RED "Failed to convert the transaction.");
        return;
    }

    if (input_ask_yes_or_no("Do you want to edit the date?", true)) {
        transaction->date = input_ask_date(year, month, true);
    }

    if (input_ask_yes_or_no("Do you want to edit the type?", true)) {
        char* type = input_ask_type(true);
        string_util_copy_string(transaction->type, type, sizeof(transaction->type));
        free(type);
    }

    if (input_ask_yes_or_no("Do you want to edit the category?", true)) {
        char* category = input_ask_category(true);
        string_util_copy_string(transaction->category, category, sizeof(transaction->category));
        free(category);
    }

    if (input_ask_yes_or_no("Do you want to edit the amount?", true)) {
        transaction->amount = input_ask_amount(true);
    }

    if (input_ask_yes_or_no("Do you want to edit the description?", true)) {
        char* description = input_ask_description(true);
        string_util_copy_string(transaction->description, description, sizeof(transaction->description));
        free(description);
    }

    cJSON* new_transaction_json = transaction_to_json(*transaction);

    if (!new_transaction_json) {
        console_write_line(CONSOLE_COLOR_RED "Failed to convert the new transaction.");
        return;
    }

    cJSON_ReplaceItemInArray(json, transaction_index, cJSON_Duplicate(new_transaction_json, 1));

    char* rendered = cJSON_Print(json);

    transaction_save_file(year, month, rendered);

    free(transaction);
    cJSON_Delete(json);
    cJSON_free(rendered);

    console_write_line(nullptr);
    console_write_line(CONSOLE_COLOR_GREEN "Transaction edited successfully.");
}

/**
 * @brief Displays the help menu for the "Edit a transaction" section.
 *
 * @param year The current year in context.
 * @param month The current month in context.
 *
 * @author Almighty-Shogun
 */
static void handle_help_option(const int year, const char* month) {
    menu_show_header("Edit a transaction - Help menu");
    console_write_line(nullptr);

    menu_show_option(EDIT_TRANSACTION, "Edit a transaction");
    console_write_line("Edits a transaction of " CONSOLE_COLOR_CYAN "%s %d", month, year);
    console_write_line(nullptr);

    menu_show_option(EDIT_OLDER_TRANSACTION, "Edit an older transaction");
    console_write_line("Edits an older transaction.");
    console_write_line("You'll be asked to enter the year and month.");
    console_write_line(nullptr);

    menu_show_option(BACK_TO_MAIN_MENU, "Go back to the main menu");
    console_write_line("Returns to the main menu.");
}

/**
 * @brief Handles the "Edit a transaction" option.
 *
 * @param year The year for the transaction.
 * @param month The month name for the transaction.
 *
 * @author Almighty-Shogun
 */
static void handle_edit_transaction_option(const int year, const char* month) {
    edit_transaction(year, month);
}

/**
 * @brief Handles the "Edit an older transaction" option.
 *
 * @author Almighty-Shogun
 */
static void handle_edit_older_transaction_option() {
    const int year = input_ask_year(true);
    char* month = input_ask_month(true);

    console_clear();
    edit_transaction(year, month);

    free(month);
}

void transaction_edit_menu() {
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
            case EDIT_TRANSACTION: {
                handle_edit_transaction_option(current_year, current_month);
                break;
            }
            case EDIT_OLDER_TRANSACTION: {
                handle_edit_older_transaction_option();
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