cmake_minimum_required(VERSION 3.2)
project(helloworld)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} helloworld.cpp PrimeChecker.cpp)

enable_testing()
add_executable(${PROJECT_NAME}-Runner TestPrimeChecker.cpp PrimeChecker.cpp)
add_test(NAME ${PROJECT_NAME}-Runner COMMAND ${PROJECT_NAME}-Runner)