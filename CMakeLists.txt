cmake_minimum_required(VERSION 3.5)
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
include(FetchContent)

project(CurlHelper LANGUAGES CXX)

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
add_executable(CurlHelper ${SOURCES})

find_package(CURL CONFIG REQUIRED)

target_link_libraries(CurlHelper PRIVATE CURL::libcurl)
target_link_libraries(CurlHelper PRIVATE nlohmann_json::nlohmann_json)
