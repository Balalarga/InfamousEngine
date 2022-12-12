cmake_minimum_required(VERSION 3.20)

project(UnknownEngineTester LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)

# Resources folder
set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/Assets)

add_subdirectory(../ UnknownEngine)

# Source files
file(GLOB_RECURSE PROJECT_SOURCES Source/*.cpp Source/*.h Source/*.hpp)

# Find all resources
file(GLOB_RECURSE RESOURCE_FILES ${RESOURCES_DIR}/*)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE "PROJECT_SOURCE_DIR=\"${CMAKE_SOURCE_DIR}\"")
target_compile_definitions(${PROJECT_NAME} PRIVATE "RESOURCES_DIR=\"${RESOURCES_DIR}\"")
set_target_properties(${PROJECT_NAME} PROPERTIES RESOURCE "${RESOURCE_FILES}")

target_include_directories(${PROJECT_NAME} PRIVATE Source)
target_link_libraries (${PROJECT_NAME} LINK_PUBLIC UnknownEngine)
target_include_directories(${PROJECT_NAME} PUBLIC UnknownEngine)

if (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json)
    configure_file(${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json COPYONLY)
endif()