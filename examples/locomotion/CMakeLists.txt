
# App executable
add_executable(locomotion
        src/main.cpp
        src/CustomEvents.h
)

target_include_directories(locomotion PRIVATE
        inc
        ${PROJECT_SOURCE_DIR}/inc
)

target_link_libraries(locomotion MEGEngine)

target_compile_definitions(locomotion PRIVATE $<$<CONFIG:Debug>:DEBUG>)

if (WIN32)
    set(ENGINE_LIB_FILE libMEGEngine.dll)
else(UNIX)
    set(ENGINE_LIB_FILE libMEGEngine.so)
endif ()

add_custom_command(TARGET locomotion POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different        # executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/build/${ENGINE_LIB_FILE}"     # <-- in-file
        $<TARGET_FILE_DIR:locomotion>)                       # <-- out-file path