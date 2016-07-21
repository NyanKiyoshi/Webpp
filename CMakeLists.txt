project(webpp)
cmake_minimum_required(VERSION 2.8)

FILE(GLOB SRC_LIST "./src/*.cpp" "./src/*/*.cpp")
FILE(GLOB HEADERS_LIST "./include/*.h" "./include/*/*.h" )

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs -lfcgi++ -lfcgi")

include_directories("./include/")
add_library(${PROJECT_NAME} ${SRC_LIST} ${HEADERS_LIST})

target_link_libraries(${PROJECT_NAME} fcgi)

add_executable(main_webpp ${SRC_LIST})
