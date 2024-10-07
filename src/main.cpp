#include <format>
#include <iostream>

#include "CurlHelper.hpp"

int main(void) {
    CurlHelper c("http://127.0.0.1:5000");
    std::print(std::cout, "Hi!\n");
    c.get_request("todos", "");
}
