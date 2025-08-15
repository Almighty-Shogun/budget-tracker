#include "menu.h"

#include <string.h>
#include <stdlib.h>

#include "input/input.h"
#include "utils/string_util.h"
#include "core/console/console.h"
#include "core/console/console_color.h"
#include "transactions/transaction_add.h"
#include "transactions/transaction_edit.h"
#include "transactions/transaction_list.h"
#include "transactions/transaction_balance.h"
#include "transactions/transaction_delete.h"

enum menu_option {
    ADD_TRANSACTION = 1,
    EDIT_TRANSACTION = 2,
    DELETE_TRANSACTION = 3,
    LIST_TRANSACTIONS = 4,
    SHOW_BALANCE = 5,
    EXIT_APPLICATION = 9
};

void menu_show_header(const char* title) {
    const size_t length = strlen(title) + 4;

    char* hashes = string_util_repeat_character('#', length);

    console_write_line(CONSOLE_COLOR_GREEN "%s", hashes);
    console_write_line(CONSOLE_COLOR_GREEN "# %s #", title);
    console_write_line(CONSOLE_COLOR_GREEN "%s", hashes);

    free(hashes);
}

void menu_show_option(const int id, const char* description) {
    console_write_line(CONSOLE_COLOR_CYAN "%d. " CONSOLE_COLOR_RESET "%s", id, description);
}

static void show_menu() {
    menu_show_header("CLI Budget Tracker");
    console_write_line(nullptr);

    menu_show_option(ADD_TRANSACTION, "Add a transaction");
    menu_show_option(EDIT_TRANSACTION, "Edit a transaction");
    menu_show_option(DELETE_TRANSACTION, "Delete a transaction");
    menu_show_option(LIST_TRANSACTIONS, "List transactions");
    menu_show_option(SHOW_BALANCE, "Show balance");
    menu_show_option(EXIT_APPLICATION, "Exit application");
    console_write_line(nullptr);
}

void menu_handle() {
    int choice;

    do {
        console_clear();
        show_menu();

        choice = input_ask_number("Enter your choice:", 1, 9, false);

        switch (choice) {
            case ADD_TRANSACTION: {
                transaction_add_menu();
                break;
            }
            case EDIT_TRANSACTION: {
                transaction_edit_menu();
                break;
            }
            case DELETE_TRANSACTION: {
                transaction_delete_menu();
                break;
            }
            case LIST_TRANSACTIONS: {
                transaction_list_menu();
                break;
            }
            case SHOW_BALANCE: {
                transaction_balance_menu();
                break;
            }
            case EXIT_APPLICATION: break;
            default: {
                console_write_line("Invalid option.");

                console_write_line(nullptr);
                console_read_key("Press any key to return to the menu...");
                break;
            }
        }
    } while (choice != 9);
}