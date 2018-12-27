include_directories(${OA_SOURCE_DIR}/bclib)
include_directories(${OA_SOURCE_DIR}/oalib)
include_directories(${OA_SOURCE_DIR}/oalhslib)

link_directories(${OA_SOURCE_DIR}/oalib)
link_directories(${OA_SOURCE_DIR}/oalhslib)
 
add_executable(oalhstest OaLHSTest.cpp main.cpp)

target_link_libraries(oalhstest oalhslib oalib)

