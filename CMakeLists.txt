cmake_minimum_required(VERSION 3.20)

project(UnknownEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/CMake")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(THIRDPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty)

if(WIN32)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

add_library(${PROJECT_NAME} INTERFACE)

include(Utils)
set(MODULES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)
ListOfDirectChildDirectories(MODULES_LIST ${MODULES_DIR})

foreach(MODULE ${MODULES_LIST})
    if(EXISTS ${MODULES_DIR}/${MODULE}/CMakeLists.txt)
        add_subdirectory(${MODULES_DIR}/${MODULE} ${MODULE})
        target_include_directories(${PROJECT_NAME} INTERFACE ${MODULE})
        target_link_libraries(${PROJECT_NAME} INTERFACE ${MODULE})
        get_property(MODULE_TARGET DIRECTORY ${MODULES_DIR}/${MODULE} PROPERTY BUILDSYSTEM_TARGETS)
        set_target_properties(${MODULE_TARGET} PROPERTIES FOLDER UnknownEngine)
        message("Added submodule ${MODULE_TARGET}(${MODULE})")
    endif()
endforeach()

