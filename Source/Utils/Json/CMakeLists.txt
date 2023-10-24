cmake_minimum_required(VERSION 3.15)

project(Json LANGUAGES CXX)

find_package(nlohmann_json CONFIG REQUIRED)

file(GLOB_RECURSE RESOURCE_FILES ./*.cpp ./*.h ./*.hpp)
add_library(${PROJECT_NAME} ${RESOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
set(nlohmann-json_IMPLICIT_CONVERSIONS OFF)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)