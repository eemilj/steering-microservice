cmake_minimum_required(VERSION 3.2)
project(helloworld)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -Werror -fprofile-arcs -ftest-coverage")

# Set the sources
set(SOURCES
        helloworld.cpp
        PrimeChecker.cpp
        )

# Create the executable
add_executable(helloworld ${SOURCES})

# Create the gcov target. Run coverage tests with 'make gcov'
add_custom_target(gcov COMMAND mkdir -p coverage
        COMMAND make test
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
add_custom_command(TARGET gcov
        COMMAND gcov -b ${CMAKE_SOURCE_DIR}/*.cpp
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
        )
add_dependencies(gcov helloworld)

# Make sure to clean up the coverage folder
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES coverage)

# Create the gcov-clean target. This cleans the build as well as generated
# .gcda and .gcno files.
add_custom_target(scrub
        COMMAND ${CMAKE_MAKE_PROGRAM} clean
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )

# Testing
enable_testing()
add_executable(${PROJECT_NAME}-Runner
        TestPrimeChecker.cpp
        PrimeChecker.cpp
        )
add_test(NAME ${PROJECT_NAME}-Runner COMMAND ${PROJECT_NAME}-Runner)
