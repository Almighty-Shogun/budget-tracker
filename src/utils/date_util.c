#include "date_util.h"

#include <time.h>
#include <stdio.h>
#include <string.h>

#include "string_util.h"

char* months[] = {
    "january", "february", "march", "april", "may", "june",
    "july", "august", "september", "october", "november", "december"
};

static struct tm get_current_time() {
    const time_t now = time(nullptr);
    const struct tm* tm = localtime(&now);

    return *tm;
}

int date_util_get_current_day() {
    const struct tm current_time = get_current_time();

    return current_time.tm_mday;
}

int date_util_get_current_month() {
    const struct tm current_time = get_current_time();

    return current_time.tm_mon + 1;
}

int date_util_get_current_year() {
    const struct tm current_time = get_current_time();

    return current_time.tm_year + 1900;
}

char* date_util_get_month_name(const int month) {
    return months[month - 1];
}

char* date_util_get_current_month_name() {
    const int month = date_util_get_current_month();

    return date_util_get_month_name(month);
}

int date_util_get_month_number(char* month) {
    if (!month) {
        return -1;
    }

    string_util_to_lower(month);

    for (int i = 0; i < 12; i++) {
        if (strcmp(months[i], month) == 0) {
            return i + 1;
        }
    }

    return -1;
}

char* date_util_get_month_padded(char* month) {
    if (!month) {
        return nullptr;
    }

    char buffer[12];
    const int month_number = date_util_get_month_number(month);

    sprintf(buffer, "%02d", month_number > 0 ? month_number : 0);

    return strdup(buffer);
}