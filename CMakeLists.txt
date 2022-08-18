cmake_minimum_required(VERSION 3.7)
project(UI)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES "UI/*.cpp" "UI/*.h")

include_directories(${PROJECT_NAME})

add_library(${PROJECT_NAME} ${SOURCE_FILES})