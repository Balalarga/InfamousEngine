cmake_minimum_required(VERSION 3.15)

project(Engine LANGUAGES CXX)

file(GLOB_RECURSE RESOURCE_FILES ./*.cpp ./*.h ./*.hpp)
add_library(${PROJECT_NAME} ${RESOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
