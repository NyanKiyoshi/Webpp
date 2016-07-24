project(webpp)
cmake_minimum_required(VERSION 2.8)

FILE(GLOB SRC_LIST      "./src/*.cpp"    "./src/*/*.cpp")
FILE(GLOB HEADERS_LIST  "./include/*.h"  "./include/*/*.h")


# -O2 -> optimisation level 2 see https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g -ftest-coverage -O2 -fprofile-arcs -lfcgi++ -lfcgi -Wl,-Map,${PROJECT_NAME}_dump.map")

include_directories("./include/")
add_library(${PROJECT_NAME} ${SRC_LIST} ${HEADERS_LIST})

target_link_libraries(${PROJECT_NAME} fcgi)

add_executable(main_webpp ${SRC_LIST})
