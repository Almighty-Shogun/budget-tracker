#include "console.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

#include "console_color.h"
#include "utils/string_util.h"

int console_read_key(const char* line) {
    if (line && *line) {
        printf("%s ", line);
    }

#ifdef _WIN32
    int character = _getch();

    if (character == 0 || character == 224) {
        character = 256 + _getch();
    }

    return character;
#else
    struct termios old, new;

    tcgetattr(STDIN_FILENO, &old);

    new = old;
    new.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &new);

    const int character = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &old);

    return character;
#endif
}

char* console_read_line() {
    char buffer[1024];

    if (!fgets(buffer, sizeof(buffer), stdin)) {
        return nullptr;
    }

    string_util_trim(buffer);
    string_util_trim_new_line(buffer);

    if (buffer[0] == '\0') {
        return nullptr;
    }

    return strdup(buffer);
}

char* console_ask_question(const char* question) {
    if (question && *question) {
        printf("%s ", question);
        fflush(stdout);
    }

    console_write(CONSOLE_COLOR_CYAN);
    char* buffer = console_read_line();
    console_write(CONSOLE_COLOR_RESET);

    return buffer;
}

void console_write(const char* text, ...) {
    va_list args;
    va_start(args, text);

    vprintf(text, args);

    fflush(stdout);
    va_end(args);
}

void console_write_line(const char* text, ...) {
    va_list args;
    va_start(args, text);

    if (text && *text) {
        vprintf(text, args);
    }

    console_write(CONSOLE_COLOR_RESET "\n");

    fflush(stdout);
    va_end(args);
}

void console_clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void console_clear_last_line() {
    console_write("\033[1A\033[2K");
    fflush(stdout);
}

void console_set_title(const char* title) {
#ifdef _WIN32
    SetConsoleTitle(title);
#else
    console_write("\033]0;%s\a", title);
    fflush(stdout);
#endif
}