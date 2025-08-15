/**
 * @file    date_util.h
 * @brief   The include file of date_util
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

#ifndef DATE_UTILS_H
#define DATE_UTILS_H

/**
 * @brief Array containing the names of all months in a year.
 *
 * @note Months are stored entirely in lowercase.
 *
 * @author Almighty-Shogun
 */
extern char* months[12];

/**
 * @brief Returns the current day of the month (1–31).
 *
 * @return Integer representing the day.
 *
 * @author Almighty-Shogun
 */
int date_util_get_current_day();

/**
 * @brief Returns the current month of the year (1–12).
 *
 * @return Integer representing the month.
 *
 * @author Almighty-Shogun
 */
int date_util_get_current_month();

/**
 * @brief Returns the current year.
 *
 * @return Integer representing the year.
 *
 * @author Almighty-Shogun
 */
int date_util_get_current_year();

/**
 * @brief Returns the name of the current month.
 *
 * @return Pointer to string with the current month's name.
 *
 * @author Almighty-Shogun
 */
char* date_util_get_current_month_name();

/**
 * @brief Returns the name of a month given its number (1–12).
 *
 * @param month Integer representing the month.
 * @return Pointer to string with month name, or NULL if invalid.
 *
 * @author Almighty-Shogun
 */
char* date_util_get_month_name(int month);

/**
 * @brief Returns the month number (1–12) for a given month name.
 *
 * @param month Null-terminated string with the month name.
 * @return Integer month number (1–12), or -1 if invalid.
 *
 * @author Almighty-Shogun
 */
int date_util_get_month_number(char* month);

/**
 * @brief Converts a month name to a zero-padded numeric string (e.g., "September" -> "09").
 *
 * @note Caller must free it.
 *
 * @param month Month name (case-insensitive). Must not be NULL.
 * @return Dynamically allocated string with a zero-padded month number ("01"-"12") or "00" if invalid.
 *
 * @author Almighty-Shogun
 */
char* date_util_get_month_padded(char* month);

#endif //DATE_UTILS_H
