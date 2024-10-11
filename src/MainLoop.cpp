#include <iostream>
#include <stdexcept>
#include <string>

#include "GameFunctions.hpp"

void MainLoop() {
    CountryGame game;
    bool exit = false;
    for (;;) {
        std::string line;
        int input;
        std::printf("1. Sign up\n2. Sign in\n3. Exit\n");
        std::getline(std::cin, line);
        try {
            input = std::stoi(line);
            if (input == 1) {
                sign_up(game);
                break;
            } else if (input == 2) {
                sign_in(game);
                break;
            } else if (input == 3) {
                exit = true;
                break;
            } else {
                std::printf("Input must be 1-3.\n");
            }
        } catch (const std::invalid_argument &e) {
            std::cerr << "Invalid input: not a valid integer.\n";
        } catch (const std::out_of_range &e) {
            std::cerr << "Input is out of range for an integer.\n";
        }
    }

    if (exit) return;

    clear_screen();

    for (;;) {
        std::string line;
        int input;
        std::printf("1. Play a game\n2. View scoreboard\n3. Exit\n");
        std::getline(std::cin, line);
        try {
            input = std::stoi(line);
            if (input == 1) {
                clear_screen();
                play_game(game);
            } else if (input == 2) {
                clear_screen();
                view_scoreboard(game);
            } else if (input == 3) {
                break;
            } else {
                std::printf("Input must be 1-3.\n");
            }
        } catch (const std::invalid_argument &e) {
            std::cerr << "Invalid input: not a valid integer.\n";
        } catch (const std::out_of_range &e) {
            std::cerr << "Input is out of range for an integer.\n";
        }
    }
}
