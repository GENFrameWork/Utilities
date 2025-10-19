@echo off
setlocal EnableDelayedExpansion

rem Algebraic to RPN expressions converter
rem Reference: https://en.wikipedia.org/wiki/Shunting_yard_algorithm
rem Antonio Perez Ayala, 2023/01

cls

if /I "%RegionCode%" equ "LA" (
echo Convertidor de Expresiones Algebraicas a Notaci¢n Polaca Inversa (RPN^)
echo/
echo Ingrese expresiones algebraicas separando *cada elemento* por uno o m s
echo espacios, y separando las funciones de sus par‚ntesis izquierdos.
echo/
echo Los n£meros no pueden empezar con signo. No se permiten operaciones unarias.
echo/
echo Algunos ejemplos:
) else (
echo Algebraic Expression to Reverse Polish Notation (RPN^) converter
echo/
echo Enter algebraic expressions separating *each element* by one or more spaces,
echo and separating function name from its left parentheses.
echo/
echo Numbers can not start with minus sign and unary operators are not allowed.
echo/
echo Some examples:
)
echo    ( 4 + 5 ) / ( 6 + 7 )
echo    4 + sin ( 3.1416 * 8 ) * cos ( 3.1416 * 8 )
echo    sqrt ( 35 * 35 + 44 * 44 )

rem Initialize operators precedences
set "prec[(]=1"
set "prec[+]=2"
set "prec[-]=2"
set "prec[*]=3"
set "prec[/]=3"
set "prec[**]=4"
set "digits=0123456789"

:nextalgebraic
echo/
echo/
set "algebraic="
set /P "algebraic=Alg: "
if not defined algebraic goto :EOF

set /P "=RPN: " < NUL
set "operStack="

:nextToken
for /F "tokens=1*" %%a in ("%algebraic%") do set "token=%%a" & set "algebraic=%%b"

if "%token%" equ "(" (             rem Left paren: insert it in oper stack
   set "operStack=( %operStack%"
) else if "%token%" equ ")" (      rem Right paren: extract operators until "("
   call :ExtractLeftParen
) else if defined prec[%token%] (  rem Token is an operator
   call :InsertOperator
) else if "!digits:%token:~0,1%=!" neq "%digits%" (  rem Token is a number: output it
   set /P "=%token% " < NUL
) else (                           rem Token is a function
   for /F "tokens=1*" %%a in ("%algebraic%") do set "next=%%a" & set "algebraic=%%b"
   if "!next!" neq "(" set "algebraic="
   set "operStack=%token% ( %operStack%"
   if not defined algebraic echo/& echo Error: function "%token%" bad written & set "operStack="
)

if defined algebraic goto nextToken

rem At end: pop out all operators left in its stack
if defined operStack if "!operStack:(=!" neq "!operStack!" echo/& echo Error: Left paren with NO closing right paren
echo/%operStack%
goto nextalgebraic


:ExtractLeftParen

rem Extract previous operators until Left paren
if not defined operStack (
   echo/
   echo Error: Right paren with NO previous left paren
   set "algebraic="
   exit /B
)
for /F "tokens=1*" %%a in ("%operStack%") do (
   set "tos=%%a"
   set "operStack=%%b"
)
if "%tos%" neq "(" (
   set /P "=%tos% " < NUL
   goto ExtractLeftParen
)
exit /B


:InsertOperator

rem Extract previous operators with greater or equal precedence
for /F "tokens=1*" %%a in ("%operStack%") do (
   set "tos=%%a"
   set "rest=%%b"
)
if "!prec[%tos%]!" geq "!prec[%token%]!" (
   set /P "=%tos% " < NUL
   set "operStack=%rest%"
   if defined operStack goto InsertOperator
)

rem Insert new operator in the stack
set "operStack=%token% %operStack%"
exit /B

