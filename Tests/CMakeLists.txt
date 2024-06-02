cmake_minimum_required(VERSION 3.15)

project(InfamousEngineTests LANGUAGES CXX)

enable_testing()
find_package(GTest REQUIRED)

file(GLOB TEST_DIRECTORIES LIST_DIRECTORIES true ${CMAKE_CURRENT_LIST_DIR}/*)
foreach (DIR_PATH ${TEST_DIRECTORIES})
    if (NOT IS_DIRECTORY ${DIR_PATH} OR NOT EXISTS ${DIR_PATH}/CMakeLists.txt)
        continue()
    endif ()

    get_filename_component(TEST_DIR_NAME ${DIR_PATH} NAME)
    add_subdirectory(${TEST_DIR_NAME})
endforeach ()
