cmake_minimum_required(VERSION 3.5)

project(CurlHelper VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall ")

file(GLOB SOURCES src/*.cpp src/*.hpp)

add_subdirectory("${CMAKE_SOURCE_DIR}/vendor/json")
add_executable(CurlHelper ${SOURCES})

find_package(CURL REQUIRED)

target_link_libraries(CurlHelper PRIVATE CURL::libcurl)
target_link_libraries(CurlHelper PRIVATE nlohmann_json::nlohmann_json)
