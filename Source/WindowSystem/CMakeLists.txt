cmake_minimum_required(VERSION 3.15)

project(WindowSystem LANGUAGES CXX)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

file(GLOB_RECURSE RESOURCE_FILES ./*.cpp ./*.h ./*.hpp)
add_library(${PROJECT_NAME} ${RESOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)