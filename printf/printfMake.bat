@echo off

\masm32\bin\ml /c /coff printfStorage.asm
if errorlevel 1 goto errasm

\masm32\bin\Link /SUBSYSTEM:CONSOLE /OPT:NOREF printf.obj GETARGS.obj printfStorage.obj
if errorlevel 1 goto errlink
echo printf.exe file successfully created
goto TheEnd

:errlink
echo/
echo Link error
goto TheEnd

:errasm
echo/
echo Assembly Error
echo Check your modifications of printfStorage.asm file!

:TheEnd
