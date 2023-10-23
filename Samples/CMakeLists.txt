cmake_minimum_required(VERSION 3.15)

project(InfamousEngineSamples LANGUAGES CXX)

file(GLOB_RECURSE PROJECT_SOURCES ./*.cpp ./*.h ./*.hpp)

# Resources folder
set(RESOURCES_DIR Resources)
# Find all resources
file(GLOB_RECURSE RESOURCE_FILES ${CMAKE_SOURCE_DIR}/${RESOURCES_DIR}/*)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${RESOURCE_FILES})
#target_compile_definitions(${PROJECT_NAME} PRIVATE "RESOURCES_DIR=\"${RESOURCES_DIR}\"")
#set_target_properties(${PROJECT_NAME} PROPERTIES RESOURCE "${RESOURCE_FILES}")

target_link_libraries(${PROJECT_NAME} InfamousEngine)
