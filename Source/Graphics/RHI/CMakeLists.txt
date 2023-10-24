cmake_minimum_required(VERSION 3.15)

project(RHI LANGUAGES CXX)

find_package(imgui CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(GLEW REQUIRED)

file(GLOB_RECURSE RESOURCE_FILES ./*.cpp ./*.h ./*.hpp)
add_library(${PROJECT_NAME} ${RESOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
