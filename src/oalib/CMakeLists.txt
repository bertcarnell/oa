include_directories(${OA_SOURCE_DIR}/bclib)

add_library(oalib STATIC ak3.cpp akconst.cpp akn.cpp construct.cpp
            COrthogonalArray.cpp GaloisField.cpp oa.cpp
            primes.cpp runif.cpp rutils.cpp)

