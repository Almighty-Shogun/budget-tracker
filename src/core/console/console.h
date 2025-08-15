/**
 * @file    console.h
 * @brief   The include file of console
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

#ifndef CONSOLE_H
#define CONSOLE_H

/**
 * @brief Reads a single key press from the console without echoing.
 *
 * @return ASCII value of the key pressed, or >255 for special keys on Windows.
 *
 * @author Almighty-Shogun
 */
int console_read_key(const char* line);

/**
 * @brief Reads a line of input from the console.
 *
 * @note Caller must free it.
 *
 * @return Allocated string with user input, or NULL on error.
 *
 * @author Almighty-Shogun
 */
char* console_read_line();

/**
 * @brief Reads a line of input from the console after displaying a prompt.
 *
 * @note Caller must free it.
 *
 * @param question Prompt to display before input (optional).
 * @return Allocated string with user input, or NULL on error.
 *
 * @author Almighty-Shogun
 */
char* console_ask_question(const char* question);

/**
 * @brief Writes formatted text to the console.
 *
 * @param text The text in a format string.
 * @param ... Additional arguments corresponding to the format specifiers.
 *
 * @author Almighty-Shogun
 */
void console_write(const char* text, ...);

/**
 * @brief Writes formatted text followed by a newline to the console.
 *
 * @param text The text in a format string.
 * @param ... Additional arguments corresponding to the format specifiers.
 *
 * @author Almighty-Shogun
 */
void console_write_line(const char* text, ...);

/**
 * @brief Clears the console screen.
 *
 * @author Almighty-Shogun
 */
void console_clear();

/**
 * @brief Clears the last line of the console output.
 *
 * @author Almighty-Shogun
 */
void console_clear_last_line();

/**
 * @brief Sets the title of the console.
 *
 * @param title The title of the console.
 *
 * @author Almighty-Shogun
 */
void console_set_title(const char* title);

#endif //CONSOLE_H