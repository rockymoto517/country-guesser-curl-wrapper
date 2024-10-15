#include "CurlHelper.hpp"

#include <curl/curl.h>
#include <curl/easy.h>

#include <cstdio>
#include <iostream>
#include <nlohmann/json.hpp>

CurlHelper::CurlHelper() {}

CurlHelper::CurlHelper(const std::string &base_url) : base_url(base_url) {}

void CurlHelper::post_request(
    const std::string &path, const std::optional<std::string> &token,
    const std::optional<std::vector<std::pair<std::string, std::string>>>
        &data) {
    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, create_curl_url(path).c_str());

        struct curl_slist *list = NULL;
        list = curl_slist_append(list, "Content-Type: application/json");
        if (token.has_value()) {
            list = curl_slist_append(
                list,
                std::string("Authorization: Bearer " + token.value()).c_str());
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

        if (data.has_value()) {
            nlohmann::json json;
            for (const auto &pair : data.value()) {
                json[pair.first] = pair.second;
            }
            set_post_body(json.dump());

            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_body.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, post_body.length());
        } else {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");
        }

        std::string buff;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_get_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buff);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::fprintf(stderr, "Error performing post request.\n%s\n",
                         curl_easy_strerror(res));
            exit(EXIT_FAILURE);
        } else {
            response = buff;
        }

        curl_slist_free_all(list);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}

void CurlHelper::get_request(const std::string &path,
                             const std::optional<std::string> &token) {
    curl_global_init(CURL_GLOBAL_DEFAULT);

    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, create_curl_url(path).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION,
                         static_cast<long>(CURL_HTTP_VERSION_3));

        struct curl_slist *list = NULL;
        list = curl_slist_append(list, "User-Agent: Mozilla/5.0");
        if (token.has_value()) {
            list = curl_slist_append(
                list,
                std::string("Authorization: Bearer " + token.value()).c_str());
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

        std::string buff;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_get_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buff);

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::fprintf(stderr, "Error performing post request.\n%s\n",
                         curl_easy_strerror(res));
            exit(EXIT_FAILURE);
        } else {
            response = buff;
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

const std::string CurlHelper::get_response() { return response; }

void CurlHelper::set_post_body(const std::string &body) { post_body = body; }
