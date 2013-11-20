echo off

:: Rtools uses CYGWIN for these file operations
set CYGWIN=nodosfilewarning
:: Deploy to lhs repository at r-forge.r-project.org
:: change this destination to match your path
set DESTINATION=C:\Users\carnellr\Documents\Repositories\lhs\admin\pkg\oalhs\src
:: dos2unix
set DOS2UNIX="C:\MinGW\msys\1.0\bin\dos2unix.exe"

:: copy oa library from oalib and oa_r to oalhs
echo ****
echo **** copying sources ****
echo ****
cp ./oalib/*.h %DESTINATION%
cp ./oalib/*.cpp %DESTINATION%
cp ./oa_r/*.h %DESTINATION%
cp ./oa_r/*.cpp %DESTINATION%

:: ensure only unix line endings
::"C:\MinGW\msys\1.0\bin\dos2unix.exe" ./oa/src/*.*
echo ****
echo **** dos2unix ****
echo ****
for /r "%DESTINATION%" %%x in (*.cpp) do %DOS2UNIX% "%%x"
for /r "%DESTINATION%" %%x in (*.h) do %DOS2UNIX% "%%x"

echo on

PAUSE
