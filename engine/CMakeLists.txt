
find_package(OpenGL REQUIRED)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(LIBRARY_TYPE STATIC)
else()
    set(LIBRARY_TYPE SHARED)
endif()

file(GLOB_RECURSE ENGINE_SOURCES src/*.cpp)
add_library(MEGEngine ${LIBRARY_TYPE} ${ENGINE_SOURCES})

# -----------------------------------------------------
# COMPILE TIME DEFINTIONS
# -----------------------------------------------------

if (CMAKE_BUILD_TYPE STREQUAL "Release")
        message("-- Building in RELEASE mode")
        target_compile_definitions(MEGEngine PRIVATE
                RELEASE
        )
else()
        message("-- Building in DEBUG mode")
        target_compile_definitions(MEGEngine PRIVATE
                DEBUG
        )
        target_compile_options(MEGEngine PRIVATE
                -g
        )
endif()
unset(CMAKE_BUILD_TYPE CACHE)

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
)

if (UNIX)
    target_compile_options(MEGEngine
            PRIVATE -fvisibility=hidden
    )
endif ()


# -----------------------------------------------------
# INCLUDE & LINKING
# -----------------------------------------------------

target_include_directories(MEGEngine PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/
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
        "${CMAKE_CURRENT_SOURCE_DIR}/resources/defaultSettings.json" # <-- in-file
        ${CMAKE_BINARY_DIR}                                  # <-- out-file path
)


# -----------------------------------------------------
# SUB-DIRECTORIES
# -----------------------------------------------------

option(BUILD_TESTS ON)
if(BUILD_TESTS STREQUAL "ON")
        message("-- BUILDING TESTS")
        add_subdirectory(tests)
endif()


# -----------------------------------------------------
# INSTALL
# -----------------------------------------------------

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(
    TARGETS MEGEngine
    EXPORT MEGEngineTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT MEGEngineTargets
    FILE MEGEngineTargets.cmake
    NAMESPACE MEGEngine::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MEGEngine
)

install(
    DIRECTORY inc/MEGEngine
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    DIRECTORY resources
    DESTINATION share/MEGEngine
)

configure_package_config_file(
    ${CMAKE_SOURCE_DIR}/cmake/MEGEngineConfig.cmake.in
    ${CMAKE_BINARY_DIR}/MEGEngineConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MEGEngine
)

install(
    FILES ${CMAKE_BINARY_DIR}/MEGEngineConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MEGEngine
)
