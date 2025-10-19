@echo off

rem printf.exe Example: Read a text file line by line
rem Antonio Perez Ayala

rem Create a sample file for tests:
(
echo First line
echo/
echo Third line
echo/
echo/
echo Last line
) > textFile.txt

echo ==== Input file:
type textFile.txt

echo/

echo ==== Read file, basic version:
< textFile.txt printf /" "%%s\n" ( 80 IN? OUT <* : )

echo ==== Didactic form:
< textFile.txt printf "%%s\n"	      /* format */ ^
   (		/* WHILE read line		*/ ^
      80	/*    80   (max line length)	*/ ^
      IN?	/*    "line read" len		*/ ^
      OUT	/*    the len is not displayed	*/ ^
   /" <* /"	/*    clear all data		*/ ^
   :		/* REPEAT			*/ ^
   )		/* ENDWHILE			*/

echo/

echo ==== Read file, numerate lines:
< textFile.txt printf /" "%%i:%%s\n" ( ]++0 [0 80 IN? OUT <* : )

echo ==== Didactic form:
< textFile.txt printf "%%i:%%s\n"     /* format	*/ ^
   (		/* WHILE read line		*/ ^
      ]++0	/*    inc reg 0 to 1, 2,...	*/ ^
      [0	/*    1	  ,2,...		*/ ^
      80	/*    1 80   (max line length)	*/ ^
      IN?	/*    1 "line read" len		*/ ^
      OUT	/*    the len is not displayed	*/ ^
   /" <* /"	/*    clear all data		*/ ^
   :		/* REPEAT			*/ ^
   )		/* ENDWHILE			*/

