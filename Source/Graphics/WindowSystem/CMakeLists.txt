cmake_minimum_required(VERSION 3.15)

project(WindowSystem LANGUAGES CXX)

find_package(glm)

set(PROJECT_SOURCE_DIR ${PROJECT_NAME})
file(GLOB_RECURSE SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/*.cpp
        ${PROJECT_SOURCE_DIR}/*.h
        ${PROJECT_SOURCE_DIR}/*.hpp
)

add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC
        Time
        glm::glm
)