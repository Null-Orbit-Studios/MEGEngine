cmake_minimum_required(VERSION 4.2)

set(LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/libraries")

# App executable
add_executable(Game
        src/main.cpp
        src/CustomEvents.h
)

target_include_directories(Game PRIVATE
        inc
        ${LIB_PATH}/include
        ${PROJECT_SOURCE_DIR}/engine/inc
)

target_link_libraries(Game MEGEngine)

target_compile_definitions(Game PRIVATE $<$<CONFIG:Debug>:DEBUG>)

if (WIN32)
    set(ENGINE_LIB_FILE libMEGEngine.dll)
else(UNIX)
    set(ENGINE_LIB_FILE libMEGEngine.so)
endif ()

add_custom_command(TARGET Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different                   # executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/build/engine/${ENGINE_LIB_FILE}"     # <-- in-file
        $<TARGET_FILE_DIR:Game>)                                        # <-- out-file path
