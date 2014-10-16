set(PROJECT_NAME_STR rectangle_html_renderer)
project(${PROJECT_NAME_STR})
cmake_minimum_required(VERSION 2.8)

# set main project source list
set(SRC_LIST
         main.cpp

)

include_directories(${PROJECT_SOURCE_DIR})

# append compilation flags
list( APPEND CMAKE_CXX_FLAGS "-std=c++0x -std=c++1y ${CMAKE_CXX_FLAGS} -g -Wall -ftest-coverage")

add_executable(${PROJECT_NAME_STR} ${SRC_LIST})


target_link_libraries(
    ${PROJECT_NAME_STR}
)










