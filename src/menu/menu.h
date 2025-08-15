/**
 * @file    menu.h
 * @brief   The include file of menu
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

#ifndef MENU_H
#define MENU_H

/**
 * @brief Displays a formatted header with the given title surrounded by hash (#) characters.
 *
 * @param title The header title string. Must not be NULL.
 *
 * @author Almighty-Shogun
 */
void menu_show_header(const char* title);

/**
 * @brief Displays a menu option with its ID and description.
 *
 * @param id Numeric identifier of the menu option.
 * @param description Textual description of the option. Must not be NULL.
 *
 * @author Almighty-Shogun
 */
void menu_show_option(int id, const char* description);

/**
 * @brief Handles the main menu loop, allowing the user to interact with various menu options.
 *
 * @author Almighty-Shogun
 */
void menu_handle();

#endif //MENU_H
