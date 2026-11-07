
enable_testing()
find_package(GTest REQUIRED)

file(GLOB_RECURSE TEST_SOURCES src/*.cpp src/*.c)

add_executable(MEGEngine_Tests ${TEST_SOURCES})
target_link_libraries(MEGEngine_Tests
    GTest::gtest
    GTest::gmock
    GTest::Main
    MEGEngine
)
target_include_directories(MEGEngine_Tests PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

add_custom_target(tests
    COMMAND engine/tests/MEGEngine_Tests
    DEPENDS MEGEngine_Tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)