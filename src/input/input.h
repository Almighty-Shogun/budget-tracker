/**
 * @file    input.h
 * @brief   The include file of input
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

#ifndef INPUT_H
#define INPUT_H

/**
 * @brief Prompts the user for an integer within [min, max], repeats until valid.
 *
 * @param question Prompt string.
 * @param min Minimum allowed value (inclusive).
 * @param max Maximum allowed value (inclusive).
 * @param log_answer If the answer should be logged.
 * @return Valid integer input.
 *
 * @author Almighty-Shogun
 */
int input_ask_number(const char* question, int min, int max, bool log_answer);

/**
 * @brief Prompts the user to enter a valid year.
 *
 * @param log_answer If the answer should be logged.
 * @return Valid year as an integer.
 *
 * @author Almighty-Shogun
 */
int input_ask_year(bool log_answer);

/**
 * @brief Prompts the user to enter a valid month name.
 *
 * @note Caller must free it.
 *
 * @param log_answer If the answer should be logged.
 * @return Pointer to dynamically allocated valid month string.
 *
 * @author Almighty-Shogun
 */
char* input_ask_month(bool log_answer);

/**
 * @brief Prompts the user for a date (1-31).
 *
 * @param year The year to filter the date input.
 * @param month The month to filter the date input, represented as a string.
 * @param log_answer If the answer should be logged.
 * @return Day of the month as an integer.
 *
 * @author Almighty-Shogun
 */
int input_ask_date(int year, const char* month, bool log_answer);

/**
 * @brief Prompts for a transaction type (e.g., "income", "expense").
 *
 * @note Caller must free it.
 *
 * @param log_answer If the answer should be logged.
 * @return Dynamically allocated valid type string.
 *
 * @author Almighty-Shogun
 */
char* input_ask_type(bool log_answer);

/**
 * @brief Prompts for a positive transaction amount as double.
 *
 * @param log_answer If the answer should be logged.
 * @return Valid positive double amount.
 *
 * @author Almighty-Shogun
 */
double input_ask_amount(bool log_answer);

/**
 * @brief Prompts for transaction category.
 *
 * @note Caller must free it.
 *
 * @param log_answer If the answer should be logged.
 * @return User input string pointer.
 *
 * @author Almighty-Shogun
 */
char* input_ask_category(bool log_answer);

/**
 * @brief Prompts for transaction description.
 *
 * @note Caller must free it.
 *
 * @param log_answer If the answer should be logged.
 * @return User input string pointer.
 *
 * @author Almighty-Shogun
 */
char* input_ask_description(bool log_answer);

/**
 * @brief Prompts the user with a yes/no question.
 *
 * @param question Prompt string.
 * @param log_answer If the answer should be logged.
 * @return true if yes, false if no.
 *
 * @author Almighty-Shogun
 */
bool input_ask_yes_or_no(const char* question, bool log_answer);

#endif //INPUT_H
