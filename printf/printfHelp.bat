@echo off
setlocal EnableDelayedExpansion

rem printf.exe v.2 On-screen help
rem Antonio Perez Ayala, January/2023

set "help=help" & set "errors=errors"
if /I "%RegionCode%" == "LA" set "help=LAhelp" & set "errors=LAerrors" & chcp 850 > NUL

if "%~1" neq "" (
   call :showError %1 < "%~F0" > "%~F0.txt"
   more "%~F0.txt"
   del "%~F0.txt"
   goto :EOF
)

set "skip="
for /F "delims=:" %%a in ('findstr /N /B ":%help%" "%~F0"') do (
   if not defined skip (
      set "skip=%%a"
   ) else (
      set /A "copy=%%a-skip-1"
   )
)

call :showHelp < "%~F0"
set /A nM2=n-2
:nextHelp
   choice /C %options%0 /N /M "%site[0]% "
   if errorlevel %n% goto :EOF
   if errorlevel %nM2% (
      !site[%errorlevel%]!
   ) else (
      explorer !site[%errorlevel%]!
   )
goto nextHelp


:showHelp
for /L %%# in (1,1,%skip%) do set /P "="

for /L %%# in (1,1,%copy%) do (
   set "line="
   set /P "line="
   if "!line!" == "pause" (
      pause < CON
   ) else (
      echo/!line!
   )
)
set /P "="

set "n=0" & set "options="
:nextSite
   set /P "site[%n%]="
   if not defined site[%n%] exit /B
   if %n% gtr 0 set "options=%options%%n%"
   set /A n+=1
goto nextSite

==========================================

:showError
for /F "delims=:" %%a in ('findstr /N /B ":%errors%" "%~F0"') do set "skip=%%a"
for /L %%# in (1,1,%skip%) do set /P "="

set "n=0"
set /P "line="
if %1 neq 0 goto nextError

echo/
if /I "%RegionCode%" equ "LA" (
echo Cuando un error ocurre en un programa, printf.exe lo cancela, muestra un
echo mensaje de error y termina con un n£mero negativo de error en ERRORLEVEL.
echo/
echo En seguida se describen los posibles mensajes de error y sus n£meros:
) else (
echo When an error happens in a RPN program, printf.exe cancel it, show an error
echo message and terminate with a negative error number in ERRORLEVEL variable.
echo/
echo The possible error messages and their numbers are described below:
)

:nextError
   set /A n-=1
   if %1 equ 0 (
      echo/
      echo %n% !line:~4!
   )
   :nextLine
      set "line="
      set /P "line="
      if not defined line goto endErrors
      if "!line:~0,3!" equ "[*]" goto endLines
      if %1 equ 0 (
         echo !line!
      ) else if %1 equ %n% (
         echo !line!
      )
   goto nextLine
   :endLines
goto nextError
:endErrors
if %1 neq 0 exit /B
echo/
if /I "%RegionCode%" equ "LA" (
echo Despu‚s que printf.exe muestre un mensaje de error, usted puede mostrar la
echo descripci¢n completa del error ejecutando esta l¡nea:
echo/
echo     printfHelp %%errorlevel%%
echo/
echo Puede insertar esta l¡nea en el archivo ERR.BAT y entonces s¢lo ejecutar: ERR
) else (
echo After printf.exe show an error message, you can show its corresponding
echo description executing this line:
echo/
echo     printfHelp %%errorlevel%%
echo/
echo You can insert this line in an ERR.BAT file and then just execute: ERR
)
exit /B

================================

:help
Emulates printf C run-time function and evaluates RPN arithmetic expressions.

    printf "format" {number [operator]|'c'|"string"|variable} ...

The format must be a "string literal" or a Batch variable that can include
control chars: \n New line, \r CarriageReturn, \t TAB, \b BackSpace, \a Bell
and specifications to show data: %i Integer, %f Float, %c Character, %s String.

                       %[flags][width][.precision]type
                         -+ 0#  -----  ---------- cdiouxXeEfgGaAps
Data specification       - | left align           c | character
formats start in         + | insert + sign        d | integer (Decimal)
% (percent sign)           | insert space for +   i | Integer = d
and end in TYPE          0 | zero pad             o | integer (Octal)
letter                   # | insert . in g type,  u | integer (Unsigned)
                           | insert 0|0x in o|x   x | integer (hexadecimal)
                                                  X | integer (HEXADECIMAL)
