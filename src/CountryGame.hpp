#pragma once
#include <string>

#include "CurlHelper.hpp"

class CountryGame {
   private:
    std::optional<std::string> token;
    std::string game_id;
    bool win;
    CurlHelper curl;

   public:
    CountryGame();
    void sign_in(const std::string &, const std::string &);
    void sign_up(const std::string &, const std::string &, const std::string &);
    void create_game();
    void guess_country(std::string &) const;
    void play_turn(const std::string &);
    std::string get_hint();
    bool did_win();
    void print_scoreboard();
};
