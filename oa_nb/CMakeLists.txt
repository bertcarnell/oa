cmake_minimum_required(VERSION 2.8)
project(OA)

set(CMAKE_CXX_FLAGS "-g -std=c++0x -m64 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g -std=c++0x -m64 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -std=c++0x -m64 -Wall")
set(CMAKe_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -std=c++0x -m64 -Wall")

add_subdirectory(oalib)
add_subdirectory(oatest)
add_subdirectory(oalhslib)
add_subdirectory(oalhstest)
#add_subdirectory(oa_r) # don't add this one because of the R requirement not on drone.io
