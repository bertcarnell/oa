rm -rf cmakebuild
mkdir cmakebuild
cd cmakebuild

IF "%1"=="MinGW" (GOTO :section1) ELSE (GOTO :section2)

:section1

set path=%path:c:\Rtools\bin;=%

"c:\Program Files (x86)\CMake 2.8\bin\cmake.exe" -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=C:/Rtools/gcc-4.6.3/bin/g++.exe -DCMAKE_BUILD_TYPE=Debug ..

"C:\MinGW\bin\mingw32-make.exe"

oatest\oatest.exe
oalhstest\oalhstest.exe

PAUSE
EXIT

:section2

"c:\Program Files (x86)\CMake 2.8\bin\cmake.exe" -G "Visual Studio 12" ..

"C:\Program Files (x86)\MSBuild\12.0\Bin\msbuild.exe" OA.sln /t:Rebuild /p:Configuration=Debug

oatest\Debug\oatest.exe
oalhstest\Debug\oalhstest.exe

PAUSE
EXIT
