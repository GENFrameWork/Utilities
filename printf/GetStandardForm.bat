 @echo off
setlocal DisableDelayedExpansion

rem GetStandardForm.bat: Auxiliary program for printf.exe application
rem Convert printf.exe "Didactic form" code into standard RPN form
rem Antonio Perez Ayala

if "%~1" neq "" if "%~1" neq "/?" goto begin

echo Extract the RPN standard form from printf.exe "Didactic Form" code
echo/
echo     GetStandardForm filename.bat
echo/
goto :EOF

:begin
if not exist "%~1" echo File not found: "%~1" & goto :EOF

set /P ^"=X^
% Do not remove this line %
=^" > equal.tmp < NUL
findstr /V "X" equal.tmp > equal.txt
del equal.tmp Form.tmp 2> NUL

< NUL ( for /F "usebackq delims=" %%a in ("%~1") do (
   set "line=%%a"
   setlocal EnableDelayedExpansion
   if "!line:/*=!" neq "!line!" (
      call :extractPart
      >> Form.tmp set /P "=!part! "
   ) else (
      if exist Form.tmp (
         type Form.tmp
         echo/
         del Form.tmp
      )
      echo !line!
   )
   endlocal
))
if exist Form.tmp (
   type Form.tmp
   echo/
   del Form.tmp
)
goto :EOF


:extractPart
for /F "delims=`" %%a in ("!line:/*=`!") do set "part=%%a"
set "part=!part:	= !"
set "part=!part:/"=!"
set "part=!part:printf =printf /" !"
:cut2spaces
set "prt=!part:  = !"
if "!prt!" neq "!part!" set "part=!prt!" & goto cut2spaces
if "!part:~-1!" equ " " set "part=!part:~0,-1!"
if "!part:~0,1!" equ " " set "part=!part:~1!"
:equal
if "!part:~0,1!" equ "=" type equal.txt >> Form.tmp & set "part=!part:~1!" & goto equal
exit /B

