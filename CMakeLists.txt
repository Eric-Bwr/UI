cmake_minimum_required(VERSION 3.7)
project(UI)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

SET(CMAKE_EXE_LINKER_FLAGS "-v")

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES "UI/*.cpp" "UI/*.h" "Sandbox/*.cpp" "Sandbox/*.h")

set(dir ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(Dependencies)

include_directories(${PROJECT_NAME} "Dependencies/OpenGL/include")
include_directories(${PROJECT_NAME} "Dependencies/Math/include")
include_directories(${PROJECT_NAME} "Dependencies/GLFW/include")
include_directories(${PROJECT_NAME} "Dependencies/FreeType/include")

include_directories(${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${SOURCE_FILES} UI/Structure/Defines.h UI/UITexture.cpp UI/UITexture.h UI/Components/TextArea/UITextArea.cpp UI/Components/TextArea/UITextArea.h)

target_link_libraries(${PROJECT_NAME}
        ${CMAKE_CURRENT_LIST_DIR}/Dependencies/FreeType/freetype.a
        ${CMAKE_CURRENT_LIST_DIR}/Dependencies/OpenGL/OpenGL.a
        ${CMAKE_CURRENT_LIST_DIR}/Dependencies/Math/Math.a
        ${CMAKE_CURRENT_LIST_DIR}/Dependencies/GLFW/libglfw3.a
        )