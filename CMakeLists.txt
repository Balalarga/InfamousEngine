cmake_minimum_required(VERSION 3.15)

project(InfamousEngine LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)

set(CXX_SOURCE_DIR InfamousEngine)

add_library(${PROJECT_NAME} INTERFACE IMPORTED)

# Add common libs
file(GLOB FILES LIST_DIRECTORIES true ${CXX_SOURCE_DIR}/*)
foreach(ITEM ${FILES})
	if(IS_DIRECTORY ${ITEM})
        if(EXISTS ${ITEM}/CMakeLists.txt)
            add_subdirectory(${ITEM})
            get_filename_component(LibName ${ITEM} NAME)
            target_link_libraries(${PROJECT_NAME} INTERFACE ${LibName})
        endif()
	endif()
endforeach()

# enable_testing()
# if(${BUILD_TESTING})
#     add_subdirectory(Tests)
# endif()

set(IS_MAIN_MODULE ${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
if (${IS_MAIN_MODULE})
    add_subdirectory(Samples)
endif()


if (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json)
    configure_file(${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json COPYONLY)
endif()
