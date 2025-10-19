@echo off
setlocal

rem Comparison of character/string processing using Index vs using Pointers
rem Antonio Perez Ayala

rem Duplicate a string (emulate:  1 dups )
rem "original"   thisCode   "original" "duplicated"

set /P "string=Enter any string: "
if errorlevel 1 goto :EOF

echo/
echo Case 1: Use getc and putc with same index
printf "Original:   \"%%s\"\nDuplicated: \"%%s\"\n"  ^
	string		/* "original"		*/  ^
	len		/* "original" len	*/  ^
	'X' /" <> /"	/* "orig" 'X' len	*/  ^
	dupc		/* "orig" "XX dup"	*/  ^
	0		/* "orig" "dup" 0	    index = 0	*/  ^
	(		/* WHILE getc?		*/  ^
	   }3		/*    "dup" 0 "orig"	*/  ^
        /" <> /"	/*    "dup" "orig" 0	*/  ^
	   getc?	/*    "dup" "orig" 0 'o'*/  ^
	   }4		/*    "orig" 0 'o' "dup"*/  ^
	   {3		/*    "orig" "dup" 0 'o'*/  ^
	   putc		/*    "orig" "oup" 0	*/  ^
	   ++		/*    "orig" "oup" 1,...    index++	*/  ^
	:		/* REPEAT		*/  ^
	)		/* ENDWHILE		*/  ^
			/* "orig" "dup" len	*/  ^
	OUT		/* show result		*/


echo/
echo Case 2: Use movc0 and movc1 over one pointer each
echo         and manually increment the pointers
printf "Original:   \"%%s\"\nDuplicated: \"%%s\"\n"  ^
	string		/* "original"		*/  ^
	]0		/* R0 = "original"	*/  ^
	len		/* "original" len	*/  ^
	'X' /" <> /"	/* "orig" 'X' len	*/  ^
	dupc		/* "orig" "XX dup"	*/  ^
	]1		/* R1 = "duplicated"	*/  ^
	(		/* WHILE movc0?		*/  ^
        /" <> /"	/*    "dup" "orig"	exchange *pointers*	*/  ^
	   movc0?	/*    "dup" "orig" 'o'		like getc?	*/  ^
	/" <> /"	/*    "dup" 'o' "orig"	*/  ^
	   ++		/*    "dup" 'o' "orig"++*/  ^
	   {3		/*    "orig"++ "dup" 'o'*/  ^
	   movc1	/*    "orig"++ "oup"		like putc	*/  ^
	   ++		/*    "orig"++ "oup"++	*/  ^
	:		/* REPEAT		*/  ^
	)		/* ENDWHILE		*/  ^
     /" <* /"		/* empty stack		*/  ^
	[0 [1		/* "orig" "dup"		*/  ^
	OUT		/* show result		*/


echo/
echo Case 3: Use movc0 and movc1 over one pointer each
echo         and auto-increment the pointers
printf "Original:   \"%%s\"\nDuplicated: \"%%s\"\n"  ^
	string		/* "original"		*/  ^
	]0		/* R0 = "original"	*/  ^
	len		/* "original" len	*/  ^
	'X' /" <> /"	/* "orig" 'X' len	*/  ^
	dupc		/* "orig" "XX dup"	*/  ^
	]1		/* R1 = "duplicated"	*/  ^
	(		/* WHILE movc+0?	*/  ^
        /" <> /"	/*    "dup" "orig"	exchange *pointers*	*/  ^
	   movc+0?	/*    "dup" "orig"++ 'o'	like getc?	*/  ^
	/" <> /"	/*    "dup" 'o' "orig"++*/  ^
	   {3		/*    "orig"++ "dup" 'o'*/  ^
	   movc+1	/*    "orig"++ "oup"++		like putc	*/  ^
	:		/* REPEAT		*/  ^
	)		/* ENDWHILE		*/  ^
     /" <* /"		/* empty stack		*/  ^
	[0 [1		/* "orig" "dup"		*/  ^
	OUT		/* show result		*/


echo/
echo Case 4: Use movc2 over *two pointers* at same time
echo         and manually increment the pointers
printf "Original:   \"%%s\"\nDuplicated: \"%%s\"\n"  ^
	string		/* "original"		*/  ^
	]0		/* R0 = "original"	*/  ^
	len		/* "original" len	*/  ^
	'X' /" <> /"	/* "orig" 'X' len	*/  ^
	dupc		/* "orig" "XX dup"	*/  ^
	]1		/* R1 = "duplicated"	*/  ^
     /" <> /"		/* "dup" "orig"		*/  ^
	(		/* WHILE movc2?		*/  ^
	   movc2?	/*    "oup" "orig"	*/  ^
	   ++		/*    "oup" "orig"++	*/  ^
	/" <> /"	/*    "orig"++ "oup"	*/  ^
	   ++		/*    "orig"++ "oup"++	*/  ^
	/" <> /"	/*    "oup"++ "orig"++	*/  ^
	:		/* REPEAT		*/  ^
	)		/* ENDWHILE		*/  ^
     /" <* /"		/* empty stack		*/  ^
	[0 [1		/* "orig" "dup"		*/  ^
	OUT		/* show result		*/

echo/
echo Case 5: Use movc2 over *two pointers* at same time
echo         and auto-increment the pointers
printf "Original:   \"%%s\"\nDuplicated: \"%%s\"\n"  ^
	string		/* "original"		*/  ^
	]0		/* R0 = "original"	*/  ^
	len		/* "original" len	*/  ^
	'X' /" <> /"	/* "orig" 'X' len	*/  ^
	dupc		/* "orig" "XX dup"	*/  ^
	]1		/* R1 = "duplicated"	*/  ^
     /" <> /"		/* "dup" "orig"		*/  ^
	(		/* WHILE movc2?		*/  ^
	   movc+2+?	/*    "oup"++ "orig"++	*/  ^
	:		/* REPEAT		*/  ^
	)		/* ENDWHILE		*/  ^
     /" <* /"		/* empty stack		*/  ^
	[0 [1		/* "orig" "dup"		*/  ^
	OUT		/* show result		*/

echo/
