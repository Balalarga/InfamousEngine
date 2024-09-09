cmake_minimum_required(VERSION 3.15)

project(Engine LANGUAGES CXX)

set(PROJECT_SOURCE_DIR ./)

file(GLOB_RECURSE SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/*.cpp
        ${PROJECT_SOURCE_DIR}/*.h
        ${PROJECT_SOURCE_DIR}/*.hpp
)

add_library(${PROJECT_NAME} ${SOURCE_FILES}
        Cmd/ConsoleArgs.cpp
        Cmd/ConsoleArgs.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)

find_package(LLGL CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC LLGL::LLGL LLGL::LLGL_Null)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm-header-only)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

find_package(GLEW REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC GLEW::GLEW)