add_library(oalhslib STATIC oaLHS.cpp)

target_include_directories(oalhslib PUBLIC ${CMAKE_SOURCE_DIR}/bclib ${CMAKE_SOURCE_DIR}/oalib)
