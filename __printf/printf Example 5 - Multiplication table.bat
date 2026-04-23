@echo off

rem printf.exe Example: Multiplication Table
rem Antonio Perez Ayala

echo Standard form:
printf /" " %%3i" 0 ( ++ 11 ==? ; < 0 ( ++ 11 ==? < ; < >2 >2 * {3 OUT <3 : ) FMT{ "\n" OUT FMT} < : ) 

echo/

echo Didactic form:
printf " %%3i"	/* format		*/ ^
   0		/* i=0			*/ ^
   (		/* WHILE ++i != 11  	*/ ^
      ++	/*    1	 ,2,... 	*/ ^
      11 ==?	/*    i 11   equ?	*/ ^
   ;		/*           break 	*/ ^
   /" < /"	/*    i			*/ ^
      0		/*    i j=0		*/ ^
      (		/*    WHILE ++j != 11	*/ ^
         ++	/*       i 1  ,2,...	*/ ^
         11 ==? /*       i j 11   equ?	*/ ^
      /" < /"	/*       i j		*/ ^
      ;		/*                break	*/ ^
      /" < /"	/*       i j		*/ ^
      /" >2 /"	/*       i j i		*/ ^
      /" >2 /"	/*       i j i j	*/ ^
         *	/*       i j i*j	*/ ^
         {3	/*	 i*j i j	*/ ^
         OUT	/*             show i*j	*/ ^
      /" <3 /"	/*       i j		*/ ^
      :		/*    REPEAT		*/ ^
      )		/*    ENDWHILE		*/ ^
		/*    i 11		*/ ^
   FMT{ "\n"	/*    EndOfLine		*/ ^
   OUT		/*    show it		*/ ^
   FMT}		/*    clear EOL FMT	*/ ^
/" < /"		/*    i			*/ ^
   :		/* REPEAT		*/ ^
   )		/* ENDWHILE		*/

