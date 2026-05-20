
enable_testing()
find_package(GTest REQUIRED)

file(GLOB_RECURSE TEST_SOURCES *.cpp *.h *.hpp)

add_executable(MEGEngine_Tests ${TEST_SOURCES})
target_link_libraries(MEGEngine_Tests
    GTest::GTest
    GTest::Main
    MEGEngine
)
target_include_directories(MEGEngine_Tests
    PUBLIC inc
    PUBLIC ${CMAKE_SOURCE_DIR}/inc
)

add_custom_target(tests
    COMMAND tests/MEGEngine_Tests
    DEPENDS MEGEngine_Tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)