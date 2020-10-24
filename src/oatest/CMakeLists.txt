include_directories(${OA_SOURCE_DIR}/bclib)
include_directories(${OA_SOURCE_DIR}/oalib)

link_directories(${OA_SOURCE_DIR}/oalib)

add_executable(oatest COrthogonalArrayTest.cpp main.cpp matrixTest.cpp
               OATestClass.cpp primesTest.cpp runifTest.cpp rutilsTest.cpp 
               GaloisFieldTest.cpp)

target_link_libraries(oatest oalib)

