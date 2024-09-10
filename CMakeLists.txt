cmake_minimum_required(VERSION 3.15)

project(InfamousEngine LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)

set(CXX_SOURCE_DIR Source)

add_library(${PROJECT_NAME} INTERFACE IMPORTED)
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

function(RecursivlyAddSubdirectories TARGET_SOURCE_DIR)
    file(GLOB FILES LIST_DIRECTORIES true ${TARGET_SOURCE_DIR}/*)
    foreach (ITEM ${FILES})
        if (NOT IS_DIRECTORY ${ITEM})
            continue()
        endif ()

        set(extra_args ${ARGN})
        if (extra_args)
            set(FOLDER_PATH ${extra_args})
        endif ()
        get_filename_component(DirName ${ITEM} NAME)
        if (EXISTS ${ITEM}/CMakeLists.txt)
            add_subdirectory(${ITEM})
            target_link_libraries(${PROJECT_NAME} INTERFACE ${DirName})
            if (FOLDER_PATH)
                set_target_properties(${DirName} PROPERTIES FOLDER "${FOLDER_PATH}")
            endif ()
        else ()
            if (FOLDER_PATH)
                RecursivlyAddSubdirectories(${ITEM} "${FOLDER_PATH}/${DirName}")
            else ()
                RecursivlyAddSubdirectories(${ITEM} "${DirName}")
            endif ()
        endif ()
    endforeach ()
endfunction()

# Add common libs
RecursivlyAddSubdirectories(${CXX_SOURCE_DIR} Core)

set(IS_MAIN_MODULE ${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
if (${IS_MAIN_MODULE})
    add_subdirectory(Tests)
    add_subdirectory(Samples)
endif ()