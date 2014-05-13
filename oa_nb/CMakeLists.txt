cmake_minimum_required(VERSION 2.8)
project(OA)

if (MSVC)
    # disable unreferenced formal parameters and constant conditional expression
	set(CMAKE_CXX_FLAGS "/EHsc /W4 /WX /wd4100;4127")
	set(CMAKE_CXX_FLAGS_DEBUG "/Od")
	set(CMAKE_CXX_FLAGS_RELEASE "/O3")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/O2")
else (MSVC)
	set(CMAKE_CXX_FLAGS "-m64 -Wall -Werror")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2")
endif (MSVC)

add_subdirectory(oalib)
add_subdirectory(oatest)
add_subdirectory(oalhslib)
add_subdirectory(oalhstest)
#add_subdirectory(oa_r) # don't add this one because of the R requirement not on drone.io
