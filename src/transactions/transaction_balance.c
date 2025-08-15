#include "transaction_balance.h"

#include <stdlib.h>
#include <string.h>
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
    VIEW_BALANCE = 1,
    VIEW_OLDER_BALANCE = 2,
    VIEW_YEARLY_BALANCE = 3,
    VIEW_OLDER_YEARLY_BALANCE = 4,
    BACK_TO_MAIN_MENU = 9
};

/**
 * @brief Displays the "Show balance" menu with options for user actions.
 *
 * @author Almighty-Shogun
 */
static void show_menu() {
    menu_show_header("Show balance");
    console_write_line(nullptr);

    menu_show_option(HELP_MENU, "Help menu");
    console_write_line(nullptr);

    menu_show_option(VIEW_BALANCE, "View balance");
    menu_show_option(VIEW_OLDER_BALANCE, "View an older balance");
    menu_show_option(VIEW_YEARLY_BALANCE, "View the yearly balance");
    menu_show_option(VIEW_OLDER_YEARLY_BALANCE, "View an older yearly balance");
    menu_show_option(BACK_TO_MAIN_MENU, "Go back to the main menu");
    console_write_line(nullptr);
}

/**
 * @brief Shows monthly balance for a given year and month.
 *
 * @param year Year for balance.
 * @param month Month name.
 *
 * @author Almighty-Shogun
 */
static void show_monthly_balance(int year, const char* month) {
    if (year <= 0) {
        console_write_line(CONSOLE_COLOR_YELLOW "Invalid year. Using current year.");
        year = date_util_get_current_year();
    }

    if (!month) {
        console_write_line(CONSOLE_COLOR_YELLOW "Invalid month. Using current month.");
        month = date_util_get_current_month_name();
    }

    console_write_line("Balance of " CONSOLE_COLOR_CYAN "%s %d", month, year);
    console_write_line(nullptr);

    cJSON* json = transaction_get_file(year, month);

    const double income = transaction_get_total_amount(json, "income");
    const double expense = transaction_get_total_amount(json, "expense");
    const double saving = transaction_get_total_amount(json, "saving");
    const double repayment = transaction_get_total_amount(json, "repayment");

    const double balance = income - expense - saving - repayment;

    char* dashes = string_util_repeat_character('-', 28);

    console_write_line(dashes);
    console_write_line("| %-11s | %10s |", "Type", "Amount");
    console_write_line(dashes);
    console_write_line("| %-11s | %10.2f |", "Income", income);
    console_write_line("| %-11s | %10.2f |", "Expense", expense);
    console_write_line("| %-11s | %10.2f |", "Saving", saving);
    console_write_line("| %-11s | %10.2f |", "Repayment", repayment);
    console_write_line(dashes);
    console_write_line("| %-11s | %10.2f |", "Balance", balance);
    console_write_line(dashes);

    free(dashes);
    cJSON_Delete(json);
}

/**
 * @brief Shows yearly balance overview.
 *
 * @param year Year for balance.
 *
 * @author Almighty-Shogun
 */
