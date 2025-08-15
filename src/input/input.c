#include "input.h"

#include <stdio.h>
#include <stdlib.h>

#include "utils/date_util.h"
#include "utils/type_parser.h"
#include "core/console/console.h"
#include "transactions/transaction.h"
#include "core/console/console_color.h"
#include "validation/date_validation.h"

int input_ask_number(const char* question, const int min, const int max, const bool log_answer) {
    int number;
    char* input = nullptr;
    bool is_valid = false;

    do {
        if (input) {
            free(input);
        }

        input = console_ask_question(question);
        is_valid = type_parser_try_parse_integer(input, &number);

        if (!is_valid || number < min || number > max) {
            console_write(CONSOLE_COLOR_RED "Invalid number format or value. Please use a number between ");
            console_write_line(CONSOLE_COLOR_CYAN "%d" CONSOLE_COLOR_WHITE " and " CONSOLE_COLOR_CYAN "%d", min, max);
        }
    } while (!is_valid || number < min || number > max);

    free(input);

    if (log_answer) {
        console_clear_last_line();
        console_write_line("%s " CONSOLE_COLOR_CYAN "%d", question, number);
    }

    return number;
}

int input_ask_year(const bool log_answer) {
    int year;
    char* input = nullptr;
    bool is_valid = false;

    const int current_year = date_util_get_current_year();

    do {
        if (input) {
            free(input);
        }

        input = console_ask_question("What is the year of the transaction? (2024, 2025)");
        is_valid = type_parser_try_parse_integer(input, &year) && date_validation_is_valid_year(year);

        if (!is_valid || year < 1900 || year > current_year) {
            console_write(CONSOLE_COLOR_RED "Invalid year value. Please use a year between ");
            console_write_line(CONSOLE_COLOR_CYAN "1900" CONSOLE_COLOR_WHITE " and " CONSOLE_COLOR_CYAN "%d", current_year);
        }
    } while (!is_valid);

    free(input);

    if (log_answer) {
        console_clear_last_line();
        console_write_line("What is the year of the transaction? " CONSOLE_COLOR_CYAN "%d", year);
    }

    return year;
}

char* input_ask_month(const bool log_answer) {
    char* input = nullptr;
    bool is_valid = false;

    do {
        if (input) {
            free(input);
        }

        input = console_ask_question("What is the month of the transaction? (January, February)");
        is_valid = date_validation_is_valid_month(input);

        if (!is_valid) {
            console_write_line(CONSOLE_COLOR_RED "Invalid month value.");
        }
    } while (!is_valid);

    if (log_answer) {
        console_clear_last_line();
        console_write_line("What is the month of the transaction? " CONSOLE_COLOR_CYAN "%s", input);
    }

    return input;
}

int input_ask_date(const int year, const char* month, const bool log_answer) {
    int day;
    char* input = nullptr;
    bool is_valid = false;

    char questionString[128];
    snprintf(questionString, 128, "When was the transaction done? (1-31 %s %d):", month, year);

    do {
        if (input) {
            free(input);
        }

        input = console_ask_question(questionString);
        is_valid = type_parser_try_parse_integer(input, &day);

        if (is_valid) {
            is_valid = date_validation_is_valid_date(day, month, year);
        }

        if (!is_valid || day < 1 || day > 31) {
            console_write(CONSOLE_COLOR_RED "Invalid date format or value. Please use a number between ");
            console_write_line(CONSOLE_COLOR_CYAN "1" CONSOLE_COLOR_WHITE " and " CONSOLE_COLOR_CYAN "31");
        }
    } while (!is_valid);

    free(input);

    if (log_answer) {
        console_clear_last_line();
        console_write_line("When was the transaction done? " CONSOLE_COLOR_CYAN "%d %s %d", day, month, year);
    }

    return day;
}

char* input_ask_type(const bool log_answer) {
    char* input = nullptr;
    bool is_valid = false;

    do {
        if (input) {
            free(input);
        }

        input = console_ask_question("What is the type of the transaction? (income/expense/savings/repayment)");
        is_valid = transaction_is_valid_type(input);

        if (!is_valid) {
            console_write(CONSOLE_COLOR_RED "Invalid type or value. Please use ");
            console_write(CONSOLE_COLOR_CYAN "income" CONSOLE_COLOR_WHITE " or " CONSOLE_COLOR_CYAN "expense");
            console_write_line(CONSOLE_COLOR_WHITE " or " CONSOLE_COLOR_CYAN "saving" CONSOLE_COLOR_WHITE " or " CONSOLE_COLOR_CYAN "repayment");
        }
    } while (!is_valid);

    if (log_answer) {
        console_clear_last_line();
        console_write_line("What is the type of the transaction? " CONSOLE_COLOR_CYAN "%s", input);
    }

    return input;
}

double input_ask_amount(const bool log_answer) {
    double amount;
    char* input = nullptr;
    bool is_valid = false;

    do {
        if (input) {
            free(input);
        }

        input = console_ask_question("What was the transaction amount? (1, 1.00, 1.56)");
        is_valid = type_parser_try_parse_double(input, &amount);

        if (!is_valid || amount < 0) {
            console_write(CONSOLE_COLOR_RED "Invalid amount format or value. Please use a value like ");
            console_write(CONSOLE_COLOR_CYAN "1" CONSOLE_COLOR_WHITE " or " CONSOLE_COLOR_CYAN "1.00");
            console_write_line(CONSOLE_COLOR_WHITE " or " CONSOLE_COLOR_CYAN "1.23");
        }
    } while (!is_valid || amount < 0);

    free(input);

    if (log_answer) {
        console_clear_last_line();
        console_write_line("What was the transaction amount? " CONSOLE_COLOR_CYAN "%.2f", amount);
    }

    return amount;
}

char* input_ask_category(const bool log_answer) {
    char* input = console_ask_question("What is the transaction category?");

    if (log_answer) {
        console_clear_last_line();
        console_write_line("What is the transaction category? " CONSOLE_COLOR_CYAN "%s", input);
    }

    return input;
}

char* input_ask_description(const bool log_answer) {
    char* input = console_ask_question("What is the description of the transaction?");

    if (log_answer) {
        console_clear_last_line();
        console_write_line("What is the description of the transaction? " CONSOLE_COLOR_CYAN "%s", input);
    }

    return input;
}

bool input_ask_yes_or_no(const char* question, const bool log_answer) {
    bool value;
    char* input = nullptr;
    bool is_valid = false;

    char questionString[128];
    snprintf(questionString, 128, "%s (y/n):", question);

    do {
        if (input) {
            free(input);
        }

        input = console_ask_question(questionString);
        is_valid = type_parser_try_parse_bool(input, &value);

        if (!is_valid) {
            console_write(CONSOLE_COLOR_RED "Invalid answer. Please use a value like ");
            console_write(CONSOLE_COLOR_CYAN "yes" CONSOLE_COLOR_WHITE " or " CONSOLE_COLOR_CYAN "y");
            console_write(CONSOLE_COLOR_WHITE " or " CONSOLE_COLOR_CYAN "no" CONSOLE_COLOR_WHITE " or ");
            console_write_line(CONSOLE_COLOR_CYAN "n");
        }
    } while (!is_valid);

    free(input);

    if (log_answer) {
        console_clear_last_line();
        console_write_line("%s " CONSOLE_COLOR_CYAN "%s", question, value ? "Yes" : "No");
    }

    return value;
}