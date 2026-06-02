cmake_minimum_required(VERSION 4.2)
project(MEGEngineProject)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE ENGINE_SOURCES src/*.cpp src/*.h src/*.hpp inc/*.cpp inc/*.h inc/*.hpp)

add_library(MEGEngine SHARED ${ENGINE_SOURCES})

# -----------------------------------------------------
# COMPILE TIME DEFINTIONS
# -----------------------------------------------------

if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug) # default to a debug build
endif()
unset(CMAKE_BUILD_TYPE CACHE) # Can be overwritten but resets to debug on next build

if (CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_definitions(MEGEngine PRIVATE
                RELEASE
        )
        message("-- Building in RELEASE mode")
else
        target_compile_definitions(MEGEngine PRIVATE
                DEBUG
        )
        message("-- Building in DEBUG mode")
endif()

target_compile_definitions(MEGEngine PRIVATE
        ENGINE_BUILD
        GLM_ENABLE_EXPERIMENTAL
        STB_IMAGE_IMPLEMENTATION
)

# -----------------------------------------------------
# COMPILATION FLAGS
# -----------------------------------------------------

target_compile_options(MEGEngine PRIVATE
        -fPIC
        -Wall
        -Wextra
        -O2
)

if (UNIX)
    target_compile_options(MEGEngine
            PRIVATE -fvisibility=hidden
    )
endif ()

# -----------------------------------------------------
# INCLUDE & LINKING
# -----------------------------------------------------

target_include_directories(MEGEngine
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/
)

# GLFW and GLAD libraries
target_link_libraries(MEGEngine PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/GLFW/libglfw3.a
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/GLAD/libGLADstatic.a
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/GLM/libglm.a
)

# -----------------------------------------------------
# CUSTOM ACTIONS
# -----------------------------------------------------

add_custom_command(TARGET MEGEngine PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different        # executes "cmake -E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/defaultSettings.json"         # <-- in-file
        ${CMAKE_BINARY_DIR}                                  # <-- out-file path
)

# -----------------------------------------------------
# SUB-DIRECTORIES
# -----------------------------------------------------

option(BUILD_EXAMPLES ON)
if(BUILD_EXAMPLES STREQUAL "ON")
        message("-- BUILDING EXAMPLES")
        add_subdirectory(examples)
endif()

option(BUILD_TESTS ON)
if(BUILD_TESTS STREQUAL "ON")
        message("-- BUILDING TESTS")
        add_subdirectory(tests)
endif()
