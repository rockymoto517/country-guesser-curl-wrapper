#pragma once
#include <curl/curl.h>

#include <optional>
#include <string>
#include <utility>
#include <vector>

class CurlHelper {
   public:
    CURL *curl;
    std::string base_url;
    std::string post_body;

    CurlHelper();
    CurlHelper(const std::string &);

    void post_request(
        const std::string &path, const std::optional<std::string> &token,
        const std::optional<std::vector<std::pair<std::string, std::string>>>
            &data);
    void get_request(const std::string &path,
                     const std::optional<std::string> &token);
    static std::size_t curl_get_callback(void *, std::size_t, std::size_t,
                                         void *);
    const std::string get_response();

   private:
    const std::string create_curl_url(const std::string &);
    void set_post_body(const std::string &);

    std::string response;
};
