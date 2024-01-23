#!/bin/sh

date >> Output.txt
START_TIME=$(date +%s)


echo -------------------------------------------------------------
printf "Start process ... \n\n"


OUTFILE="../../../../../../Utilities/Batch/Output.txt"
export OUTFILE
echo -------------------------------------------------------------
printf "[Examples Linux PC x64]\n\n"

printf " * [Examples Base x64]\n\n"
sh ./internal/compile_linux.sh ../../Examples/Base/AppBaseExample/Platforms/Linux /x64 appbaseexample
sh ./internal/compile_linux.sh ../../Examples/Base/Canvas2DDisplay/Platforms/Linux /x64 canvas2ddisplay
sh ./internal/compile_linux.sh ../../Examples/Base/MemCtrlExample/Platforms/Linux /x64 memctrlexample
sh ./internal/compile_linux.sh ../../Examples/Base/NotAppExample/Platforms/Linux /x64 notappexample

printf " * [Examples Console x64]\n\n"
sh ./internal/compile_linux.sh ../../Examples/Console/BinConnPro/Platforms/Linux /x64 binconnpro
sh ./internal/compile_linux.sh ../../Examples/Console/Databases/Platforms/Linux /x64 databases
sh ./internal/compile_linux.sh ../../Examples/Console/MiniWebServer/Platforms/Linux /x64 miniwebserver
sh ./internal/compile_linux.sh ../../Examples/Console/ScriptsExample/Platforms/Linux /x64 scriptsexample 

printf " * [Examples Graphics x64]\n\n"
sh ./internal/compile_linux.sh ../../Examples/Graphics/Canvas2D/Platforms/Linux /x64 canvas2d
sh ./internal/compile_linux.sh ../../Examples/Graphics/UI_Options/Platforms/Linux /x64 ui_options


OUTFILE="../../../../../Utilities/Batch/Output.txt"
export OUTFILE
echo -------------------------------------------------------------
printf "[Test Linux PC x64]\n\n"

printf " * [Development tests x64]\n\n"
sh ./internal/compile_linux.sh ../../Tests/DevTestsConsole/Platforms/Linux /x64 devtestconsole
sh ./internal/compile_linux.sh ../../Tests/DevTestsDevices/Platforms/Linux /x64 devtestsdevices
sh ./internal/compile_linux.sh ../../Tests/DevTestsCanvas2D/Platforms/Linux /x64 devtestscanvas2D

printf " * [Unit tests x64]\n\n"
sh ./internal/compile_linux.sh ../../Tests/UnitTests/Platforms/Linux /x64 unit


OUTFILE="../../../../../Utilities/Batch/Output.txt"
export OUTFILE
echo -------------------------------------------------------------
printf "[Utilities x64]\n\n"
sh ./internal/compile_linux.sh ../../Utilities/APPUpdateCreator/Platforms/Windows \x64 appupdatecreator
sh ./internal/compile_linux.sh ../../Utilities/CompileBuilder/Platforms/Windows \x64 compilerbuilder


END_TIME=$(date +%s)
ELAPSED_TIME=$((END_TIME - START_TIME))
HOURS=$((ELAPSED_TIME / 3600))
MINUTES=$(((ELAPSED_TIME % 3600) / 60 ))
SECONDS=$((ELAPSED_TIME % 60))

echo -------------------------------------------------------------
printf "End process.\nProcessing time: %02d:%02d:%02d\n" "$HOURS" "$MINUTES" "$SECONDS"
echo -------------------------------------------------------------

