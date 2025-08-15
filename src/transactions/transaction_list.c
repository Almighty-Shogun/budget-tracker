#include "transaction_list.h"

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
    LIST_TRANSACTIONS = 1,
    LIST_OLDER_TRANSACTIONS = 2,
    BACK_TO_MAIN_MENU = 9
};

/**
 * @brief Displays the "List transactions" menu with options for user actions.
 *
 * @author Almighty-Shogun
 */
static void show_menu() {
    menu_show_header("List transactions");
    console_write_line(nullptr);

    menu_show_option(HELP_MENU, "Help menu");
    console_write_line(nullptr);

    menu_show_option(LIST_TRANSACTIONS, "View current transactions");
    menu_show_option(LIST_OLDER_TRANSACTIONS, "View older transactions");
    menu_show_option(BACK_TO_MAIN_MENU, "Go back to the main menu");
    console_write_line(nullptr);
}

/**
 * @brief Lists transactions for a given year and month.
 *
 * @param year Year of transactions.
 * @param month Month name.
 *
 * @author Almighty-Shogun
 */
static void list_transactions(int year, const char* month) {
    if (year <= 0) {
        console_write_line(CONSOLE_COLOR_YELLOW "Invalid year. Using current year.");
        year = date_util_get_current_year();
    }

    if (!month) {
        console_write_line(CONSOLE_COLOR_YELLOW "Invalid month. Using current month.");
        month = date_util_get_current_month_name();
    }

    console_write_line("Transactions of " CONSOLE_COLOR_CYAN "%s %d", month, year);
    console_write_line(nullptr);

    cJSON* json = transaction_get_file(year, month);

    if (cJSON_GetArraySize(json) == 0) {
        console_write_line(CONSOLE_COLOR_YELLOW "No transactions found.");

        cJSON_Delete(json);
        return;
    }

    char* dashes = string_util_repeat_character('-', 104);

    console_write_line(dashes);
    console_write_line("| %3s | %-4s | %-10s | %-20s | %8s | %-40s |", "ID", "Date", "Type", "Category", "Amount", "Description");
    console_write_line(dashes);

    cJSON* item;
    cJSON_ArrayForEach(item, json) {
        transaction_t* transaction = transaction_from_json(item);

        console_write_line("| %3d | %-4d | %-10s | %-20s | %8.2f | %-40s |",
            transaction->id, transaction->date, transaction->type,
            transaction->category, transaction->amount, transaction->description);

        free(transaction);
    }

    console_write_line(dashes);

    free(dashes);
    cJSON_Delete(json);
}

/**
 * @brief Displays the help menu for the "Adding a transaction" section.
 *
 * @param year The current year in context.
 * @param month The current month in context.
 *
 * @author Almighty-Shogun
 */
static void handle_help_option(const int year, const char* month)  {
    menu_show_header("List transactions - Help menu");
    console_write_line(nullptr);

    menu_show_option(LIST_TRANSACTIONS, "View current transactions");
    console_write_line("Shows all transactions of " CONSOLE_COLOR_CYAN "%s %d", month, year);
    console_write_line(nullptr);

    menu_show_option(LIST_OLDER_TRANSACTIONS, "View older transactions");
    console_write_line("Shows transactions from previous year or month.");
    console_write_line("You'll be asked to enter the year and month.");
    console_write_line(nullptr);

    menu_show_option(BACK_TO_MAIN_MENU, "Go back to the main menu");
    console_write_line("Returns to the main menu.");
}

/**
 * @brief Handles the "List transactions" option.
 *
 * @param year The year for the transactions.
 * @param month The month name for the transactions.
 *
 * @author Almighty-Shogun
 */
static void handle_list_transactions_option(const int year, const char* month) {
    list_transactions(year, month);
}

/**
 * @brief Handles the "List older transactions" option.
 *
 * @author Almighty-Shogun
 */
static void handle_list_older_transactions_option() {
    const int year = input_ask_year(false);
    char* month = input_ask_month(false);

    console_clear();
    list_transactions(year, month);

    free(month);
}

void transaction_list_menu() {
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
            case LIST_TRANSACTIONS: {
                handle_list_transactions_option(current_year, current_month);
                break;
            }
            case LIST_OLDER_TRANSACTIONS: {
                handle_list_older_transactions_option();
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