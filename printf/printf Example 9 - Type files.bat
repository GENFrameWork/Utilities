@echo off

rem printf.exe Example: read file names from "DIR /B *.TXT" command and then,
rem for each filename found, type it via a TYPE "filename" command

rem Didactic form:
printf	"\n\nFile: %%s\n"		/* Format			*/ ^
	"DIR /B *.TXT" CMD /" < /"	/* Read filenames from CMD-1	*/ ^
	(				/* WHILE another file name?	*/ ^
	   100 IN? OUT			/*    "filename" len   Show it	*/ ^
	   /" < /" ]1			/*    drop len, store name in R1*/ ^
	   GETK				/*    wait for a key (pause)	*/ ^
	   FMT{ "%%s\n"			/*    new format for file lines	*/ ^
	   "TYPE \"" [1 "\"" 3 ""	/*    "TYPE '" "filename" "'" 3 "" */ ^
	   join1			/*    "TYPE 'filename'"		*/ ^
	   CMD /" < /"			/*    Read file lines from CMD-2*/ ^
	   (				/*    WHILE another line?	*/ ^
	      1000 IN? OUT		/*       "line" len     Show it	*/ ^
	      /" <* /"			/*       clear stack (all data)	*/ ^
	      :				/*    REPEAT			*/ ^
	   )				/*    ENDWHILE   CMD-2 closes	*/ ^
	   FMT}				/*    Format close		*/ ^
	   /" <* /"			/*    clear all data		*/ ^
	   :				/* REPEAT			*/ ^
	)				/* ENDWHILE   CMD-1 closes	*/

goto :EOF

rem Standard form:
printf /" "\n\nFile: %s\n" "DIR /B *.TXT" CMD ^< ( 100 IN? OUT ^< ]1 GETK FMT{ "%s\n" "TYPE \"" [1 "\"" 3 "" join1 CMD ^< ( 1000 IN? OUT ^<* : ) FMT} ^<* : )
