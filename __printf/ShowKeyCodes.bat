@echo off
setlocal EnableDelayedExpansion
rem ShowKeyCodes.bat - Show variables defined by DefineKeyCodes subroutine

rem Store current variables in vars.txt
(for /F "delims==" %%a in ('set') do (
   echo %%a
)) > "vars.txt"

call :DefineKeyCodes

rem Show new variables that are not in vars.txt
set "a=a"
< "vars.txt" (
for /F "tokens=1* delims==" %%a in ('set') do (
   if "!a!" equ "%%a" (
      set /P "a="
   ) else (
      echo %%a=%%b
   )
)) > "vars2.txt"
more "vars2.txt"
del "vars.txt" "vars2.txt"
echo/
pause
goto :EOF


:DefineKeyCodes
@echo off
rem DefineKeyCodes.bat - Definition of key codes via key names
rem Antonio Perez Ayala

rem Modify "i" and "Alt_" variables.
rem Can not use Setlocal because the purpose is to create global variables

for %%a in ("BackSpace=8" "TabKey=9" "Ctrl_Enter=10" "EnterKey=13" "EscKey=27" "Ctrl_@=-3") do (
   set %%a
)

rem Codes are defined in the physical order of keyboard keys
set i=-14
for %%a in (Alt_BackSpace Shift_Tab) do (
   set /A "%%a=i, i-=1"
)
rem Currently: i=-16
for %%a in (Q W E R T Y U I O P LeftBracket RightBracket) do (
   set /A "Alt_%%a=i, i-=1"
)
set i=-30
for %%a in (A S D F G H J K L Semicolon Apostrophe BackQuote) do (
   set /A "Alt_%%a=i, i-=1"
)
set i=-43
for %%a in (BackSlash Z X C V B N M Comma Dot Slash "" GrayStar) do (
   set /A "Alt_%%~a=i, i-=1"
)
set i=-59
for %%a in (F1 F2 F3 F4 F5 F6 F7 F8 F9 F10) do (
   set /A "%%a=i, i-=1"
)
set i=-71
for %%a in (HomeKey UpArrow PageUp Alt_GrayDash LeftArrow KeyPad5 RightArrow
            Alt_GrayPlus EndKey DownArrow PageDown InsKey DelKey) do (
   set /A "%%a=i, i-=1"
)
rem Currently: i=-84
for %%a in (Shift Ctrl Alt) do (
   for %%b in (F1 F2 F3 F4 F5 F6 F7 F8 F9 F10) DO (
      set /A "%%a_%%b=i, i-=1"
   )
)
rem Currently: i=-114
for %%a in (PrtSc LeftArrow RightArrow End PageDown Home) do (
   set /A "Ctrl_%%a=i, i-=1"
)
rem Currently: i=-120
for %%a in (1 2 3 4 5 6 7 8 9 0 Dash Equal Ctrl_PageUp) do (
   set /A "Alt_%%a=i, i-=1"
)
rem Original IBM-PC keyboard have not F11 nor F12 keys
rem Currently: i=-133
for %%a in (F11 F12 Shift_F11 Shift_F12 Ctrl_F11 Ctrl_F12 Alt_F11 Alt_F12) do (
   set /A "%%a=i, i-=1"
)
rem Currently: i=-141
for %%a in (UpArrow GrayDash KeyPad5 GrayPlus DownArrow Ins Del Tab GraySlash GrayStar) do (
   set /A "Ctrl_%%a=i, i-=1"
)
rem Currently: i=-151
for %%a in (Home UpArrow PageUp "" LeftArrow KeyPad5 RightArrow "" End
            DownArrow PageDown Ins Del GraySlash) do (
   set /A "Alt_%%~a=i, i-=1"
)
set "Alt_="
set "i="
exit /B

rem DefineKeyCodes.bat - End of file
