include_directories(${OA_SOURCE_DIR}/bclib)
include_directories(${OA_SOURCE_DIR}/oalib)
include_directories(${OA_SOURCE_DIR}/oalhslib)
include_directories(${RCPP_INCLUDE_DIR})
include_directories(${R_INCLUDE_DIR})

link_directories(${OA_SOURCE_DIR}/oalib)
link_directories(${OA_SOURCE_DIR}/oalhslib)
link_directories(${RCPP_LINKER_DIR})
link_directories(${R_LINKER_DIR})

add_library(oa_r SHARED oa_r.cpp)

# order dependent, R is changed to -lR and finds libR.so
#  Rcpp was not handled properly, nor was RCPP_LIBRARY, -l:Rcpp.so is all that worked
target_link_libraries(oa_r R -l:Rcpp.so oalib oalhslib)
