cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

include(cmake/HunterGate.cmake)

HunterGate(
    URL "https://github.com/babyrage666/hunter/archive/v0.19.137.1.tar.gz"
    SHA1 "5dd3fe4797efb419dba4d161ce9a0b141134bce3"
)

project(main)

hunter_add_package(CURL)
find_package(CURL CONFIG REQUIRED)
hunter_add_package(OpenSSL)
find_package(OpenSSL REQUIRED)

add_executable(main ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(main PRIVATE CURL::libcurl OpenSSL::SSL OpenSSL::Crypto)

install(TARGETS main RUNTIME DESTINATION bin)
