@echo off
setlocal

rem printf.exe Example: Two-variables statistical calculations
rem Antonio Perez Ayala

rem Create a standard data file
(
echo  0.00	4.63
echo 20.00	5.78
echo 40.00	6.61
echo 60.00	7.21
echo 80.00	7.78
echo/
echo 65.00
echo 70.00
echo 75.00
) > "HP-15C Page 49 example.txt"

if "%~1" neq "/?" goto begin

echo Two-variables statistical calculations
echo/
echo     "%~0" textFile.txt
echo/
echo The textFile.txt must contain a series of X-Y value pairs terminated by an
echo empty line and followed by lines with X values used for Linear Estimations
echo/
echo The included example was taken from page 49 of HP-15C Owner's Handbook at
echo http://h10032.www1.hp.com/ctg/Manual/c03030589.pdf#page=49
echo/
type "HP-15C Page 49 example.txt"
echo/
echo/
choice /M "--> Do you want to open the HP-15C handbook now "
if %errorlevel% equ 1 explorer "http://h10032.www1.hp.com/ctg/Manual/c03030589.pdf#page=49"
goto :EOF


Emulating the operation of S+ key and statistical calculations in HP-15C calculator

Statistics storage registers used in HP-15C

R2	n	Number of data points accumulated.
R3	Sx	Summation of x-values.
R4	Sx^2	Summation of squares of x-values.
R5	Sy	Summation of y-values.
R6	Sy^2	Summation of squares of y-values.
R7	Sxy	Summation of products of x- and y-values.

Statistical formulae
Reference: Appendix A of HP-15C Owner's Handbook at #page=206

R8	M = R2*R4 - R3^2
R9	N = R2*R6 - R5^2
R0	P = R2*R7 - R3*R5

Mean (average):
  Mx = R3 / R2
  My = R5 / R2

Standard Deviation:
  Sx = SQRT( R8 / (R2*(R2-1)) )
  Sy = SQRT( R9 / (R2*(R2-1)) )

Coefficients for Linear Regression: y = A*x + B
  A = R0 / R8
  B = (R8*R5 - R0*R3) / (R2*R8)

After Linear Regression Coefficients are calculated,
they are stored at R.1=A and R.2=B

Correlation coefficient:
  r = R0 / SQRT(R8*R9)

Linear Estimation:
  Direct formula:  y ~= A*x + B  =  R.1*x + R.2
  HP's formula:    y ~= ( R8*R5 + R0*(R2*x - R3) ) / (R2*R8)

Direct formula values are equivalent to HP formula:
y =    A   *x   +   B
y = (R0/R8)*x   +   (R8*R5 - R0*R3) / (R2*R8)
  = (R0/R8)*(R2*R8)*x / (R2*R8)   +   (R8*R5 - R0*R3) / (R2*R8)
  = (  (R0/R8)*(R2*R8)*x + (R8*R5 - R0*R3)  ) / (R2*R8)
  = (  (R0)*(R2)*x + (R8*R5 - R0*R3)  ) / (R2*R8)
  = (  (R0*R2)*x + R8*R5 - R0*R3  ) / (R2*R8)
  = (  R8*R5 + (R0*R2)*x - R0*R3  ) / (R2*R8)
  = (  R8*R5 + R0*(R2*x - R3)  ) / (R2*R8)


:begin

set "file=HP-15C Page 49 example.txt"
if "%~1" neq "" set "file=%~1"
if not exist "%file%" echo File not found: "%file%" & goto :EOF

echo Input file "%file%":
type "%file%"
echo/

rem Didactic form
< "%file%" printf ""  /* no base format */ ^
   /* Part 1: Populate statistics registers */ ^
   (		/* WHILE read line	*/ ^
      80	/*    80   (input len)	*/ ^
      IN	/*    "x.xx y.yy" len	*/ ^
      ==0? ;	/* line empty?  break	*/ ^
   /" < /"	/*    "x.xx y.yy"	*/ ^
      atof1	/*    x. y. 2		*/ ^
   /" < /"	/*    x. y.		*/ ^
      STO++2	/*       Accum n	*/ ^
      STO+5	/*       Accum Sy	*/ ^
      STO9	/*       R9 = y		*/ ^
      Sqr	/*    x. y^2		*/ ^
      STO+6	/*       Accum Sy^2	*/ ^
      DROP	/*    x.		*/ ^
      STO+3	/*       Accum Sx	*/ ^
      DUP	/*    x. x.		*/ ^
      Sqr	/*    x. x^2		*/ ^
      STO+4	/*       Accum Sx^2	*/ ^
      DROP	/*    x.		*/ ^
      RCL*9	/*    x*y		*/ ^
      STO+7	/*       Accum Sx*y	*/ ^
      DROP	/*       Empty stack	*/ ^
   :		/* REPEAT		*/ ^
   )		/* ENDWHILE		*/ ^
