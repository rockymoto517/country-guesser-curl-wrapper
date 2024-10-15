#include "CountryGame.hpp"

#include <iostream>
#include <nlohmann/json.hpp>
#include <optional>

CountryGame::CountryGame() { curl = CurlHelper("http://172.19.112.1:5000"); }

void CountryGame::sign_up(const std::string &username, const std::string &email,
                          const std::string &password) {
    std::vector<std::pair<std::string, std::string>> body = {
        {"username", username},
        {"email", email},
        {"password", password},
    };
    curl.post_request("auth/signup", std::nullopt, body);
}

void CountryGame::sign_in(const std::string &email,
                          const std::string &password) {
    std::vector<std::pair<std::string, std::string>> body = {
        {"email", email},
        {"password", password},
    };
    curl.post_request("auth/signin", std::nullopt, body);

    nlohmann::json res = nlohmann::json::parse(curl.get_response());

    token = res["token"];
}

void CountryGame::create_game() {
    curl.post_request("game/new", token, std::nullopt);
    const std::string response = curl.get_response();
    if (response != "error") {
        game_id = nlohmann::json::parse(response)["game"][0]["gameId"];
        win = false;
    }
}

void CountryGame::play_turn(const std::string &country) {
    std::vector<std::pair<std::string, std::string>> body = {
        {"country", country},
        {"gameId", game_id},
    };
    curl.post_request("game/turn", token, body);
}

std::string CountryGame::get_hint() {
    nlohmann::json response = nlohmann::json::parse(curl.get_response());
    if (response.contains("hint")) {
        return response["hint"]["msg"];
    } else {
        win = true;
        return "You win!";
    }
}

bool CountryGame::did_win() { return win; }

void CountryGame::print_scoreboard() {
    curl.get_request("game/scoreboard", token);
    nlohmann::json response = nlohmann::json::parse(curl.get_response());
    std::cout << response["scoreBoard"].dump(4) << std::endl;
}
