cmake_minimum_required(VERSION 3.29)
project(NetPolicyPW)

set(CMAKE_CXX_STANDARD 26)

include(FetchContent)
FetchContent_Declare(
        argparse
        GIT_REPOSITORY https://github.com/p-ranav/argparse.git
        GIT_TAG v3.1
)
FetchContent_MakeAvailable(argparse)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git GIT_TAG 11.0.2)
FetchContent_MakeAvailable(fmt)

add_executable(NetPolicyPW src/main.cpp
        src/fs_utils.cpp
        src/fs_utils.h
        src/constants.h
        src/str_utils.cpp
        src/str_utils.h)

target_link_libraries(${PROJECT_NAME} PRIVATE argparse nlohmann_json::nlohmann_json fmt::fmt)
