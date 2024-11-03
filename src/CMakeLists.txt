cmake_minimum_required(VERSION 3.29)
project(src)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)
FETCHCONTENT_MAKEAVAILABLE(SFML)

set(CMAKE_CXX_STANDARD 23)

add_executable(src main.cpp)

target_link_libraries(src sfml-graphics sfml-window sfml-system)