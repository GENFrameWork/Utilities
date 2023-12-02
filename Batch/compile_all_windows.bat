@echo off
call erase_all_windows.bat
set vctype=%1
if "%vctype%"=="" (set vctype=Enterprise)
echo %DATE% %TIME% >> Output.txt
for /f "tokens=1-4 delims=:.," %%a in ("%time%") do (
    set /a "start_time=(((%%a*60+1%%b %% 100)*60+1%%c %% 100)*100+1%%d %% 100)"
)


echo -------------------------------------------------------------
..\printf\printf "Start process ... \n\n"


set "OUTFILE=..\..\..\..\..\..\Utilities\Batch\Output.txt"
set "PRINTF=..\..\..\..\..\..\Utilities\printf\printf"
call "C:\Program Files\Microsoft Visual Studio\2022\%vctype%\VC\Auxiliary\Build\vcvarsall.bat" amd64_x86
..\printf\printf "\n"
echo -------------------------------------------------------------
..\printf\printf "[Examples Windows PC x32]\n\n"

..\printf\printf " * [Examples Base x32]\n\n"
call internal/compile_windows.bat ../../Examples/Base/NotAppExample/Platforms/Windows /x32 notappexample
call internal/compile_windows.bat ../../Examples/Base/AppBaseExample/Platforms/Windows /x32 appbaseexample
call internal/compile_windows.bat ../../Examples/Base/MemCtrlExample/Platforms/Windows /x32 memctrlexample
call internal/compile_windows.bat ../../Examples/Base/Canvas2DDisplay/Platforms/Windows /x32 canvas2ddisplay

..\printf\printf " * [Examples Console x32]\n\n"
call internal/compile_windows.bat ../../Examples/Console/BinConnPro/Platforms/Windows /x32 binconnpro
call internal/compile_windows.bat ../../Examples/Console/Databases/Platforms/Windows /x32 databases
call internal/compile_windows.bat ../../Examples/Console/MiniWebServer/Platforms/Windows /x32 miniwebserver
call internal/compile_windows.bat ../../Examples/Console/ScriptsExample/Platforms/Windows /x32 scriptsexample 

..\printf\printf " * [Examples Graphics x32]\n\n"
call internal/compile_windows.bat ../../Examples/Graphics/Canvas2D/Platforms/Windows /x32 canvas2d
call internal/compile_windows.bat ../../Examples/Graphics/UI_Options/Platforms/Windows /x32 ui_options


set "OUTFILE=..\..\..\..\..\Utilities\Batch\Output.txt"
set "PRINTF=..\..\..\..\..\Utilities\printf\printf"
..\printf\printf "[Tests Windows PC x32]\n\n"

..\printf\printf " * [Development tests x32]\n\n"
call internal/compile_windows.bat ../../Tests/DevTestsConsole/Platforms/Windows \x32 devtestsconsole
call internal/compile_windows.bat ../../Tests/DevTestsDevices/Platforms/Windows \x32 devtestsdevices
call internal/compile_windows.bat ../../Tests/DevTestsCanvas2D/Platforms/Windows \x32 devtestscanvas2d

..\printf\printf " * [Unit tests x32]\n\n"
call internal/compile_windows.bat ../../Tests/UnitTests/Platforms/Windows \x32 unit     
                          
      
set "OUTFILE=..\..\..\..\..\..\Utilities\Batch\Output.txt"
set "PRINTF=..\..\..\..\..\..\Utilities\printf\printf"
call "C:\Program Files\Microsoft Visual Studio\2022\%vctype%\VC\Auxiliary\Build\vcvarsall.bat" amd64  
..\printf\printf "\n"
echo -------------------------------------------------------------
..\printf\printf "[Examples Windows PC x64]\n\n"

..\printf\printf " * [Examples Base Windows PC x64]\n\n"
call internal/compile_windows.bat ../../Examples/Base/NotAppExample/Platforms/Windows /x64 notappexample
call internal/compile_windows.bat ../../Examples/Base/AppBaseExample/Platforms/Windows /x64 appbaseexample
call internal/compile_windows.bat ../../Examples/Base/MemCtrlExample/Platforms/Windows /x64 memctrlexample
call internal/compile_windows.bat ../../Examples/Base/Canvas2DDisplay/Platforms/Windows /x64 canvas2ddisplay

..\printf\printf " * [Examples Console Windows PC x64]\n\n"
call internal/compile_windows.bat ../../Examples/Console/BinConnPro/Platforms/Windows /x64 binconnpro
call internal/compile_windows.bat ../../Examples/Console/Databases/Platforms/Windows /x64 databases
call internal/compile_windows.bat ../../Examples/Console/MiniWebServer/Platforms/Windows /x64 miniwebserver
call internal/compile_windows.bat ../../Examples/Console/ScriptsExample/Platforms/Windows /x64 scriptsexample 

..\printf\printf " * [Examples Graphics Windows PC x64]\n\n"
call internal/compile_windows.bat ../../Examples/Graphics/Canvas2D/Platforms/Windows /x64 canvas2d
call internal/compile_windows.bat ../../Examples/Graphics/UI_Options/Platforms/Windows /x64 ui_options
   
set "OUTFILE=..\..\..\..\..\Utilities\Batch\Output.txt"
set "PRINTF=..\..\..\..\..\Utilities\printf\printf"   
..\printf\printf "[Tests Windows PC x64]\n\n"

..\printf\printf " * [Development tests x64]\n\n"                                                  
call internal/compile_windows.bat ../../Tests/DevTestsConsole/Platforms/Windows \x64 devtestsconsole
call internal/compile_windows.bat ../../Tests/DevTestsDevices/Platforms/Windows \x64 devtestsdevices
call internal/compile_windows.bat ../../Tests/DevTestsCanvas2D/Platforms/Windows \x64 devtestscanvas2d

..\printf\printf " * [Unit tests x64]\n\n"
call internal/compile_windows.bat ../../Tests/UnitTests/Platforms/Windows \x64 unit



for /f "tokens=1-4 delims=:.," %%a in ("%time%") do (
    set /a "end_time=(((%%a*60+1%%b %% 100)*60+1%%c %% 100)*100+1%%d %% 100)"
)

set /a "elapsed_time=end_time - start_time"
set /a "hours=elapsed_time / 360000"
set /a "minutes=(elapsed_time %% 360000) / 6000"
set /a "seconds=(elapsed_time %% 6000) / 100"

echo -------------------------------------------------------------
.\..\printf\printf "End process.\nProcessing time: %%02d:%%02d:%%02d\n"  %hours% %minutes% %seconds%
echo -------------------------------------------------------------
pause
