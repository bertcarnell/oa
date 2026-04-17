add_executable(oatest COrthogonalArrayTest.cpp main.cpp matrixTest.cpp
               OATestClass.cpp primesTest.cpp runifTest.cpp rutilsTest.cpp 
               GaloisFieldTest.cpp)

target_include_directories(oatest PUBLIC ${CMAKE_SOURCE_DIR}/bclib ${CMAKE_SOURCE_DIR}/oalib)

target_link_libraries(oatest PUBLIC oalib)