static void show_yearly_balance(int year) {
    if (year <= 0) {
        console_write_line(CONSOLE_COLOR_YELLOW "Invalid year. Using current year.");
        year = date_util_get_current_year();
    }

    console_write_line("Balance overview of " CONSOLE_COLOR_CYAN "%d", year);
    console_write_line(nullptr);

    char* dashes = string_util_repeat_character('-', 79);

    console_write_line(dashes);
    console_write_line("| %-10s | %10s | %10s | %10s | %10s | %10s |", "Month", "Income", "Expense", "Saving", "Repayment", "Balance");
    console_write_line(dashes);

    double total_income = 0, total_expense = 0, total_saving = 0, total_repayment = 0;

    for (int i = 0; i < 12; i++) {
        char* month = strdup(months[i]);

        string_util_uc_first(month);

        cJSON* json = transaction_get_file(year, month);

        const double income = transaction_get_total_amount(json, "income");
        const double expense = transaction_get_total_amount(json, "expense");
        const double saving = transaction_get_total_amount(json, "saving");
        const double repayment = transaction_get_total_amount(json, "repayment");

        const double balance = income - expense - saving - repayment;

        total_income += income;
        total_expense += expense;
        total_saving += saving;
        total_repayment += repayment;

        console_write_line("| %-10s | %10.2f | %10.2f | %10.2f | %10.2f | %10.2f |", month, income, expense, saving, repayment, balance);

        free(month);
        cJSON_Delete(json);
    }

    const double balance = total_income - total_expense - total_saving - total_repayment;

    console_write_line(dashes);
    console_write_line("| %-10s | %10.2f | %10.2f | %10.2f | %10.2f | %10.2f |", "Total", total_income, total_expense, total_saving, total_repayment, balance);
    console_write_line(dashes);

    free(dashes);
}

/**
 * @brief Displays the help menu for the "Show balance" section.
 *
 * @param year The current year in context.
 * @param month The current month in context.
 *
 * @author Almighty-Shogun
 */
static void handle_help_option(const int year, const char* month) {
    menu_show_header("Show balance - Help menu");
    console_write_line(nullptr);

    menu_show_option(VIEW_BALANCE, "View current balance");
    console_write_line("Shows the current balance for " CONSOLE_COLOR_CYAN "%s %d", month, year);
    console_write_line(nullptr);

    menu_show_option(VIEW_OLDER_BALANCE, "View an older balance");
    console_write_line("Allows you to select a specific year and month to view the balance for.");
    console_write_line("You'll be asked to enter the year and month.");
    console_write_line(nullptr);

    menu_show_option(VIEW_YEARLY_BALANCE, "View yearly balance");
    console_write_line("Shows the overall balance for the current year.");
    console_write_line(nullptr);

    menu_show_option(VIEW_OLDER_YEARLY_BALANCE, "View an older yearly balance");
    console_write_line("Allows you to view the overall balance for a past year.");
    console_write_line("You'll be asked to enter the year.");
    console_write_line(nullptr);

    menu_show_option(BACK_TO_MAIN_MENU, "Go back to the main menu");
    console_write_line("Returns you to the main menu.");
}

/**
 * @brief Handles the "View balance" option.
 *
 * @param year The current year in context.
 * @param month The current month in context.
 *
 * @author Almighty-Shogun
 */
static void handle_show_balance_option(const int year, const char* month) {
    show_monthly_balance(year, month);
}

/**
 * @brief Handles the "View an older balance" option.
 *
 * @author Almighty-Shogun
 */
static void handle_show_older_balance_option() {
    const int year = input_ask_year(false);
    char* month = input_ask_month(false);

    console_clear();
    show_monthly_balance(year, month);

    free(month);
}

/**
 * @brief Handles the "View the yearly balance" option.
 *
 * @param year The current year in context.
 *
 * @author Almighty-Shogun
 */
static void handle_show_yearly_balance_option(const int year) {
    show_yearly_balance(year);
}

/**
 * @brief Handles the "View a older yearly balance" option.
 *
 * @author Almighty-Shogun
 */
static void handle_show_older_yearly_balance_option() {
    const int year = input_ask_year(false);

    console_clear();
    show_yearly_balance(year);
}

void transaction_balance_menu() {
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
            case VIEW_BALANCE: {
                handle_show_balance_option(current_year, current_month);
                break;
            }
            case VIEW_OLDER_BALANCE: {
                handle_show_older_balance_option();
                break;
            }
            case VIEW_YEARLY_BALANCE: {
                handle_show_yearly_balance_option(current_year);
                break;
            }
            case VIEW_OLDER_YEARLY_BALANCE: {
                handle_show_older_yearly_balance_option();
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
    } while (choice != 9);
}