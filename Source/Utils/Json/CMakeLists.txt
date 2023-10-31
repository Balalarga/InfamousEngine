cmake_minimum_required(VERSION 3.15)

project(Json LANGUAGES CXX)

find_package(nlohmann_json CONFIG REQUIRED)

set(PROJECT_SOURCE_DIR ${PROJECT_NAME})
file(GLOB_RECURSE SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/*.cpp
    ${PROJECT_SOURCE_DIR}/*.h
    ${PROJECT_SOURCE_DIR}/*.hpp
)

add_library(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)