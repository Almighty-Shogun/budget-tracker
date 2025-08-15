/**
 * @file    date_validation.h
 * @brief   The include file of date_validation
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

#ifndef DATE_VALIDATION_H
#define DATE_VALIDATION_H

/**
 * @brief Checks if a given year is within the valid range.
 *
 * @param year Year to validate.
 * @return true if valid otherwise, false.
 *
 * @author Almighty-Shogun
 */
bool date_validation_is_valid_year(int year);

/**
 * @brief Checks if the month name is valid.
 *
 * @param month Month name string.
 * @return true if valid otherwise, false.
 *
 * @author Almighty-Shogun
 */
bool date_validation_is_valid_month(const char* month);

/**
 * @brief Checks if a given date is valid.
 *
 * @param day Day of the month.
 * @param month Month name string.
 * @param year The year.
 * @return true if valid, false otherwise.
 *
 * @author Almighty-Shogun
 */
bool date_validation_is_valid_date(int day, const char* month, int year);

#endif //DATE_VALIDATION_H
