cmake_minimum_required(VERSION 3.20)

project(UnknownEngineTester LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)

# Resources folder
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Assets)

# Source files
file(GLOB_RECURSE PROJECT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.hpp)

# Find all resources
file(GLOB_RECURSE RESOURCE_FILES ${RESOURCES_DIR}/*)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE "PROJECT_SOURCE_DIR=\"${CMAKE_SOURCE_DIR}\"")
target_compile_definitions(${PROJECT_NAME} PRIVATE "RESOURCES_DIR=\"${RESOURCES_DIR}\"")
set_target_properties(${PROJECT_NAME} PROPERTIES RESOURCE "${RESOURCE_FILES}")

target_include_directories(${PROJECT_NAME} PRIVATE Source)
target_link_libraries (${PROJECT_NAME} LINK_PUBLIC UnknownEngine)
target_include_directories(${PROJECT_NAME} PUBLIC UnknownEngine)

foreach(Binary ${UNKNOWN_ENGINE_THIRDPARTY_DLLS})
    message("Copy files from ${Binary} -> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${Binary} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach()

if (EXISTS ${CMAKE_BINARY_DIR}/compile_commands.json)
    configure_file(${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json COPYONLY)
endif()