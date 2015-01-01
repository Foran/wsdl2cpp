cmake_minimum_required(VERSION 2.6)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} /usr/include/libxml2)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -g -std=c++0x")

# Link runXSDUnitTests with what we want to test and the GTest, pthread and xml2 library
add_executable(runXSDUnitTests xsdUnitTests.cpp ../xsd.cpp ../xsdelement.cpp ../xsdsimpletype.cpp ../xsdcomplextype.cpp ../path.cpp)
target_link_libraries(runXSDUnitTests ${GTEST_LIBRARIES} pthread xml2)

# Link runWSDLUnitTests with what we want to test and the GTest, pthread and xml2 library
add_executable(runWSDLUnitTests wsdlUnitTests.cpp ../wsdl.cpp ../wsdlmessage.cpp ../wsdlmessagepart.cpp ../wsdloperation.cpp ../wsdlporttype.cpp ../xsd.cpp ../xsdelement.cpp ../xsdsimpletype.cpp ../xsdcomplextype.cpp ../path.cpp)
target_link_libraries(runWSDLUnitTests ${GTEST_LIBRARIES} pthread xml2)

# Link runPathUnitTests with what we want to test and the GTest and pthread library
add_executable(runPathUnitTests pathUnitTests.cpp ../path.cpp)
target_link_libraries(runPathUnitTests ${GTEST_LIBRARIES} pthread)

