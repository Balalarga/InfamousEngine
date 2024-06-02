cmake_minimum_required(VERSION 3.15)

project(ResourceManagerTests LANGUAGES CXX)


file(GLOB_RECURSE SOURCE_FILES *.cpp *.h *.hpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Tests")
target_link_libraries(${PROJECT_NAME} PRIVATE InfamousEngine GTest::gtest_main GTest::gtest)

add_test(${PROJECT_NAME} ${PROJECT_NAME})
