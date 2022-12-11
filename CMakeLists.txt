cmake_minimum_required(VERSION 3.20)

project(UnknownEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(THIRDPARTY_DIR ThirdParty)

# GLEW setup
set(GLEW_DIR ${THIRDPARTY_DIR}/GLEW)
set(ADDITIONAL_INCLUDE_DIRS ${GLEW_DIR}/include)
set(ADDITIONAL_LINK_DIRS ${GLEW_DIR}/lib/x64)
set(BINARIES ${GLEW_DIR}/bin/x64)

if(WIN32)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    set(PROJECT_LIBS glew32 opengl32 glu32 Imm32)
    
    if(MINGW)
        set(PROJECT_LIBS ${PROJECT_LIBS} mingw32)
    endif()
else(WIN32)
    set(PROJECT_LIBS GLEW GL GLU)
endif(WIN32)

# SDL setup
set(SDL_DIR ${THIRDPARTY_DIR}/SDL)
set(ADDITIONAL_INCLUDE_DIRS ${ADDITIONAL_INCLUDE_DIRS} ${SDL_DIR}/include)
set(BINARIES ${BINARIES} ${SDL_DIR}/bin)
set(PROJECT_LIBS ${PROJECT_LIBS} SDL2 SDL2main SDL2_image SDL2_ttf)
if (MSVC)
    set(ADDITIONAL_LINK_DIRS ${ADDITIONAL_LINK_DIRS} ${SDL_DIR}/lib/MSVC/x64)
else()
    set(ADDITIONAL_LINK_DIRS ${ADDITIONAL_LINK_DIRS} ${SDL_DIR}/lib/MinGW/x64)
endif()

# FMT setup
add_subdirectory(${THIRDPARTY_DIR}/fmt fmt)
set(ADDITIONAL_INCLUDE_DIRS ${ADDITIONAL_INCLUDE_DIRS} ${THIRDPARTY_DIR}/fmt/include)
set(PROJECT_LIBS ${PROJECT_LIBS} fmt)

# ImGui setup
set(USE_IMGUI ON)
if (${USE_IMGUI})
    add_compile_definitions(USE_IMGUI = 1)

    set(ADDITIONAL_INCLUDE_DIRS ${ADDITIONAL_INCLUDE_DIRS}
        ${THIRDPARTY_DIR}/ImGui/
        ${THIRDPARTY_DIR}/ImGui/backends/)

    set(ADDITIONAL_SOURCES
        # Main Imgui files
       ${THIRDPARTY_DIR}/ImGui/imgui.cpp
       ${THIRDPARTY_DIR}/ImGui/imgui_draw.cpp
       ${THIRDPARTY_DIR}/ImGui/imgui_tables.cpp
       ${THIRDPARTY_DIR}/ImGui/imgui_widgets.cpp
       # SDL2+OpenGL-specific files
       ${THIRDPARTY_DIR}/ImGui/backends/imgui_impl_sdl.cpp
       ${THIRDPARTY_DIR}/ImGui/backends/imgui_impl_opengl3.cpp)
else()
    add_compile_definitions(USE_IMGUI = 0)
endif()

# RapidJson
set(ADDITIONAL_INCLUDE_DIRS ${ADDITIONAL_INCLUDE_DIRS} ${THIRDPARTY_DIR}/RapidJson/include)

# Cereal
set(ADDITIONAL_INCLUDE_DIRS ${ADDITIONAL_INCLUDE_DIRS} ${THIRDPARTY_DIR}/Cereal/include)

# Glm
set(ADDITIONAL_INCLUDE_DIRS ${ADDITIONAL_INCLUDE_DIRS} ${THIRDPARTY_DIR}/Glm/glm)

# Find all source files
file(GLOB_RECURSE PROJECT_SOURCES Sources/*.cpp Sources/*.h Sources/*.hpp)

# Add targer
add_library(${PROJECT_NAME} ${PROJECT_SOURCES} ${ADDITIONAL_SOURCES})

# Libraries linking
target_link_directories(${PROJECT_NAME} PUBLIC ${ADDITIONAL_LINK_DIRS})
target_link_libraries(${PROJECT_NAME} ${PROJECT_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC Sources ${ADDITIONAL_INCLUDE_DIRS})

# Copy dll files
foreach(BINARY ${BINARIES})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/${BINARY} $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endforeach()
