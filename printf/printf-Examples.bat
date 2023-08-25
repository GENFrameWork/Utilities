@echo off
setlocal

rem Show several examples on printf.exe auxiliary program usage
rem Antonio Perez Ayala

rem Do NOT use 'more' on the output of this Batch file

mode CON: COLS=80 LINES=200
set "prompt=%~D0\> "
cls
echo on

rem Example session on printf.exe program features.

printf "A char: %%c, a string: %%s, an int: %%i, a float: %%f\n"  ^
                                 'X'       "Hello"         123      456.789

rem The format specification may be stored in a variable, with quotes,
rem but in this case the standard control characters can not be used:
set "format=A char: '%%c', a string: "%%s", an int: %%i, a float: %%f%%c"
printf format 'X' "Hello" 123 456.789  10

rem Characters are managed as 32-bits integers:
printf "Ascii code of '%%c' is %%i, char. of code %%i is '%%c'" 'A' 'A' 97 97

rem Management of 64-bits "long-long" integers:
printf "Wrong: int1: %%i, long-long1: %%i, long-long2: %%i, int2: %%i\n"  ^
                              123      9876543210           456ll       789
printf "Right: int1: %%i, long-long1: %%lli, long-long2: %%lli, int2: %%i\n"  ^
                          123        9876543210             456ll       789

rem Large integers and octal/hexadecimal notations:
printf "Dec: %%lld, Hex: %%lld, Oct: %%lld\n"  ^
                                    123456789012345678        0x123456789ABCDEF0    0123456712345671234567

rem Octal/hexadecimal output formats:
printf "Dec: %%lld, Hex: %%#llX, Oct: %%#llo\n"  ^
                                  123456789012345678       0x123456789ABCDEF0       0123456712345671234567

rem Largest signed and unsigned 64-bits integer numbers:
printf "Largest positive: %%lld, largest unsigned: %%llu\n"  ^
                                 0x7FFFFFFFFFFFFFFF      0xFFFFFFFFFFFFFFFF

rem Some examples of Reverse Polish Notation expressions:

printf "Number: %%lli, result: %%lli, number: %%lli"  12ll  34ll 56ll +  78ll

printf "Change sign of %%lli is equal to BitNOT the number plus 1: %%lli\n"  ^
                         12345ll                @ ~               1ll     +
printf "Max positive product: %%lli (%%#llX)\n" 0x7FFFFFFF 0x7FFFFFFF * @
printf "Max unsigned product: %%llu (%%#llX)\n" 0xFFFFFFFF 0xFFFFFFFF *u @
printf "%%lli divided by %%i is %%i plus %%i in remainder\n"  ^
                   123456789012345 ]     100000  [ 100000 /  [ 100000 %%

for /F "tokens=3" %%a in ('dir') do @set "free=%%a"
set "free=%free:,=%"
echo The free space on disk is:
printf "%%lld B = %%lld KB (+%%lldB) = %%lld MB (+%%lldKB) = %%lld GB (+%%lldMB)\n"  ^
%free%ll ] [ 0x3FFll ^& [ 10 ^>^> ] # [ 0x3FFll ^& [ 10 ^>^> ] # [ 10 ^>^> [ 0x3FFll ^&

rem Trick to avoid to escape all those special characters:
set "format=The free space on disk is:%%c%%lld B = %%lld KB (+%%lldB) = %%lld MB (+%%lldKB) = %%lld GB (+%%lldMB)%%c"
for /F "delims=" %%a in ("printf format 10 %free%ll ] [ 0x3FFll & [ 10 >> ] # [ 0x3FFll & [ 10 >> ] # [ 10 >> [ 0x3FFll & 10") do %%a

rem Example taken from:
rem http://stackoverflow.com/questions/35767361/
rem a-number-is-both-greater-and-less-than-another-in-a-windows-batch-file
set bakfilesize=399502220288
set freespace=463777075200
printf "baksize is %%.*s%%.*s\n" %bakfilesize% %freespace% - $ 1ll - ! ]  ^
   0 %% 6 * 0 %% "larger" [ ! 0 %% 16 * 0 %% "smaller or equal"

rem =======================
rem Floating point examples

printf "The result of (4+5)/(6+7) is: %%f\n"  4. 5. Add 6. 7. Add Div

printf "Square root(2)=%%f, Cubic root(64)=%%g, e=%%f, Sin(30)=%%g\n"  ^
                               2. Sqrt     64. 3. Inv Pow  1. Exp   30. Rad Sin

set /A X=4,Y=3
printf "Rectangular (X=%%i, Y=%%i) is Polar (Angle=%%g, Magnitude=%%g)\n"  ^
        %X% %Y%    %Y%. %X%. Div ATan Deg    %X%. X^^2 %Y%. X^^2 Add Sqrt

rem Some special values of the IEEE 754 floating-point specification:
printf "Minus zero: %%g, Infinite: %%g, NotANumber: %%g\n"  ^
                                   -1. 0. Mul     1. 0. Div        -2. Sqrt

rem Up to 8 floating-point numbers can be entered in the FPU stack:
printf "Enter 8 numbers: %%g %%g %%g %%g %%g %%g %%g %%g\n"  ^
                                                    1. 2. 3. 4. 5. 6. 7. 8.

rem If more numbers are entered, a FPU stack *error condition* happen:
printf "Enter 9 numbers: %%g %%g %%g %%g %%g %%g %%g %%g %%g\n"  ^
                                                 1. 2. 3. 4. 5. 6. 7. 8. 9.

rem ... or if the 8th number have a fractional part or exponent NEQ 0:
rem (because in this case an additional Power function must be performed)
printf "8th number use Pow function: %%g %%g %%g %%g %%g %%g %%g %%g\n"  ^
                                                    1. 2. 3. 4. 5. 6. 7. 8.5

rem The next functions cause the same error when the stack is full:
rem (because they use one additional FPU register to achieve its result)
rem     Frac, Tan, ASin, ACos, ATan, Ln, Log, Exp, ExpT
printf "Frac on 7th number OK: %%g %%g %%g %%g %%g %%g %%g\n"  ^
                                                       1. 2. 3. 4. 5. 6. 7.5 Frac
printf "Frac on 8th number fail: %%g %%g %%g %%g %%g %%g %%g %%g\n"  ^
                                                    1. 2. 3. 4. 5. 6. 7. 8.5 Frac

rem In order to *display* more numbers, use CLST (CLearSTack) function:
printf "Display 10 numbers: %%g %%g %%g %%g %%g %%g %%g %%g %%g %%g\n"  ^
                                              1. 2. 3. 4. 5. 6. 7. CLST 8.5 9. 10.
