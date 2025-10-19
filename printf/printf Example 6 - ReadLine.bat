@echo off

rem printf Example - Read a line char by char; process BackSpace and Enter keys
rem Antonio Perez Ayala

set /P "=Enter a line: " < NUL

rem Didactic form
printf "%%s\n"	/* result format	*/ ^
   80		/* maxLen for line read	*/ ^
   ]2		/* store it in R2	*/ ^
   '$' /" <> /"	/* '$' maxLen		*/ ^
   dupc		/* "buffer"  for string	*/ ^
   ]1		/* store buffer in R1	*/ ^
   0		/* "buf" 0   char index	*/ ^
   (		/* WHILE GETK != Enter	*/ ^
      GETK	/*    "buf" i key	*/ ^
      13	/*    "buf" i key CR	*/ ^
      ==? ;	/*    is Enter?: break	*/ ^
   /" < /" 8	/*    "buf" i key BS	*/ ^
      ==?	/*       is BS ?	*/ ^
      (		/*    IF          :	*/ ^
      /" < < /"	/*       "buf" i	*/ ^
         ==0? ;	/*       no chars?: QUIT*/ ^
         --	/*       "buf" i--	*/ ^
         FMT{ "\b \b" OUT FMT}	/* clear last char */ ^
      )		/*    ENDIF		*/ ^
   :		/* REPEAT when key=BS	*/ ^
   /" < /" 32	/*    "buf" i key 32	*/ ^
   /" >? < <	/*    key < 32 ?   "	*/ ^
   :		/* yes: ignore it	*/ ^
   /" < /"	/*    "buf" i char	*/ ^
      ]0	/*    store char in R0	*/ ^
   /" < /"	/*    "buf" i		*/ ^
      [2	/*    "buf" i maxLen	*/ ^
      ==?	/*    no more space? :	*/ ^
   /" < /"	/*    clear maxlen and	*/ ^
   :		/* REPEAT (ignore char)	*/ ^
   /" < /"	/*    "buf" i		*/ ^
      FMT{ "%%c" [0 OUT FMT}	/* show char	*/ ^
      [0 putc	/*    "Cuf" i     store char	*/ ^
      ++	/*    "Cuf" i++ ...	*/ ^
   :		/* REPEAT		*/ ^
   )		/* ENDWHILE		*/ ^
   FMT{ "\n" OUT FMT}	/* end of line	*/ ^
		/* "linebuf" len CR CR	*/ ^
/" < < /"	/* "linebuf" len	*/ ^
   0		/* "linebuf" len 0	*/ ^
   putc		/* "line" len		*/ ^
   FMT{ "Line read: \"%%s\"\n" [1 OUT	/* output result */


echo/
set /P "=Enter a line: " < NUL
rem Standard form
printf /" "%%s\n" 80 ]2 '$' <> dupc ]1 0 ( GETK 13 ==? ; < 8 ==? ( < < ==0? ; -- FMT{ "\b \b" OUT FMT} ) : < 32 >? < < : < ]0 < [2 ==? < : < FMT{ "%%c" [0 OUT FMT} [0 putc ++ : ) FMT{ "\n" OUT FMT} < < 0 putc FMT{ "Line read: \"%%s\"\n" [1 OUT

echo/
set /P "=Enter a password: " < NUL
rem Standard form
printf /" "%%s\n" 12 ]2 '$' <> dupc ]1 0 ( GETK 13 ==? ; < 8 ==? ( < < ==0? ; -- FMT{ "\b \b" OUT FMT} ) : < 32 >? < < : < ]0 < [2 ==? < : < FMT{ "%%c" '*' OUT FMT} [0 putc ++ : ) FMT{ "\n" OUT FMT} < < 0 putc FMT{ "Pass read: \"%%s\"\n" [1 OUT

echo/
set /P "=Enter a 8-digits number: " < NUL
rem Standard form
printf /" "%%s\n" 8 ]2 '$' <> dupc ]1 0 ( GETK 13 ==? ; < 8 ==? ( < < ==0? ; -- FMT{ "\b \b" OUT FMT} ) : < 48 >? < < : < 57 <? < < : < ]0 < [2 ==? < : < FMT{ "%%c" [0 OUT FMT} [0 putc ++ : ) FMT{ "\n" OUT FMT} < < 0 putc FMT{ "Number read: \"%%s\"\n" [1 OUT