[width]  Minimum/total width (no truncate):       e | float   ([-]d.ddddeñddd)
printf "%05i" 3  =  "00003"                       E | float   (like e, with E)
                                                  f | float   ([-]ddd.dddddd)
[.precision]  Maximum width (truncate/round):     g | float   (shorter of f|e)
printf "%.4f" 3.141592654  =  "3.1416"            G | float   (like g, with E)
                                                  a | float   ([-]0xh.hhhpñdd)
An asterisk in place of width and/or precision    A | float   (like a, with P)
get its value from the next (int) parameter:      p | string  (address in hex)
printf "%0*i" 5 3  =  "00003"                     s | string
printf "%0*.*f" 8 4 3.141592654  =  "003.1416"

pause

Numbers start with digit and optional minus sign. They are Floating-point type
if include decimal point or Exponent of ten; else, they are 32-bits Integers.
Each data or operator must be separated by one or more spaces.
    printf "Int: %i, Float: %f, Char: %c, String: %s\n" 23 45. 'X' "Hello"

Integer and Float operations can be evaluated in Reverse Polish Notation (RPN)
in which first enter numbers, then operators. (4+5)/(6+7) is: 4 5 + 6 7 + /

Integer operators works on 32-bits integers *only*. One-operand operators:
! BoolNot, ~ BitNot, _ ChS, $ Sign, ] Sto, [ Rcl, > Dup, < Drop, ++ Inc, -- Dec
Two-operands operators: + Add, - Subtract, * Multiply, / Div, % Mod, ** Power,
<< BitSHL, >> BitSHR, & BitAnd, | BitOr, ^ BitXor, <> Exchan. # Random, . Float
    printf "3 plus 5 = %i, 8 minus 2 = %i\n"  3 5 +  8 2 -

Integer Stack manipulation:  >n dupN  <>n xchgN  <n dropN  {n rdnN  }n rupN
Integer Store:  ]n ][n ]+n ]++n ]-n ]--n ]*n ]/n ]%n
Integer Recall: [n     [+n [++n [-n [--n [*n [/n [%n

Floating-point functions operate float numbers *only*. One-operand functions:
CHS, ABS, SIGN, FRAC, INV, SQR, SQRT; LN, LOG, EXP, EXPT; STO, RCL, DUP, DROP.
SIN, COS, TAN, ASIN, ACOS, ATAN (rad); DEG, RAD. Special: ZERO, ONE, PI, INT.
Two-operands functions: ADD, SUB, MUL, DIV, MOD, POW, XCHG.
    printf "Integer result: %i, Float result: %f\n"  35 12 -  44. 23. SUB
    printf "The result of (4+5)/(6+7) is: %.2f\n"  4. 5. ADD 6. 7. ADD DIV

Float Stack manipulation:       DUPn      XCHGn      DROPn      INIT
Float Store:    STOn STO[n STO+n STO++n STO-n STO--n STO*n STO/n STO%n
Float Recall:   RCLn       RCL+n RCL++n RCL-n RCL--n RCL*n RCL/n RCL%n

pause

printf.exe Version 2.11  Copyright (C) 2016-2023, Antonio Perez Ayala

Provides strings management and the simplest (REC) "Block Programming" scheme
with Hewlett-Packard calculator style companion conditional tests.

Operations on character strings:

atoi(string)     | Convert string to integer | "123"  ATOI  123
atof(string)     | Convert string to float   | "123"  ATOF  123.
len(string)      | Length of string          | "AEIOU"  LEN  "AEIOU" 5
getc(str,pos)    | Get char from string      | "AEIOU" 2  GETC  "AEIOU" 2 'I'
putc(str,pos,C)  | Put char in string        | "AEIOU" 2 'x'  PUTC  "AExOU" 2
xchc(str,pos,C)	 | Exchange char from string | "AEIO" 2 'x'  XCHC  "AExO" 2 'I'
dupc(character,N)| Duplicate a char -> string| 'A' 8  DUPC  "AAAAAAAA"
dups(string,N)   | Duplicate a string        | "EI-" 4  DUPS  "EI-EI-EI-EI-"
revc(string)     | Reverse chars in string   | "AEIOU"  REVC  "UOIEA"
revs(s1,..,sn,N) | Reverse several strings   | "AE" "IOU" 2  REVS  "IOU" "AE" 2
gets(str,pos,len)| Get a substring           | "AEIOU" 2 3  GETS  "AEIOU" "IOU"
index(str,subs)  | Positions of substring    | "AEIOU" "IO"  INDEX  "AEIOU" 2 1
split(string)    | Split string in substr's  | "AEI OU"  SPLIT  "AEI" "OU" 2
join(s1,..,sn,N) | Join several strings      | "A" "EI" "OU" 3  JOIN  "AEIOU"
shift(s1,..,sn,N)| Shift several strings     | "A" "E" "I" 3 SHIF "E" "I" 2 "A"
repl(str,s1,s2)  | Replace substrings        | "AEIOU" "IO" "x"  REPL  "AExU"
cmps(cad1,cad2)  | Compare two strings:-1 0 1| "ONE" "One" CMPS 1

Input/Output operations:

OUT            | Send formatted output to the screen: "format" data1 data2 ...
FMT{           | Define new format and data for OUT, up to close it with FMT}
GETK           | Wait for a key press; return ASCII code or -(special value)
GETK?          | No wait: if there is not a key pressed ready, is False
GETK?:r        | Wait for the next milliseconds time-slice given in register R
maxlen IN      | Read a line; remove maxlen and returns "Line read" len
"command" CMD  | Execute cmd.exe's command and open a pipe to read its output
maxlen IN?     | Read a line; at EndOfFile close the last pipe open by CMD
"file" IN{?:n  | Open the file for input in handle N; if not found, is False
"file" IN{+?:n | Open the file for update in both input/output handles N
maxlen IN?:n   | Read a line from handle N; at EndOfFile close the handle
"file" OUT{:n  | Create and open the file for output in handle N
"file" OUT{+:n | Open the file for append (output at EndOfFile) in handle N
OUT:n          | Send formatted output to handle N
OUT}:n         | Close output/update handle N
OUT}+:n        | Set file size to current FP position and close handle N
SEEK#:n:p      | Move FP position of handle N to position P from origin #

pause

The "Block Programming" is a scheme to write programs based on just 4 elements:
( "Begin"   : "Repeat"   ; "Quit"   ) "End"
and a couple simple rules about the evaluation of Conditions (Tests).

The Begin-End parentheses delimits a "Code Block" and sets the points where
the control flow can be transfered: to begin or end of the code block
- The : (Repeat) operator transfer control to begin of its code block.
- The ; (Quit) operator transfer control *after* the end of its code block.

A Test is an operation that answers if a Condition result is True or False;
all Tests are written with a question-mark character added at end:  Test?
- If the Test? is True: the control flow continue to the next element
- If the Test? is False: the control flow jumps after the next   ;   :   )

The simplest Tests are some operators that also works as conditions:
--? ]--n?  !? &? %?  getc?  GETK? IN?
    printf "Turn number %i\n" 10 ( OUT --? : )

        | Integer Tests:              | Floating Point Tests:
X vs 0: | >0? >=0? <0? <=0? ==0? !=0? | GTR0? GEQ0? LSS0? LEQ0? EQU0? NEQ0?
X vs Y: | >?  >=?  <?  <=?  ==?  !=?  | GTR?  GEQ?  LSS?  LEQ?  EQU?  NEQ?

Code blocks can be nested in each other. Multiplication table (one long line):
    printf /" " %3i" 0 ( ++ 11 ==? ; < 0 ( ++ 11 ==? < ;
                         < >2 >2 * {3 OUT <3 : ) FMT{ "\n" OUT FMT} < : )


Additional documentation with related data:

   1- Technicall description of printf CRT function
   2- Format specification reference for printf CRT function
   3- Reverse Polish Notation (RPN) article at Wikipedia
   4- Learn Reverse Polish Notation (RPN) at HPmuseum.org
   5- Reverse Polish Notation (RPN) extensive tutorial
   6- HP-15C Hewlett-Packard RPN calculator Owner's Handbook
   7- User's manual of this printf.exe application
   8- Algebraic Expression to Reverse Polish Notation converter
   9- Description of printf.exe error messages

:helpEnd
Select the desired document (0 to end):
https://msdn.microsoft.com/en-us/library/wc7014hz.aspx
https://learn.microsoft.com/en-us/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions
https://en.wikipedia.org/wiki/Reverse_Polish_notation
http://www.hpmuseum.org/rpn.htm#learn
http://hansklav.home.xs4all.nl/rpn/index.html
"http://h10032.www1.hp.com/ctg/Manual/c03030589.pdf"
"printf.exe - Arithmetic and Programming.html"
AlgebraicToRPN.bat
printfHelp.bat 0


:errors
[*]  NOT ENOUGH MEMORY!
    - The computer have *very little* available memory (very unlikely).
    - You have requested a *very high* number of storage registers/characters.
[*]  Unclosed 'Char, "string or /*comment
    The closing delimiter of a Char', String" or Comment*/ is missing.
    An unclosed string or comment can only be detected until the program ends.
[*]  Wrong or too large number
    A number is bad written. Refer to "3.1- Data Types" for the proper syntax.
[*]  Invalid operator
    This error is usually a typo.
    Remember to separate all operators by one or more spaces.
    This error may happen when a "long" operator is bad written, like: ]--.3?
[*]  Undefined function or variable
    This error is usually a typo. Check the spelling.
    This error may happen when a "long" function is bad written, like: IN{+?:6
    If you use a Batch variable, such a variable *must be defined*.
[*]  Maximum number of operations exceeded
    More than 20 levels of active FMT{ marks or nested CMD functions,
    or more than 32 Blocks with Name (subroutines) defined.
    See the Appendix # for instructions about incrementing these limits.
[*]  ":" Repeat, ";" Quit, ")" End or false Test? outside any (Block
    These operations:  : ; )  and a Test? that is False
    can only be used *inside* a (code block).
[*]  Unclosed Block at nesting level #
    The right parenthesis of an open code block is missing.
    Note that this error can only be detected until the program ends.
    The reported block's nesting level can help to identify the unclosed block.
[*]  This NAME( Block can not be defined here
    A named block (subroutine) must be defined *before* the "format" string
    and must be an *external* (not nested) code block.
    Two named blocks can not have the same name (first 4 characters).
[*] Too many (recursive) subroutine calls
    This error is usually a loop of recursive invocations with no exit.
    Check *the condition* that break the recursive invocations.
    The maximum number of pending subroutine returns is about 128,000.
[*] Can not create/open output file
    An *output* file tried to be opened was not found or can not be created.
    This is usually a typo that inserts an illegal character in the file name,
    or a non-existent subdirectory.
    Remember that you can create a directory via CMD function.
    The same "not found" error on an *input* file is detected in the IN{?:n
    open operation/test? itself.
[*] Input/Output operation on a not open handle
    An input IN?:n or output OUT:n file operation uses a handle
    that was not previously open.
    Check that the N handle number used in open and I/O operations be the same.


==============================================================


:LAhelp
Emula la funci¢n printf de C run-time y eval£a operaciones aritm‚ticas en RPN.

    printf "formato" {n£mero [operador]|'c'|"cadena"|variable} ...

El formato debe ser una "cadena literal" o variable Batch que puede inclu¡r
caracteres de control: \n New line, \r CarriageReturn, \t TAB, \b BackSpace
y especificaciones para datos: %i Entero, %f Flotante, %c Caracter, %s Cadena.

                       %[marca][ancho][.precision]tipo
                         -+ 0#  -----  ---------- cdiouxXeEfgGaAps
Las especificaciones     - | justifica izquierda  c | character
para datos comienzan     + | inserta signo +, ¢   d | integer (Decimal)
en % (porcentaje) y        | pone espacio en +    i | Integer = d
terminan en la letra     0 | rellena con ceros    o | integer (Octal)
del TIPO                 # | inserta . en tipo g  u | integer (Unsigned)
                           | inserta 0|0x en o|x  x | integer (hexadecimal)
                                                  X | integer (HEXADECIMAL)
[ancho]  Ancho m¡nimo o total (no trunca):        e | float   ([-]d.ddddeñddd)
printf "%05i" 3  =  "00003"                       E | float   (como e, con E)
                                                  f | float   ([-]ddd.dddddd)
[.precision]  Ancho m ximo (trunca/redondea):     g | float   (m s corto f|e)
printf "%.4f" 3.141592654  =  "3.1416"            G | float   (como g, con E)
                                                  a | float   ([-]0xh.hhhpñdd)
Un asterisco en lugar del ancho o precision       A | float   (como a, con P)
toma su valor del siguiente dato entero:          p | string  (direcci¢n hex)
printf "%0*i" 5 3  =  "00003"                     s | string
printf "%0*.*f" 8 4 3.141592654  =  "003.1416"

pause

Los n£meros comienzan con d¡gito o signo menos opcional. Son de punto flotante
si incluyen punto decimal o Exponente de 10; si no, son enteros de 32 bits.
Todos los datos y operadores deben separarse por uno o m s espacios.
    printf "Entero: %i, Flotante: %f, Car: %c, Cadena: %s\n" 23 45. 'X' "Hola"

Operaciones enteras y flotantes pueden evaluarse en Notaci¢n Polaca Inversa
(RPN) que ingresa los operadores *despu‚s* de los n£meros: 4*5+6 es: 4 5 * 6 +

Los operadores enteros procesan *solamente* enteros de 32-bits. De un operando:
! BoolNot, ~ BitNot, _ ChS, $ Sign, ] Sto, [ Rcl, > Dup, < Drop, ++ Inc, -- Dec
De dos operandos: + Suma, - Resta, * Multiplica, / Divide, % Mod, ** Potencia,
<< BitSHL, >> BitSHR, & BitAnd, | BitOr, ^ BitXor, <> Exchan. # Random, . Float
    printf "3 m s 5 = %i, 8 menos 2 = %i\n"  3 5 +  8 2 -

Manejo del Stack Entero:  >n dupN   <>n xchgN   <n dropN   {n rdnN   }n rupN
Almacena Entero:  ]n  ][n  ]+n  ]++n  ]-n  ]--n  ]*n  ]/n  ]%n
Recupera Entero:  [n       [+n  [++n  [-n  [--n  [*n  [/n  [%n

Las funciones flotantes operan *solamente* n£meros flotantes. De un operando:
CHS, ABS, SIGN, FRAC, INV, SQR, SQRT; LN, LOG, EXP, EXPT; STO, RCL, DUP, DROP.
SIN, COS, TAN, ASIN, ACOS, ATAN (rad); DEG, RAD. Especial: ZERO, ONE, PI, INT.
De dos operandos: ADD, SUB, MUL, DIV, MOD, POW, XCHG.
    printf "Resultado entero: %i, Flotante: %f\n"  35 12 -  44. 23. SUB
    printf "El resultado de (4+5)/(6+7) es: %.2f\n"  4. 5. ADD 6. 7. ADD DIV

Manejo del Stack Flotante:     DUPn     XCHGn     DROPn     INIT
Almacena Flotante:  STOn STO[n STO+n STO++n STO-n STO--n STO*n STO/n STO%n
Recupera Flotante:  RCLn       RCL+n RCL++n RCL-n RCL--n RCL*n RCL/n RCL%n

pause

printf.exe Version 2.11  Copyright (C) 2016-2023, Antonio P‚rez Ayala

Incluye manejo de cadenas y el esquema mas simple (REC) de "Programaci¢n por
Bloques" con pruebas condicionales estilo calculadora Hewlett-Packard.

Operaciones sobre cadenas de caracteres:

atoi(cadena)     | Convierte cadena a entero | "123"  ATOI  123
atof(cadena)     | Convierte cadena flotante | "123"  ATOF  123.
len(cadena)      | Longitud de cadena        | "AEIOU"  LEN  "AEIOU" 5
getc(cad,pos)    | Toma caracter de cadena   | "AEIOU" 2  GETC  "AEIOU" 2 'I'
putc(cad,pos,C)  | Pone caracter en cadena   | "AEIOU" 2 'x'  PUTC  "AExOU" 2
xchc(cad,pos,C)	 | Cambia caracter de cadena | "AEIO" 2 'x'  XCHC  "AExO" 2 'I'
dupc(caracter,N) | Duplica un caracter -> cad| 'A' 8  DUPC  "AAAAAAAA"
dups(cadena,N)   | Duplica una cadena        | "EI-" 4  DUPS  "EI-EI-EI-EI-"
revc(string)     | Invierte caracteres en cad| "AEIOU"  REVC  "UOIEA"
revs(c1,..,cn,N) | Invierte varias cadenas   | "AE" "IOU" 2  REVS  "IOU" "AE" 2
gets(cad,pos,len)| Toma una subcadena        | "AEIOU" 2 3 GETS  "AEIOU" "IOU"
index(cad,subc)  | Posiciones de subcadena   | "AEIOU" "IO"  INDEX  "AEIOU" 2 1
split(cadena)    | Divide cadena en subcadnas| "AEI OU"  SPLIT  "AEI" "OU" 2
join(c1,..,cn,N) | Une varias cadenas        | "A" "EI" "OU" 3  JOIN  "AEIOU"
shift(c1,..,cn,N)| Desplaza varias cadenas   | "A" "E" "I" 3 SHIF "E" "I" 2 "A"
repl(cad,s1,s2)  | Reemplaza subcadenas      | "AEIOU" "IO" "x"  REPL  "AExU"
cmps(cad1,cad2)  | Compara dos cadenas:-1 0 1| "UNO" "Uno"  CMPS  1

Operaciones de Entrada y Salida:

OUT            | Manda salida formato a la pantalla: "formato" dato1 dato2 ...
FMT{           | Define nuevo formato y datos para OUT, hasta cerrar con FMT}
GETK           | Espera por una tecla; entrega c¢digo ASCII o -valor_especial
GETK?          | No espera: si no hay una tecla lista, es False
GETK?:r        | Espera siguiente intervalo de milisegundos dado en memoria R
maxlen IN      | Lee una l¡nea; elimina maxlen y entrega: "L¡nea le¡da" len
"comando" CMD  | Ejecuta comando de cmd.exe y abre un pipe para leer su salida
maxlen IN?     | Lee una l¡nea; en EndOfFile cierra el £ltimo pipe de CMD
"file" IN{?:n  | Abre el archivo para input en handle N; si no est , es False
"file" IN{+?:n | Abre el archivo para update en ambos input/output handles N
maxlen IN?:n   | Lee una l¡nea desde handle N; en EndOfFile cierra el handle
"file" OUT{:n  | Crea y abre el archivo para output en el handle N
"file" OUT{+:n | Abre el archivo para append (output en EndOfFile) en handle N
OUT:n          | Manda salida con formato al handle N
OUT}:n         | Cierra el handle N de output o update
OUT}+:n        | Fija el tama¤o del archivo al FP actual y cierra el handle N
SEEK#:n:p      | Mueve puntero FP del handle N a la posici¢n P desde origen #

pause

La "Programaci¢n por Bloques" es un esquema de escritura de programas basado
en estos cuatro elementos:   ( "Begin"   : "Repeat"   ; "Quit"   ) "End"
y un par de reglas simples sobre la evaluaci¢n de Condiciones (Tests).

Los par‚ntesis Begin-End delimitan un "Bloque de C¢digo" y marcan los puntos
a los que se puede transferir el control: al principio o al final del bloque.
- El operador  :  (Repeat) transfiere el control al principio de su bloque.
- El operador  ;  (Quit) transfiere el control *despu‚s* del fin de su bloque.

Un Test es una operaci¢n que contesta si una Condici¢n es verdadera o falsa;
todos los Tests se escriben con un signo de interrogaci¢n al final:  Test?
- Si el Test? es verdadero: la ejecuci¢n contin£a en la siguiente operaci¢n
- Si el Test? es falso: la ejecuci¢n brinca hasta pasar el siguiente   :   ;  )

Los Tests mas simples son algunos operadores que tambi‚n funcionan como Tests:
--? ]--n?  !? &? %?  getc?  GETK? IN?
    printf "Vuelta n£mero %i\n" 10 ( OUT --? : )

        | Tests Enteros:              | Tests de Punto Flotante:
X vs 0: | >0? >=0? <0? <=0? ==0? !=0? | GTR0? GEQ0? LSS0? LEQ0? EQU0? NEQ0?
X vs Y: | >?  >=?  <?  <=?  ==?  !=?  | GTR?  GEQ?  LSS?  LEQ?  EQU?  NEQ?

Los bloques de c¢digo pueden anidarse. Tabla de multiplicar (una l¡nea larga):
    printf /" " %3i" 0 ( ++ 11 ==? ; < 0 ( ++ 11 ==? < ;
                         < >2 >2 * {3 OUT <3 : ) FMT{ "\n" OUT FMT} < : )


Documentaci¢n adicional con informaci¢n relacionada:

   1- Descripci¢n t‚cnica de la funci¢n printf de C Run-Time
   2- Sintaxis de la especificaci¢n de formato para la funci¢n printf
   3- Art¡culo sobre Notaci¢n Polaca Inversa (RPN) en Wikipedia
   4- Introducci¢n a RPN en el manual de la calculadora HP-12C
      (tambi‚n revise el Ap‚ndice A en la p gina 168)
   5- Manual del propietario de la calculadora HP-15C (en ingl‚s)
   6- Manual de usuario de esta aplicaci¢n printf.exe
   7- Convertidor de Expresiones Algebraicas a Notaci¢n Polaca Inversa
   8- Descripci¢n de los mensajes de error de printf.exe

:LAhelpEnd
Seleccione el documento deseado (0 para terminar):
https://learn.microsoft.com/es-es/cpp/c-runtime-library/reference/printf-printf-l-wprintf-wprintf-l
https://learn.microsoft.com/es-es/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions
https://es.wikipedia.org/wiki/Notaci%C3%B3n_polaca_inversa
"http://www.hp.com/ctg/Manual/bpia5312#page=18"
"http://h10032.www1.hp.com/ctg/Manual/c03030589.pdf"
"printf.exe - Aritm‚tica y Programaci¢n.html"
AlgebraicToRPN.bat
printfHelp.bat 0

:LAerrors
[*]  ­MEMORIA INSUFICIENTE!
    - La computadora tiene *muy poca* memoria disponible (poco probable).
    - Se solicit¢ un n£mero *muy grande* de registros de almacenamiento.
[*]  'Caracter, "cadena o /*comentario sin cerrar
    Falta el delimitador de cierre de un Caracter', Cadena" o Comentario*/.
    Note que una cadena o comentario sin cerrar s¢lo se puede detectar
    hasta que el programa termina.
[*]  N£mero err¢neo o demasiado grande
    Un n£mero est  mal escrito.
    Consulte "3.1- Tipos de Datos" para revisar la forma correcta.
[*]  Operador inv lido
    Suele ser un error de tecleo.
    Recuerde separar todos los operadores por uno o m s espacios.
    Este error puede suceder al escribir operadores muy "largos", como: ]--.3?
[*]  Funci¢n o variable no definida
    Suele ser un error de tecleo; revise la sintaxis.
    Este error puede suceder al escribir funciones muy "largas", como: IN{+?:6
    Recuerde que si usa una variable Batch, la variable *debe estar definida*.
[*]  N£mero m ximo de operaciones excedido
    M s de 20 niveles de marcas FMT{ activas o funciones CMD anidadas,
    o m s de 32 Bloques con Nombre (subrutinas) definidos.
    Consulte el Ap‚ndice # 2 por instrucciones para aumentar estos l¡mites.
[*]  ":" Repeat, ";" Quit, ")" End o Test? falso fuera de todo (Bloque
    Las operaciones:  : ; )  o un Test? que resulta falso s¢lo pueden aparecer
    dentro de un (bloque de c¢digo).
[*]  Bloque sin cerrar en un nivel de anidamiento
    Falta el par‚ntesis de cierre de un bloque de c¢digo.
    Note que este error s¢lo puede detectarse hasta que el programa termina.
    El nivel de anidamiento reportado ayuda a identificar el bloque abierto.
[*]  Este bloque con NOMBRE( no puede definirse aqu¡
    Los bloques con nombre (subrutinas) deben definirse *antes* del "formato"
    y deben ser bloques *externos* (no anidados).
    Dos subrutinas no pueden tener el mismo nombre (primeros 4 caracteres).
[*] Demasiadas llamadas (recursivas) a subrutinas
    Este error usualmente es un bucle de invocaciones recursivas sin salida.
    Revise *la condici¢n* que interrumpe las invocaciones recursivas.
    El m ximo n£mero de regresos pendientes de subrutinas es 128,000 aprox.
[*] No se puede crear/abrir un archivo de salida
    El archivo *de salida* que se intent¢ abrir no se encontr¢/no pudo crearse.
    Suele ser un error de tecleo que inserta un caracter ilegal en el nombre
    del archivo, o un subdirectorio que no existe.
    Recuerde que se puede crear un directorio usando la funci¢n CMD.
    El mismo error "no encontrado" sobre un archivo *de entrada* se detecta
    en la misma operaci¢n/test? de apertura IN{?:n
[*] Operaci¢n de entrada/salida sobre un handle no abierto
    Una operaci¢n IN?:n de entrada u OUT:n de salida sobre un archivo
    usa un n£mero de handle que no ha sido abierto.
    Revise que el n£mero de handle N de la operaci¢n de E/S sea el mismo de la
    operaci¢n de apertura.

