@echo off

rem printf Example: simple animation
rem Antonio Perez Ayala

rem Didactic form:
printf "\b %%c"		/* format			*/ ^
   SF1			/* Set Flag 1			*/ ^
   100 ]1 /" < /"	/* Delay = 100 drop		*/ ^
   219			/* 219=ASCII code of block char	*/ ^
   (			/* DO				*/ ^
      OUT		/*    Advance the block		*/ ^
      ( GETK?:1		/*    SWITCH (key pressed)	*/ ^
         ( -75 ==?	/*       CASE -75: (left arrow)	*/ ^
            10 ]+1 /" <	/* "        Delay += 10	drop	*/ ^
         ) /" < /"	/*          drop the -75	*/ ^
         ( -77 ==?	/*       CASE -77: (right arrow)*/ ^
            10 ]-1 /" < /* "        Delay -= 10	drop	*/ ^
         ) /" < /"	/*          drop the -77	*/ ^
         ( 13 ==?	/*       CASE 13: (enter)	*/ ^
            CF1		/*          Clear Flag 1	*/ ^
         ) /" < /"	/*          drop the 13		*/ ^
         /" < /"	/*    drop the key		*/ ^
      )			/*    ENDSWITCH			*/ ^
      F1?		/* WHILE Flag 1 is set		*/ ^
   :			/* REPEAT			*/ ^
   )			/* ENDWHILE			*/


goto :EOF

rem Standard form:
printf /" "\b %%c"  SF1  100 ]1 <  219 ( OUT  ( GETK?:1  ( -75 ==? 10 ]+1 < ) <  ( -77 ==? 10 ]-1 < ) <  ( 13 ==? CF1 ) <  <  )  F1? : ) 

rem Modified code that use nested conditional blocks instead Flag1:
printf /" "\b %%c"       100 ]1 <  219 ( OUT  ( GETK?:1  ( -75 ==? 10 ]+1 < ) <  ( -77 ==? 10 ]-1 < ) <  ( 13 ==? ; <  <  )?  )?     : )

