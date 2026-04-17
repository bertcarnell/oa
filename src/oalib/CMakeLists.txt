add_library(oalib STATIC ak3.cpp akconst.cpp akn.cpp construct.cpp
            COrthogonalArray.cpp GaloisField.cpp oa.cpp
            primes.cpp runif.cpp rutils.cpp)

target_include_directories(oalib PUBLIC ${CMAKE_SOURCE_DIR}/bclib)
