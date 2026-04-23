;	printfStorage.asm: Data Definition Module for integer and floating point storage registers
;	                   and string data storage area for printf.exe application

;	Antonio Perez Ayala
;	version 1: 2023/01/01

	.486					;create 32 bit code
	.model flat, stdcall			;32 bit memory model
	option casemap :none			;case sensitive


	;Declaration of names exported to other modules
	PUBLIC		IREGS, IstorageI, Istorage,  FREGS, Fstorage,  CHARS
	PUBLIC		MAX_FORMAT, formatStack,  MAX_CMDSTDIN, cmdStdinStack,  NAMEDBLOCK_LEN, namedBlockName, namedBlockEntry


	;These are the importing declarations in the other (base) file:

;	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	;storage registers are declared in printfStorage.asm module 
;	EXTERN		IREGS:ABS, IstorageI:DWORD, Istorage:DWORD	;number/area of Integer storage registers
;	EXTERN		FREGS:ABS, Fstorage:REAL8			;number/area of Floating Point storage registers
;	EXTERN		CHARS:ABS					;size of memory block for string data area
;	EXTERN		MAX_FORMAT:ABS, formatStack:DWORD		;number/area of nested FMT{ marks
;	EXTERN		MAX_CMDSTDIN:ABS, cmdStdinStack:DWORD		;number/area of nested CMD's (redirected Stdin streams)
;	EXTERN		NAMEDBLOCK_LEN:ABS, namedBlockName:DWORD, namedBlockEntry:DWORD	;number/areas for defined subroutines
;	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


	.data?					;Uninitialized data segment: don't take space in the .exe

	IREGS		EQU	20		;Number of Integer storage registers
	FREGS		EQU	20		;Number of Floating Point storage registers
	CHARS		EQU	10 * 1024	;Size of memory block for string data = 10 KB
			;
	IstorageI	DD	?		;Index (i) integer register, *MUST BE PLACED* here! before Istorage
	Istorage	DD	IREGS DUP (?)	;Integer storage registers
	Fstorage	REAL8	FREGS DUP (?)	;Floating Point storage registers
			;
			;				;Reserve/Free data area for printf formats via: FMT{ ... FMT} delimiters
	MAX_FORMAT	EQU	40			;- Maximum nested FMT{ marks * 2
	formatStack	DD	MAX_FORMAT DUP (?)	;- Stack for stored FMT marks (comprised of Stack pointer and Data pointer pairs)
			;
			;				;Nested management of Stdin FILE * streams via: CMD..IN? (EOF)
	MAX_CMDSTDIN	EQU	20			;- Maximum redirected Stdin's (nested CMD asynchronous functions)
	cmdStdinStack	DD	MAX_CMDSTDIN DUP (?)	;- Stack for redirected CMD Stdin streams
			;
	NAMEDBLOCK_LEN	EQU	32			;Allowed number of "namedBlocks" (subroutines)
	namedBlockName	DD	NAMEDBLOCK_LEN DUP (?)	;- array for "namedBlock" names
	namedBlockEntry	DD	NAMEDBLOCK_LEN DUP (?)	;- array for "namedBlock" entry points
			;
	end
