cmake_minimum_required(VERSION 3.12)
project(json)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Wpedantic -Weffc++ -Werror)

include_directories(${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(jpath)
add_subdirectory(json)
