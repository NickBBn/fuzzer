cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(
        HUNTER_CACHE_SERVERS
        "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
        CACHE STRING "Default cache server"
)

include("cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.23.214.tar.gz"    # URL к ядру Hunter
        SHA1 "e14bc153a7f16d6a5eeec845fb0283c8fad8c358"
)

project(fuzzer)

hunter_add_package(nlohmann_json)
find_package(nlohmann_json CONFIG REQUIRED)

add_library(${PROJECT_NAME} INTERFACE)
add_executable(parser parser/main.cpp)
add_executable(debugger debugger/main.cpp)


target_include_directories(${PROJECT_NAME}
        INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
        )

target_link_libraries(${PROJECT_NAME} INTERFACE
        nlohmann_json::nlohmann_json)
target_link_libraries(parser nlohmann_json::nlohmann_json)
target_link_libraries(debugger ${PROJECT_NAME})