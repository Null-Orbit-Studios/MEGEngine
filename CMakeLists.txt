cmake_minimum_required(VERSION 4.2)
project(MEGEngineProject)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE ENGINE_SOURCES src/*.cpp src/*.h src/*.hpp inc/*.cpp inc/*.h inc/*.hpp)

add_library(MEGEngine SHARED ${ENGINE_SOURCES})

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

target_compile_definitions(MEGEngine PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
        ENGINE_BUILD
        GLM_ENABLE_EXPERIMENTAL
        STB_IMAGE_IMPLEMENTATION
)

target_compile_options(MEGEngine
        PRIVATE -fPIC
)

if (UNIX)
    target_compile_options(MEGEngine
            PRIVATE -fvisibility=hidden
    )
endif ()

add_custom_command(TARGET MEGEngine PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different        # executes "cmake -E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/defaultSettings.ini"          # <-- in-file
        ${CMAKE_BINARY_DIR}                                  # <-- out-file path
)

# default to a debug build
if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug)
endif()
unset(CMAKE_BUILD_TYPE CACHE) # Can be overwritten but resets to debug on next build

if(BUILD_EXAMPLES STREQUAL "ON")
        add_subdirectory(examples)
endif()

if(BUILD_TESTS STREQUAL "ON")
        add_subdirectory(tests)
endif()
