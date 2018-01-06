cmake_minimum_required(VERSION 3.2.2)

set(CMAKE_CXX_COMPILER "g++-7")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/HunterGate.cmake)

HunterGate(
    URL "https://github.com/babyrage666/hunter/archive/v0.19.137.1.tar.gz"
    SHA1 "5dd3fe4797efb419dba4d161ce9a0b141134bce3"
)

project(pack)
hunter_add_package(nlohmann_json)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(pack ${CMAKE_CURRENT_SOURCE_DIR}/sources/pack.cpp)
target_link_libraries(pack nlohmann_json)
add_executable(unpack ${CMAKE_CURRENT_SOURCE_DIR}/sources/unpack.cpp)
target_link_libraries(unpack nlohmann_json)