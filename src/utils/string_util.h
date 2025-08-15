/**
 * @file    string_util.h
 * @brief   The include file of string_util
 *
 * Copyright (c) 2025, Almighty Shogun.
 * ------------------------------------------------------------------
 * Almighty Shogun - https://github.com/Almighty-Shogun
 * BudgetTracker - https://github.com/Almighty-Shogun/BudgetTracker
 * ------------------------------------------------------------------
 * This file is part of BudgetTracker.
 * For the full copyright and license information, please view the
 * LICENSE file that was distributed with this source code.
 */

#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <stddef.h>

/**
 * @brief Converts a null-terminated string to lowercase.
 *
 * @param string Pointer to the string. Does nothing if NULL.
 *
 * @author Almighty-Shogun
 */
void string_util_to_lower(char* string);

/**
 * @brief Trims leading and trailing whitespace from a null-terminated string.
 *
 * @param string Pointer to the string. Does nothing if NULL.
 *
 * @author Almighty-Shogun
 */
void string_util_trim(char* string);

/**
 * @brief Removes trailing newline and carriage return characters from a string.
 *
 * @param string Pointer to the string. Does nothing if NULL.
 *
 * @author Almighty-Shogun
 */
void string_util_trim_new_line(char* string);

/**
 * @brief Creates a string with a character repeated a given number of times.
 *
 * @note Caller must free it.
 *
 * @param character The character to repeat.
 * @param amount Number of repetitions. Must be non-negative.
 * @return Allocated string or NULL on failure/invalid amount.
 *
 * @author Almighty-Shogun
 */
char* string_util_repeat_character(char character, size_t amount);

/**
 * @brief Copies the content of the source string to the destination string.
 *
 * @param destination Pointer to the destination buffer.
 * @param source Pointer to the source null-terminated string.
 * @param size Size of the destination buffer.
 *
 * @author Almighty-Shogun
 */
void string_util_copy_string(char* destination, const char* source, size_t size);

/**
 * @brief Compares two null-terminated strings for equality.
 *
 * @param string_one Pointer to the first string. Must not be NULL.
 * @param string_two Pointer to the second string. Must not be NULL.
 * @return True if the strings are equal otherwise, false.
 *
 * @author Almighty-Shogun
 */
bool string_util_is_equal(const char* string_one, const char* string_two);

/**
 * @brief Capitalizes the first non-whitespace character of a null-terminated string.
 *
 * @param string Pointer to the string. Does nothing if NULL.
 *
 * @author Almighty-Shogun
 */
void string_util_uc_first(char* string);

#endif //STRING_UTIL_H
