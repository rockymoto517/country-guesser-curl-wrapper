#include "GameFunctions.hpp"

#include <format>
#include <iostream>
#include <string>

#if defined(_WIN32) || defined(_WIN64)
#include <consoleapi.h>
#include <processenv.h>
#include <winbase.h>
#include <windows.h>
#elif defined(__APPLE__) || defined(__unix__)
#include <termios.h>
#include <unistd.h>
#endif

#if defined(_WIN32) || defined(_WIN64)
void disable_echo(HANDLE hConsole) {
    DWORD console_mode;
    GetConsoleMode(hConsole, &console_mode);
    console_mode &= ~ENABLE_ECHO_INPUT;
    SetConsoleMode(hConsole, console_mode);
}

void enable_echo(HANDLE hConsole) {
    DWORD console_mode;
    GetConsoleMode(hConsole, &console_mode);
    console_mode |= ENABLE_ECHO_INPUT;
    SetConsoleMode(hConsole, console_mode);
}
#elif defined(__APPLE__) || defined(__unix__)
void disable_echo() {
    termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void enable_echo() {
    termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}
#endif

void clear_screen() { std::cout << "\033[2J\033[H"; }

void sign_up(CountryGame &game) {
    std::string username, email, password;
    std::printf("Username: ");
    std::getline(std::cin, username);

    std::printf("Email: ");
    std::getline(std::cin, email);

    std::printf("Password: ");
#if defined(_WIN32) || defined(_WIN64)
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    disable_echo(hStdin);
    std::getline(std::cin, password);
    enable_echo(hStdin);
#elif defined(__APPLE__) || defined(__unix__)
    disable_echo();
    std::getline(std::cin, password);
    enable_echo();
#endif

    game.sign_up(username, email, password);
}

void sign_in(CountryGame &game) {
    std::string email, password;
    std::printf("Email: ");
    std::getline(std::cin, email);

    std::printf("Password: ");
#if defined(_WIN32) || defined(_WIN64)
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    disable_echo(hStdin);
    std::getline(std::cin, password);
    enable_echo(hStdin);
#elif defined(__APPLE__) || defined(__unix__)
    disable_echo();
    std::getline(std::cin, password);
    enable_echo();
#endif

    game.sign_in(email, password);
}

void play_game(CountryGame &game) {
    game.create_game();
    std::printf("Game created\n");

    for (;;) {
        std::string line;
        std::printf("Guess a country: ");
        std::getline(std::cin, line);

        game.play_turn(line);
        std::string hint = game.get_hint();
        std::print(std::cout, "{}\n", hint);

        if (game.did_win()) {
            break;
        }
    }
}

void view_scoreboard(CountryGame &game) { game.print_scoreboard(); }
