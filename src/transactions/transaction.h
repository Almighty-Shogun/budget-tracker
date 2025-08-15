/**
 * @file    transaction.h
 * @brief   The include file of transaction
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

#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <cjson/cJSON.h>

typedef struct {
  int id;
  char type[10];
  char category[20];
  double amount;
  char description[1024];
  int date;
} transaction_t;

/**
 * @brief Ensures that the transaction directory and files exist for the current year.
 *
 * @author Almighty-Shogun
 */
void transaction_ensure_files_exists();

/**
 * @brief Retrieves the JSON contents of the file for the specified year and month.
 *
 * @note Caller must free it with cJSON_Delete.
 *
 * @param year Year of the file.
 * @param month Month name (e.g., "January").
 * @return Pointer to a cJSON object.
 *
 * @author Almighty-Shogun
 */
cJSON* transaction_get_file(int year, const char* month);

/**
 * @brief Saves JSON data to the file for the specified year and month.
 *
 * @param year Year of the data.
 * @param month Month name (e.g., "January").
 * @param json JSON string to save.
 *
 * @author Almighty-Shogun
 */
void transaction_save_file(int year, const char* month, const char* json);

/**
 * @brief Checks if a transaction type is valid (e.g., "income", "expense").
 *
 * @param type Null-terminated string (not null).
 * @return true if valid, false otherwise.
 *
 * @author Almighty-Shogun
 */
bool transaction_is_valid_type(char* type);

/**
 * @brief Converts a Transaction to a cJSON object.
 *
 * @note Caller should free ONLY it with cJSON_Delete when ownership has NOT been transferred.
 *
 * @param transaction Initialized Transaction struct.
 * @return Newly created cJSON object on success, or nullptr on failure.
 *
 * @author Almighty-Shogun
 */
cJSON* transaction_to_json(transaction_t transaction);

/**
 * @brief Converts a cJSON object to a Transaction.
 *
 * @note Caller must free it.
 *
 * @param json cJSON object (not null).
 * @return Dynamically allocated Transaction* or nullptr on failure.
 *
 * @author Almighty-Shogun
 */
transaction_t* transaction_from_json(const cJSON* json);

/**
 * @brief Retrieves the last transaction ID from a given JSON object.
 *
 * @param json Pointer to a constant cJSON object containing transaction data.
 * @return ID of the last transaction, or -1 if not found or on error.
 *
 * @author Almighty-Shogun
 */
int transaction_get_last_id(const cJSON* json);

/**
 * @brief Returns the total amount for a specific transaction type.
 *
 * @param json Pointer to cJSON containing transactions.
 * @param type Transaction type (e.g., "income", "expense").
 * @return Total amount for the given type.
 *
 * @author Almighty-Shogun
 */
double transaction_get_total_amount(const cJSON* json, const char* type);

/**
 * @brief Finds the index of a transaction by its ID in a JSON array.
 *
 * @param json Pointer to a cJSON array. Must not be NULL.
 * @param id Integer ID to search for.
 * @return Index of the transaction if found, or -1 if not found.
 *
 * @author Almighty-Shogun
 */
int transaction_find_index(const cJSON* json, int id);

#endif //TRANSACTIONS_H
