:: copy oa library from oalib and oa_r to oa
cp ./oalib/*.h ./oa/src
cp ./oalib/*.cpp ./oa/src
cp ./oa_r/*.h ./oa/src
cp ./oa_r/*.cpp ./oa/src

:: copy boost files using bcp to a boost directory
"c:\Program Files\boost\boost_1_51\bin\bcp.exe" --scan --boost="..\..\boost" .\oa\src\CommonDefines.h .\oa\src

:: ensure only unix line endings
::"C:\MinGW\msys\1.0\bin\dos2unix.exe" ./oa/src/*.*
for /r "./oa/src" %%x in (*.cpp) do "C:\MinGW\msys\1.0\bin\dos2unix.exe" "%%x"
for /r "./oa/src" %%x in (*.h) do "C:\MinGW\msys\1.0\bin\dos2unix.exe" "%%x"

PAUSE
