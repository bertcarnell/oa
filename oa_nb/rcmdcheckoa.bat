:: Check the R build

echo *******
echo This check must be run as an administrator
echo *******

rm -rf .\oa\src-i386
rm -rf .\oa\src-x64
"c:\Program Files\R\R-3.0.1\bin\R.exe" CMD check oa

PAUSE
