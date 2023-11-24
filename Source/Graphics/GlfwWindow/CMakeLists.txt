cmake_minimum_required(VERSION 3.15)

project(GlfwWindow LANGUAGES CXX)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(GLEW REQUIRED)

set(PROJECT_SOURCE_DIR ${PROJECT_NAME})
file(GLOB_RECURSE SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/*.cpp
    ${PROJECT_SOURCE_DIR}/*.h
    ${PROJECT_SOURCE_DIR}/*.hpp
)

add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ./)

target_link_libraries(${PROJECT_NAME} PUBLIC
    GLEW::GLEW
    WindowSystem
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glm::glm
)