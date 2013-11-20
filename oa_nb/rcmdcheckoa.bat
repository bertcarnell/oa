:: Check the R build

echo off
echo *******
echo This check must be run as an administrator
echo *******

set CYGWIN=nodosfilewarning

echo ****
echo **** removing old checks ****
echo ****
rm -rf .\oa\src-i386
rm -rf .\oa\src-x64

echo ****
echo **** R CMD check oa ****
echo **** 
"c:\Program Files\R\R-3.0.1\bin\R.exe" CMD check oa

echo on

PAUSE
