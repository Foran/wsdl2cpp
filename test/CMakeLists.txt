cmake_minimum_required(VERSION 2.6)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} /usr/include/libxml2)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -g -std=c++0x")

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests tests.cpp ../xsd.cpp ../xsdelement.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread xml2)
