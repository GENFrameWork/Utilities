@echo off

rem printf.exe Example: Process characters of a string
rem Antonio Perez Ayala


rem Get string from parameter or create a default one
set "string=%~1"
if not defined string set "string=String Example"


echo String length:
printf /" "\"%%s\" have %%i characters\n"  string  0 ( getc? < ++ : < ) OUT

echo Didactic form:
printf "\"%%s\" have %%i characters\n" /* format */ ^
   string		/* "string"		*/  ^
   0			/* "string" 0		*/  ^
   (			/* WHILE getc?		*/  ^
      getc?		/*    "string" 0 C	*/  ^
      /" < /"		/*    "string" 0	*/  ^
      ++		/*    "string" 1 ,2,...	*/  ^
   :			/* REPEAT		*/  ^
			/*    "string" len 0	*/  ^
      /" < /"		/*    "string" len	*/  ^
   )			/* ENDWHILE		*/  ^
   OUT

echo/

echo Convert characters to lowercase:
printf "%%s\n"  string  /"  0 ( getc? ( 'A' <=? < 'Z' >=? < 32 + putc 'c' 'x' ) < < ++ : ) < <  OUT

echo Convert characters to uppercase:
printf "%%s\n"  string  /"  0 ( getc? ( 'a' <=? < 'z' >=? < 32 - putc 'c' 'x' ) < < ++ : ) < <  OUT

echo Didactic form:
printf "%%s\n"		/* format               */  ^
   string		/* "string"		*/  ^
   0			/* "string" 0		*/  ^
   (			/* WHILE getc?		*/  ^
      getc?		/*    "string" 0 c	*/  ^
      (			/*"   IF 'a' <= c AND c <= 'z'	"*/  ^
         'a'		/*       "string" 0 c 'a'	*/  ^
         /" <=?		/*          True if 'a' <= c	"*/  ^
			/*       AND			*/  ^
         /" < /"	/*       "string" 0 c		*/  ^
         'z'		/*       "string" 0 c 'z'	*/  ^
         /" >=?		/*          True if 'z' >= c	"*/  ^
         /" < /"	/*       "string" 0 c		*/  ^
			/*    THEN c is lowcase letter	*/  ^
         32 -		/*       "string" 0 C    convert upcase */  ^
         putc		/*       "String" 0	   store char	*/  ^
         'c'		/*       "String" 0 'c'     reload char	*/  ^
         'x'		/*       "String" 0 'c' 'x'   reload 'a' or 'z' */  ^
      )			/*    ENDIF		*/  ^
      /" < < /"		/*    "String" 0	*/  ^
      ++		/*    "String" 1 ,2,...	*/  ^
   :			/* REPEAT		*/  ^
			/*    "STRING" len 0	*/  ^
   )			/* ENDWHILE 		*/  ^
   /" < < /"		/* "STRING"		*/  ^
   OUT
