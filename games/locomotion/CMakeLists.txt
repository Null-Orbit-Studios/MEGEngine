
file(GLOB_RECURSE GAME_SOURCES src/*.cpp src/*.h src/*.hpp)

# App executable
add_executable(locomotion ${GAME_SOURCES})

target_include_directories(locomotion PRIVATE
        inc
        ${PROJECT_SOURCE_DIR}/engine/inc
)

target_link_libraries(locomotion MEGEngine)

target_compile_definitions(locomotion PRIVATE $<$<CONFIG:Debug>:DEBUG>)

if (WIN32)
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        set(ENGINE_LIB_FILE libMEGEngine.lib)
    else()
        set(ENGINE_LIB_FILE libMEGEngine.dll)
    endif()
else(UNIX)
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        set(ENGINE_LIB_FILE libMEGEngine.a)
    else()
        set(ENGINE_LIB_FILE libMEGEngine.so)
    endif()
endif ()

add_custom_command(TARGET locomotion POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different        # executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/build/engine/${ENGINE_LIB_FILE}"     # <-- in-file
        $<TARGET_FILE_DIR:locomotion>)                       # <-- out-file path