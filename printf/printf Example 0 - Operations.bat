@echo off
setlocal EnableDelayedExpansion

rem Show several examples on printf.exe program usage
rem Antonio Perez Ayala

rem Create the standard control characteres in same-named variables

REM \b (Back Space): ASCII 8
for /F %%a in ('echo prompt $H ^| cmd') do set "\b=%%a"

REM \t (Tab): ASCII 9
rem First, try the old method for Windows XP
for /F "skip=4 delims=pR tokens=2" %%a in (
       'reg query hkcu\environment /v temp' ) do set "\t=%%a"
rem Then, the method for newer versions
for /F "tokens=2 delims=0" %%a in ('shutdown /? ^| findstr /BC:E') do if not defined \t set "\t=%%a"

REM \n "new line" (Line Feed): ASCII 10
set \n=^
%don't remove%
%these lines%

REM \r (Carriage Return): ASCII 13
for /F %%a in ('copy /Z "%~F0" NUL') do set "\r=%%a"

rem Do NOT use 'more' on the output of this Batch file

mode CON: COLS=80 LINES=200
set "prompt=%~D0\> "
cls
echo on

rem Example session on printf.exe program features
rem ==============================================

printf "A char: %%c, a string: %%s, an int: %%i, a float: %%f\n"  ^
                                 'X'       "Hello"         123      456.789

rem The format specification can be stored in a variable, but
rem standard control characters must be inserted using !DelayedExpansion!
rem on same-named variables that were created previously

set "format=!\t!TAB, Back !\b!Space, !\r!CR!\n!"
printf format

rem Characters are managed as 32-bits integers:
printf "Ascii code of '%%c' is %%i. Code %%i is char '%%c'\n" 'A' 'A' 97 97

rem
rem Integer examples
rem ================

rem Octal/hexadecimal output formats:
printf "Dec: %%d, Hex: %%#X, Oct: %%#o\n"  ^
                                             1234567890    1234567890   1234567890

rem Octal/hexadecimal number notations:
printf "Dec: %%d, Hex: %%d, Oct: %%d\n"  ^
                                               1234567890   0x499602D2   011145401322

rem Largest signed and unsigned 32-bits integer numbers:
printf "Largest positive: %%d, largest unsigned: %%u\n"  ^
                                           0x7FFFFFFF            0xFFFFFFFF

rem Some examples of Reverse Polish Notation expressions:

printf "Number: %%i, result: %%i, number: %%i\n"  12  34 56 +  78

printf "Change sign of %%i is equal to BitNOT the number plus 1: %%i\n"  ^
                             12345           ^>      ~                 1   +
printf "Max positive square (product): %%i (%%#X)\n" 46340 ^> * ^>
printf "Max unsigned square (product): %%u (%%#X)\n" 65535 ^> *u ^>
printf "%%i divided by %%i is %%i plus %%i in remainder\n"  ^
                        1234567890 ]1      100000  [1 100000 /  [1 100000 %%

rem
rem Floating point examples
rem =======================

printf "The result of (4+5)/(6+7) is: %%f\n"  4. 5. Add 6. 7. Add Div

printf "Square root(2)=%%f, Cubic root(64)=%%g, e=%%f, Sin(30)=%%g\n"  ^
                               2. Sqrt     64. 3. Inv Pow  1. Exp    30. Rad Sin

set /A X=4,Y=3
rem Data below is:
REM    %%X%% %%Y%%   %%Y%%. %%X%%. Div ATan Deg  %%X%%. Sqr %%Y%%. Sqr Add Sqrt

printf "Rectangular (X=%%i, Y=%%i) is Polar (Angle=%%g, Magnitude=%%g)\n"  ^
                       %X% %Y%    %Y%. %X%. Div ATan Deg    %X%. Sqr %Y%. Sqr Add Sqrt

rem Some special values of the IEEE 754 floating-point specification:
printf "Minus zero: %%g, Infinite: %%g, -Infinite: %%g, NotANumber: %%g\n"  ^
                    -1. 0. Mul     1. 0. Div     -1. 0. Div        -2. Sqrt

rem Up to 8 floating-point numbers can be entered in the FPU stack:
printf "Enter 8 numbers: %%g %%g %%g %%g %%g %%g %%g %%g\n"  ^
                                                    1. 2. 3. 4. 5. 6. 7. 8.

rem If more numbers are entered, a FPU stack *error condition* happen:
printf "Enter 9 numbers: %%g %%g %%g %%g %%g %%g %%g %%g %%g\n"  ^
                                                 1. 2. 3. 4. 5. 6. 7. 8. 9.

rem ... or if the 8th number have a fractional part or Exponent NEQ 0:
rem (because in this case an additional Power function must be performed)
printf "8th number use Pow function: %%g %%g %%g %%g %%g %%g %%g %%g\n"  ^
                                                    1. 2. 3. 4. 5. 6. 7. 8.5

rem The next functions cause the same error when the stack is full:
rem (because they use one additional FPU register to get the result)
rem     Frac, Tan, ASin, ACos, ATan, Ln, Log, Exp, ExpT
printf "Frac on 7th number OK: %%g %%g %%g %%g %%g %%g %%g\n"  ^
                                                       1. 2. 3. 4. 5. 6. 7.5 Frac
printf "Frac on 8th number fail: %%g %%g %%g %%g %%g %%g %%g %%g\n"  ^
                                                    1. 2. 3. 4. 5. 6. 7. 8.5 Frac

rem In order to *display* more numbers, use INIT (Init FPU) function:
printf "Display 10 numbers: %%g %%g %%g %%g %%g %%g %%g %%g %%g %%g\n"  ^
                                        1. 2. 3. 4. 5. 6. 7. INIT 8.5 9. 10.
rem ... but numbers before the INIT were *deleted* from FPU stack:
printf "Add last 3 numbers OK: %%g %%g %%g %%g %%g %%g %%g %%g\n"  ^
                                        1. 2. 3. 4. 5. 6. 7. INIT 8.5 9. 10. Add Add
printf "Add last 4 numbers fail: %%g %%g %%g %%g %%g %%g %%g\n"  ^
                                        1. 2. 3. 4. 5. 6. 7. INIT 8.5 9. 10. Add Add  ADD
rem End of example
