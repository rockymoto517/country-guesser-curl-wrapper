#include "CurlHelper.hpp"

#include <curl/curl.h>
#include <curl/easy.h>

#include <format>
#include <iostream>
#include <nlohmann/json.hpp>

CurlHelper::CurlHelper(const std::string &base_url) : base_url(base_url) {}

void CurlHelper::post_request(
    const std::string &path, const std::string &opts, const std::string &header,
    const std::vector<std::pair<std::string, std::string>> &data) {
    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, create_curl_url(path).c_str());

        struct curl_slist *list = NULL;
        list = curl_slist_append(list, header.c_str());
        list = curl_slist_append(list, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

        nlohmann::json post_body;
        for (const auto &pair : data) {
            post_body[pair.first] = pair.second;
        }
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_body.dump().c_str());

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::print(std::cerr, "Error performing post request.\n{}",
                       curl_easy_strerror(res));
        }

        curl_slist_free_all(list);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}

void CurlHelper::get_request(const std::string &path,
                             const std::string &token) {
    curl_global_init(CURL_GLOBAL_DEFAULT);

    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, create_curl_url(path).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION,
                         static_cast<long>(CURL_HTTP_VERSION_3));

        struct curl_slist *list = NULL;
        list = curl_slist_append(list, "User-Agent: Mozilla/5.0");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

        std::string buff;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_get_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buff);

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::print(std::cerr, "Error performing GET request.\n{}",
                       curl_easy_strerror(res));
        } else {
            std::print(std::cout, "Response:\n{}",
                       nlohmann::json::parse(buff).dump(4));
        }

        curl_slist_free_all(list);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}

const std::string CurlHelper::create_curl_url(const std::string &path) {
    std::string full_path = base_url + "/" + path;
    return full_path;
}

std::size_t CurlHelper::curl_get_callback(void *contents, std::size_t size,
                                          std::size_t nmemb, void *userp) {
    static_cast<std::string *>(userp)->append(static_cast<char *>(contents),
                                              size * nmemb);
    return size * nmemb;
}
