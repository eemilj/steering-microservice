cmake_minimum_required(VERSION 3.2)
project(SteeringMicroservice)

################################################################################
# Defining the relevant versions of OpenDLV Standard Message Set and libcluon.
# The OpenDLV Standard Message Set contains a set of messages usually used in automotive research project.
set(OPENDLV_STANDARD_MESSAGE_SET src/opendlv-standard-message-set-v0.9.6.odvd)
# libcluon is a small and portable middleware to easily realize high-performance microservices with C++: https://github.com/chrberger/libcluon
set(CLUON_COMPLETE src/cluon-complete-v0.0.127.hpp)

################################################################################
# Set the search path for .cmake files.
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# Build a static binary.
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
# Add further warning levels to increase the code quality.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    -D_XOPEN_SOURCE=700 \
    -D_FORTIFY_SOURCE=2 \
    -O2 \
    -fprofile-arcs \
    -ftest-coverage \
    -fstack-protector \
    -fomit-frame-pointer \
    -pipe \
    -Weffc++ \
    -Wall -Wextra -Wshadow -Wdeprecated \
    -Wdiv-by-zero -Wfloat-equal -Wfloat-conversion -Wsign-compare -Wpointer-arith \
    -Wuninitialized -Wunreachable-code \
    -Wunused -Wunused-function -Wunused-label -Wunused-parameter -Wunused-but-set-parameter -Wunused-but-set-variable \
    -Wunused-value -Wunused-variable -Wunused-result \
    -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Werror")

# Threads are necessary for linking the resulting binaries as the network communication is running inside a thread.
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

################################################################################
# Extract cluon-msc from cluon-complete.hpp.
# cluon-msc is the message compiler that compiles a .odvd message specification into a header-only C++ file.
add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/cluon-msc
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/${CLUON_COMPLETE} ${CMAKE_BINARY_DIR}/cluon-complete.hpp
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/cluon-complete.hpp ${CMAKE_BINARY_DIR}/cluon-complete.cpp
        COMMAND ${CMAKE_CXX_COMPILER} -o ${CMAKE_BINARY_DIR}/cluon-msc ${CMAKE_BINARY_DIR}/cluon-complete.cpp -std=c++14 -pthread -D HAVE_CLUON_MSC
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${CLUON_COMPLETE})

################################################################################
# Generate opendlv-standard-message-set.hpp from ${OPENDLV_STANDARD_MESSAGE_SET} file.
add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/opendlv-standard-message-set.hpp
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${CMAKE_BINARY_DIR}/cluon-msc --cpp --out=${CMAKE_BINARY_DIR}/opendlv-standard-message-set.hpp ${CMAKE_CURRENT_SOURCE_DIR}/${OPENDLV_STANDARD_MESSAGE_SET}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${OPENDLV_STANDARD_MESSAGE_SET} ${CMAKE_BINARY_DIR}/cluon-msc)
# Add current build directory as include directory as it contains generated files.
include_directories(SYSTEM ${CMAKE_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

################################################################################
# Gather all object code first to avoid double compilation.
set(LIBRARIES Threads::Threads)

if(UNIX)
    if(NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
        find_package(LibRT REQUIRED)
        set(LIBRARIES ${LIBRARIES} ${LIBRT_LIBRARIES})
        include_directories(SYSTEM ${LIBRT_INCLUDE_DIR})
    endif()
endif()

# This project uses OpenCV for image processing.
find_package(OpenCV REQUIRED core highgui imgproc)
include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS})
set(LIBRARIES ${LIBRARIES} ${OpenCV_LIBS})

################################################################################
# Create executable.
FILE(GLOB SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SRCFILES})

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

# Add dependency to OpenDLV Standard Message Set.
add_custom_target(generate_opendlv_standard_message_set_hpp DEPENDS ${CMAKE_BINARY_DIR}/opendlv-standard-message-set.hpp)
add_dependencies(${PROJECT_NAME} generate_opendlv_standard_message_set_hpp)

################################################################################
# Install executable.
install(TARGETS ${PROJECT_NAME} DESTINATION bin COMPONENT ${PROJECT_NAME})

# Create the gcov target. Run coverage tests with 'make gcov'
add_custom_target(gcov COMMAND mkdir -p coverage
        COMMAND make test
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
add_custom_command(TARGET gcov
        COMMAND gcov -b ${CMAKE_SOURCE_DIR}/*.cpp
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
        )
add_dependencies(gcov SteeringMicroservice)

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
        test/ImageProcessorTester.cpp
        src/ImageProcessor.cpp
        src/ConeDetector.cpp
        src/ImageRecognitionController.cpp
        src/SteeringAngleCalculator.cpp
        src/IOHandler.cpp
        test/ConeDetectorTester.cpp
        test/IOHandlerTester.cpp
        test/SteeringAngleCalculatorTester.cpp
        test/ImageRecognitionControllerTester.cpp)
target_link_libraries(${PROJECT_NAME}-Runner ${LIBRARIES})
add_test(NAME ${PROJECT_NAME}-Runner COMMAND ${PROJECT_NAME}-Runner)