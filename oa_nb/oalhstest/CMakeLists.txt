include_directories(${OA_SOURCE_DIR}/bclib)
include_directories(${OA_SOURCE_DIR}/oalib)
include_directories(${OA_SOURCE_DIR}/oalhslib)
 
if (MSVC)
else (MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif (MSVC)
	
add_executable(oalhstest OaLHSTest.cpp
                      main.cpp)

link_directories(${OA_SOURCE_DIR}/oalib)
link_directories(${OA_SOURCE_DIR}/oalhslib)
target_link_libraries(oalhstest oalhslib oalib)
