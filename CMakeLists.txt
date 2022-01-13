cmake_minimum_required(VERSION 3.10.2)

project(tictactoe)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(Helper)

target_include_directories(${PROJECT_NAME} 
PUBLIC Helper
)

target_link_directories(${PROJECT_NAME} 
PRIVATE Helper
)

target_link_libraries(${PROJECT_NAME} Helper)