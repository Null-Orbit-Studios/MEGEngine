cmake_minimum_required(VERSION 4.2)
project(MEGEngineProject)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# -----------------------------------------------------
# SUB-DIRECTORIES
# -----------------------------------------------------

add_subdirectory(engine)

option(BUILD_EXAMPLES ON)
if(BUILD_EXAMPLES STREQUAL "ON")
        message("-- BUILDING EXAMPLES")
        add_subdirectory(games)
endif()
