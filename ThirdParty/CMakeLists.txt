cmake_minimum_required(VERSION 3.20)

project(ThirdParty LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GLEW setup
set(GLEW_DIR ${THIRDPARTY_DIR}/GLEW)
set(ADDITIONAL_INCLUDE_DIRS ${GLEW_DIR}/include)
set(ADDITIONAL_LINK_DIRS ${GLEW_DIR}/lib/x64)
set(BINARIES ${GLEW_DIR}/bin/x64)

if(WIN32)
    set(PROJECT_LIBS glew32 opengl32 glu32 Imm32)
    if(MINGW)
        set(PROJECT_LIBS ${PROJECT_LIBS} mingw32)
    endif()
else(WIN32)
    set(PROJECT_LIBS GLEW GL GLU)
endif(WIN32)

# GLM includes
set(ADDITIONAL_INCLUDE_DIRS ${ADDITIONAL_INCLUDE_DIRS} ${THIRDPARTY_DIR}/glm)

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
set_target_properties(fmt PROPERTIES FOLDER ThirdParty)
set(ADDITIONAL_INCLUDE_DIRS ${ADDITIONAL_INCLUDE_DIRS} fmt)
set(PROJECT_LIBS ${PROJECT_LIBS} fmt)

# RapidJson setup
set(ADDITIONAL_INCLUDE_DIRS ${ADDITIONAL_INCLUDE_DIRS} ${THIRDPARTY_DIR}/RapidJson/include)

# Cereal setup
set(ADDITIONAL_INCLUDE_DIRS ${ADDITIONAL_INCLUDE_DIRS} ${THIRDPARTY_DIR}/Cereal/include)

set(USE_IMGUI ON)
if (${USE_IMGUI})
# ImGui setup
    add_compile_definitions(USE_IMGUI = 1)
    
    file(GLOB ADDITIONAL_SOURCES ${THIRDPARTY_DIR}/ImGui/*.cpp ${THIRDPARTY_DIR}/ImGui/*.h ${THIRDPARTY_DIR}/ImGui/*.hpp)
    set(ADDITIONAL_SOURCES ${ADDITIONAL_SOURCES}
        # Main Imgui files
       ${THIRDPARTY_DIR}/ImGui/backends/imgui_impl_sdl.cpp
       ${THIRDPARTY_DIR}/ImGui/backends/imgui_impl_opengl3.cpp)
    set(ADDITIONAL_INCLUDE_DIRS ${ADDITIONAL_INCLUDE_DIRS} ${THIRDPARTY_DIR}/ImGui/)
    set(ADDITIONAL_INCLUDE_DIRS ${ADDITIONAL_INCLUDE_DIRS} ${THIRDPARTY_DIR}/ImGui/backends/)
else()
    add_compile_definitions(USE_IMGUI = 0)
endif()

add_library(${PROJECT_NAME} ${ADDITIONAL_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ThirdParty)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${PROJECT_LIBS})
target_link_directories(${PROJECT_NAME} PUBLIC ${ADDITIONAL_LINK_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${ADDITIONAL_INCLUDE_DIRS})