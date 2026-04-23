@echo off

rem printf.exe Example: traverse a whole directory tree via a recursive subroutine
rem Antonio Perez Ayala


rem Didactic form:
printf				^
  TREE(				/* Subroutine that just show *one* directory	*/ ^
	"DIR /A:D /B" CMD	/* Read subdirectories from (nested) CMD	*/ ^
	FMT{ "%%.*s%%s\n"	/* Open new format for: margin spaces dirname	*/ ^
	(			/* WHILE another subdir name?			*/ ^
	   80 IN? /" < /"	/*    "subdirname" (drop len)			*/ ^
	   [0 [2		/*    "subdirname"  R0=margin  R2="spaces"	*/ ^
	   }3			/*    margin "spaces" "subdirname"		*/ ^
	   OUT			/*    "%.*s%s\n"  margin into * define the size	*/ ^
				/*              of "spaces" before "subdirname"	*/ ^
	   CD			/*    enter to this subdirectory		*/ ^
	   3 ]+0 /" <* /"	/*    increment margin in +3 and clear data	*/ ^
	   TREE			/*    show the contents of the subdirectory!!!	*/ ^
	   ".." CD		/*    go back to previous directory		*/ ^
	   3 ]-0 /" <* /"	/*    decrement margin in -3 and clear data	*/ ^
	   :			/* REPEAT					*/ ^
	)			/* ENDWHILE	Nested CMD closes		*/ ^
	FMT}			/* Close format					*/ ^
  )				/* END of TREE subroutine			*/ ^
  ""				/* No format for this "main" program		*/ ^
  ' ' 30 dupc ]2 /" < /"	/* create "30 spaces", store in R2 and drop it	*/ ^
  TREE				/* Start TREE!					*/

pause

rem Standard form:
printf /" TREE( "DIR /A:D /B" CMD FMT{ "%%.*s%%s\n" ( 80 IN? < [0 [2 }3 OUT CD 3 ]+0 <*  TREE  ".." CD 3 ]-0 <* : ) FMT} )  "" ' ' 30 dupc ]2 <  TREE

pause

rem Modified code that also show the files in each subdirectory:
printf				^
  TREE(				/* Subroutine that just show *one* directory	*/ ^
	"DIR /A:D /B" CMD	/* Read subdirectories from (nested) CMD	*/ ^
	FMT{ "\n%%.*s%%s\n"	/* Open new format for: margin spaces dirname	*/ ^
	(			/* WHILE another subdir name?			*/ ^
	   80 IN? /" < /"	/*    "subdirname" (drop len)			*/ ^
	   [0 [2		/*    "subdirname"  R0=margin  R2="spaces"	*/ ^
	   }3			/*    margin "spaces" "subdirname"		*/ ^
	   OUT			/*    "%.*s%s\n"  margin into * define the size	*/ ^
				/*              of "spaces" before "subdirname"	*/ ^
	   CD			/*    enter to this subdirectory		*/ ^
				/*    ======== New part to show files ========= */ ^
	   "DIR /A:-D /B 2>NUL" CMD /*    read file names from nested CMD	*/ ^
	   FMT{ "%%.*s+ %%s\n"	/*    open new format for nested file names	*/ ^
	   ( 80 IN? /" < /"	/*    WHILE    same as above to show file names	*/ ^
	     [0 [2 }3 OUT /" <*	/* "     show the file name and clear data	*/ ^
	     :			/*    REPEAT					*/ ^
	   )			/*    ENDWHILE		Nested CMD closes	*/ ^
	   FMT}			/*    close nested format			*/ ^
				/*    ======== End part to show files ========= */ ^
	   3 ]+0 /" <* /"	/*    increment margin in +3 and clear data	*/ ^
	   TREE			/*    show the contents of the subdirectory!!!	*/ ^
	   ".." CD		/*    go back to previous directory		*/ ^
	   3 ]-0 /" <* /"	/*    decrement margin in -3 and clear data	*/ ^
	   :			/* REPEAT	go back for next subdirectory	*/ ^
	)			/* ENDWHILE	Nested CMD closes		*/ ^
	FMT}			/* Close format					*/ ^
  )				/* END of TREE subroutine			*/ ^
  ""				/* No format for this "main" program		*/ ^
  ' ' 30 dupc ]2 /" < /"	/* create "30 spaces", store in R2 and drop it	*/ ^
  TREE				/* Start TREE!					*/

