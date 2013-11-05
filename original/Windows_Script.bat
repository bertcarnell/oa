::REM to extract the files from oa_c.txt

:: c:\Rtools\bin\sh.exe oa_c.txt

::REM to run the Makefile you must be an administrator
:: Startbar -> accessories -> right click command prompt -> run as administraor
:: cd c:\Users\carnellr\Documents\Repositories\oa\original

c:\Rtools\bin\make.exe -f Makefile_win cleanup
c:\Rtools\bin\make.exe -f Makefile_win all

