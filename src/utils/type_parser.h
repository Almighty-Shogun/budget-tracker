/**
 * @file    type_parser.h
 * @brief   The include file of type_parser
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

#ifndef TYPE_PARSER_H
#define TYPE_PARSER_H

/**
 * @brief Parses an integer from a string.
 *
 * @param input Input string that should be parsed.
 * @param output Pointer to store the result.
 * @return true if parsing succeeds, false otherwise.
 *
 * @author Almighty-Shogun
 */
bool type_parser_try_parse_integer(const char* input, int* output);

/**
 * @brief Parses a double from a string.
 *
 * @param input Input string that should be parsed.
 * @param output Pointer to store the result.
 * @return true if parsing succeeds, false otherwise.
 *
 * @author Almighty-Shogun
 */
bool type_parser_try_parse_double(const char* input, double* output);

/**
 * @brief Parses a boolean from a string.
 *
 * @note Accepts values like "true", "false", "yes", "no", etc.
 *
 * @param input Input string that should be parsed.
 * @param output Pointer to store the result.
 * @return true if parsing succeeds, false otherwise.
 *
 * @author Almighty-Shogun
 */
bool type_parser_try_parse_bool(const char* input, bool* output);

#endif //TYPE_PARSER_H
