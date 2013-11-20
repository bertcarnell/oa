
echo off

set CYGWIN=nodosfilewarning

:: copy oa library from oalib and oa_r to oa
echo ****
echo **** copying sources ****
echo ****
cp ./oalib/*.h ./oa/src
cp ./oalib/*.cpp ./oa/src
cp ./oa_r/*.h ./oa/src
cp ./oa_r/*.cpp ./oa/src

:: ensure only unix line endings
::"C:\MinGW\msys\1.0\bin\dos2unix.exe" ./oa/src/*.*
echo ****
echo **** dos2unix ****
echo ****
for /r "./oa/src" %%x in (*.cpp) do "C:\MinGW\msys\1.0\bin\dos2unix.exe" "%%x"
for /r "./oa/src" %%x in (*.h) do "C:\MinGW\msys\1.0\bin\dos2unix.exe" "%%x"

echo on

PAUSE

