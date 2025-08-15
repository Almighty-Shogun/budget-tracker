#include "date_validation.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "utils/date_util.h"
#include "utils/string_util.h"

/**
 * @brief Checks if a year is a leap year.
 *
 * @param year Year to check.
 * @return true if leap year, false otherwise.
 *
 * @author Almighty-Shogun
 */
static bool is_leap_year(const int year) {
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

/**
 * @brief Validates if a string matches the "YYYY-MM-DD" format.
 *
 * @param date Pointer to the date string.
 * @return true if a format is valid, false otherwise.
 *
 * @author Almighty-Shogun
 */
static bool is_valid_format(const char* date) {
    if (strlen(date) != 10) {
        return false;
    }

    for (int i = 0; i < 10; i++) {
        if (((i == 4 || i == 7) && date[i] != '-') || (i != 4 && i != 7 && !isdigit((unsigned char)date[i]))) {
            return false;
        }
    }

    return true;
}

bool date_validation_is_valid_year(const int year) {
    return year >= 1900 && year <= date_util_get_current_year();
}

bool date_validation_is_valid_month(const char* month) {
    char month_lower[16];

    string_util_copy_string(month_lower, month, sizeof(month_lower));
    string_util_to_lower(month_lower);

    for (int i = 0; i < 12; i++) {
        if (string_util_is_equal(month_lower, months[i])) {
            return true;
        }
    }

    return false;
}

static bool is_valid_date(const char* date) {
    char* end;

    if (!is_valid_format(date)) {
        return false;
    }

    const int year = strtol(date, &end, 10);

    if (*end != '-') {
        return false;
    }

    const int month = strtol(end + 1, &end, 10);

    if (*end != '-') {
        return false;
    }

    const int day = strtol(end + 1, &end, 10);

    if (*end != '\0') {
        return false;
    }

    if (month < 1 || month > 12 || !date_validation_is_valid_year(year)) {
        return false;
    }

    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (is_leap_year(year) && month == 2) {
        days[1] = 29;
    }

    if (day < 1 || day > days[month - 1]) {
        return false;
    }

    return true;
}

bool date_validation_is_valid_date(const int day, const char* month, const int year) {
    char date[11];
    char month_lower[16];

    string_util_copy_string(month_lower, month, sizeof(month_lower));

    char* padded_month = date_util_get_month_padded(month_lower);

    if (!padded_month) {
        return false;
    }

    snprintf(date, sizeof(date), "%04d-%s-%02d", year, padded_month, day);

    free(padded_month);

    return is_valid_date(date);
}