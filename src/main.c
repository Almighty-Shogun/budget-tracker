#include "menu/menu.h"
#include "core/console/console.h"
#include "transactions/transaction.h"

int main() {
    console_set_title("Budget Tracker");
    transaction_ensure_files_exists();

    menu_handle();

    console_clear();

    return 0;
}