/" <* /"	/* empty stack		*/ ^
   FMT{ "Statistics registers:\n" OUT FMT}	/* Header	*/ ^
   FMT{ "R2 n:\t\t%%.0f\nR3 Sum x:\t%%.2f\nR4 Sum x^2:\t%%.2f\nR5 Sum y:\t%%.2f\nR6 Sum y^2:\t%%.2f\nR7 Sum x*y:\t%%.2f\n\n"	/* Output */ ^
         RCL2            RCL3              RCL4                RCL5              RCL6                RCL7           OUT FMT}	/* registers */ ^
   /* Part 2: Calculate statistics values		*/ ^
   /*    R8  =  M = R2*R4 - R3^2			*/ ^
   /*    R9  =  N = R2*R6 - R5^2			*/ ^
   /*    R0  =  P = R2*R7 - R3*R5			*/ ^
   RCL2 RCL4 Mul RCL3 Sqr Sub STO8 Drop		/* M	*/ ^
   RCL2 RCL6 Mul RCL5 Sqr Sub STO9 Drop		/* N	*/ ^
   RCL2 RCL7 Mul RCL3 RCL5 Mul Sub STO0 Drop	/* P 	*/ ^
   /* Part 3: Calculate and output results		*/ ^
   /*    Mean:  Mx = R3 / R2,  My = R5 / R2		*/ ^
   FMT{ "Mean (average):\t\tMx=%%.2f  My=%%.2f\n"  RCL3 RCL2 Div  RCL5 RCL2 Div  OUT FMT}	/* Mean	  */ ^
   /*    Standard Deviation:  Sx = SQRT( R8 / (R2*(R2-1)) ), Sy = SQRT( R9 / (R2*(R2-1)) )  */ ^
   FMT{ "Standard Deviation:\tSx=%%.2f  Sy=%%.2f\n"	/* Standard Deviation		    */ ^
        RCL8 RCL2 DUP ONE Sub Mul STO1 Div Sqrt   RCL9 RCL1 Div Sqrt   OUT FMT}			/* Sx, Sy */ ^
   /* Coefficients for Linear Regression:  y = A*x + B			*/ ^
   /*    R.1 = A = R0 / R8,   R.2 = B = (R8*R5 - R0*R3) / (R2*R8)	*/ ^
   FMT{ "Linear Regression:\ty = %%.2f*x + %%.2f\n"		/* L.R.	*/ ^
        RCL0 RCL8 Div STO.1   RCL8 RCL5 Mul RCL0 RCL3 Mul Sub RCL2 RCL8 Mul Div STO.2  OUT FMT}	/* A*x+B  */ ^
   /* Correlation coefficient:  r = R0 / SQRT(R8*R9)	*/ ^
   FMT{ "Correlation coeff:\tr = %%.2f\n\n"  RCL0 RCL8 RCL9 Mul Sqrt Div  OUT FMT}		/* r	  */ ^
   /* Part 3: Linear Estimations loop */ ^
   FMT{ "Linear Estimations:\n" OUT FMT}	/* Header */ ^
   FMT{ "%%.2f   %%.2f\n"	/* Data	*/ ^
   (		/* WHILE read line	*/ ^
      80	/*    80   (input len)	*/ ^
      IN?	/*    "x.xx" len	*/ ^
   /" < /"	/*    "x.xx"		*/ ^
      atof	/*    x.		*/ ^
      DUP	/*    x. x.		*/ ^
      RCL.1 Mul RCL.2 Add    /* y=A*x+B */ ^
      OUT	/*      show estimation	*/ ^
   /" <* /"	/*      clear stack	*/ ^
   :		/* REPEAT		*/ ^
   )		/* ENDHILE		*/
