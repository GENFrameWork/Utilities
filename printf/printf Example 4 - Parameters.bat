@echo off

rem printf.exe Example: process the parameters of the Batch file
rem Antonio Perez Ayala

set "parameters=%*"
if not defined parameters (
   echo This program requires *parameters* after its name. For example:
   echo/
   echo    %0 First Second "Param with spaces" Last
   echo/
   pause
   goto :EOF
)

echo/
echo First method: process parameters left-to-right using *shift* function

printf	""			/* No format			*/ ^
	parameters		/* "par1 par2 ... parN"		*/ ^
	split			/* "par1" "par2" ... "parN" N	*/ ^
	(			/* WHILE			*/ ^
	   ?			/*    another param?		*/ ^
	   shift		/*    "par2" "parN" N-1 "par1"	*/ ^
	   ]1 /" < /"		/*    R1 = "par1" and drop it	*/ ^
	   FMT{ "Param %%i: %%s\n" /* Param format		*/ ^
	      ]++0		/*       inc R0 = param counter	*/ ^
	      [0 [1 OUT		/*       count par1  output	*/ ^
	   FMT}			/*    Close format		*/ ^
				/*    "par2" "parN" N-1		*/ ^
	:			/* REPEAT			*/ ^
	)			/* ENDWHILE			*/

echo/
echo Didactic form:
printf /" "" parameters split ( ? shift ]1 < FMT{ "Param %%i: %%s\n" ]++0 [0 [1 OUT FMT} : ) 
echo/
echo/
echo Second method: reverse parameters with *revs* function; process right-to-left

printf	""			/* No format			*/ ^
	parameters		/* "par1 par2 ... parN"		*/ ^
	split			/* "par1" "par2" ... "parN" N	*/ ^
	revs			/* "parN" ... "par2" "par1" N	*/ ^
	(			/* WHILE			*/ ^
	   ?			/*    another param?		*/ ^
	   /" <> /"		/*    "parN" . "par2" N "par1"	*/ ^
	   ]1 /" < /"		/*    R1 = "par1" and drop it	*/ ^
	   FMT{ "Param %%i: %%s\n" /* Param format		*/ ^
	      ]++0		/*       inc R0 = param counter	*/ ^
	      [0 [1 OUT		/*       count par1  output	*/ ^
	   FMT}			/*    Close format		*/ ^
				/*    "parN" . "par2" N		*/ ^
	   --			/*    "parN" . "par2" N-1	*/ ^
	:			/* REPEAT			*/ ^
	)			/* ENDWHILE			*/

echo/
echo Didactic form:
printf /" "" parameters split revs ( ? <> ]1 < FMT{ "Param %%i: %%s\n" ]++0 [0 [1 OUT FMT} -- : ) 

