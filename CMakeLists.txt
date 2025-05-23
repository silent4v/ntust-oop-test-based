cmake_minimum_required(VERSION 3.8)

project(FinalExamExample)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ONLINE_JUDGE_MODE OFF)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/001")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/002")