cmake_minimum_required(VERSION 3.5)
include(FetchContent)

project(CountryGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall ")

file(GLOB SOURCES src/*.cpp src/*.hpp)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)
set(JSON_BuildTests OFF CACHE INTERNAL "")

FetchContent_Declare(curl 
	URL https://curl.se/download/curl-8.10.1.tar.xz
	OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(curl)

add_executable(CountryGame ${SOURCES})

find_package(CURL CONFIG REQUIRED)

target_link_libraries(CountryGame PRIVATE CURL::libcurl)
target_link_libraries(CountryGame PRIVATE nlohmann_json::nlohmann_json)
