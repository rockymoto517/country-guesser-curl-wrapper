#include <curl/curl.h>

#include <string>
#include <utility>
#include <vector>

class CurlHelper {
   public:
    std::string base_url;
    CURL *curl;

    CurlHelper(const std::string &);
    void post_request(const std::string &, const std::string &,
                      const std::string &,
                      const std::vector<std::pair<std::string, std::string>> &);
    void get_request(const std::string &, const std::string &);
    static std::size_t curl_get_callback(void *, std::size_t, std::size_t,
                                         void *);

   private:
    const std::string create_curl_url(const std::string &);
};
