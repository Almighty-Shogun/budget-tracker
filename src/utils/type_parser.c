#include "type_parser.h"

#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "string_util.h"

static char* true_values[] = {
    "true", "yes", "y", "on", "1"
};

static char* false_values[] = {
    "false", "no", "n", "off", "0"
};

bool type_parser_try_parse_integer(const char* input, int* output) {
    if (!input || !output) {
        return false;
    }

    char buffer[128];

    strncpy(buffer, input, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    string_util_trim(buffer);

    if (*buffer == '\0') {
        return false;
    }

    char* end;
    const long value = strtol(buffer, &end, 10);

    if (buffer == end || *end != '\0' || value < INT_MIN || value > INT_MAX) {
        return false;
    }

    *output = (int)value;

    return true;
}

bool type_parser_try_parse_double(const char* input, double* output) {
    if (!input || !output) {
        return false;
    }

    char buffer[128];
    strncpy(buffer, input, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    string_util_trim(buffer);

    if (*buffer == '\0') {
        return false;
    }

    char* end;
    const double value = strtod(buffer, &end);

    if (buffer == end || *end != '\0') {
        return false;
    }

    *output = value;

    return true;
}

bool type_parser_try_parse_bool(const char* input, bool* output) {
    if (!input || !output) {
        return false;
    }

    char buffer[16];
    strncpy(buffer, input, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    string_util_trim(buffer);
    string_util_to_lower(buffer);

    constexpr int true_count  = sizeof(true_values) / sizeof(true_values[0]);
    constexpr int false_count = sizeof(false_values) / sizeof(false_values[0]);

    for (int i = 0; i < true_count; i++) {
        if (strcmp(buffer, true_values[i]) == 0) {
            *output = true;
            return true;
        }
    }

    for (int i = 0; i < false_count; i++) {
        if (strcmp(buffer, false_values[i]) == 0) {
            *output = false;
            return true;
        }
    }

    return false;
}