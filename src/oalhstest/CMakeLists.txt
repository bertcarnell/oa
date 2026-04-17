add_executable(oalhstest OaLHSTest.cpp main.cpp)

target_include_directories(oalhstest PUBLIC ${CMAKE_SOURCE_DIR}/bclib ${CMAKE_SOURCE_DIR}/oalib ${CMAKE_SOURCE_DIR}/oalhslib)

target_link_libraries(oalhstest PUBLIC oalhslib oalib)
