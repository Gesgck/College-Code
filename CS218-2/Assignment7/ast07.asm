; *****************************************************************
;  Name: Alec Zheng
;  NSHE_ID: 2001982564
;  Section: 1003
;  Assignment: 7
;  Description: odd even sort an array

; Sort a list of number using the odd/even sort algorithm.
; Also finds the minimum, median, maximum, and average of the list.

; =====================================================================
;  Macro to convert integer to senary value in ASCII format.
;  Reads <integer>, converts to ASCII/senary string including
;	NULL into <string>


;	YOUR CODE GOES HERE
%macro	int2aSenary	2

mov rcx, 0
mov eax, %1
mov r10, 6
mov r8, %2
%%mConvert6:
cdq
div r10d		;divides rax by 6
push rdx		;push remainder
inc rcx			;counts how many loops there is
cmp eax, 0
jne %%mConvert6	;loops if the quotient is not 0
mov rbx, 14
sub rbx, rcx	;spaces to right justify the string
mov rcx, 0
%%mRightJust:		;loop to right justify
mov [r8], byte ' '	;don't know how else to make it space
inc r8
inc rcx
cmp rbx, rcx
jne %%mRightJust
%%mPopLoop:		;loop to pop numbers off the stack
inc rcx
pop rax
add rax, 0x30
mov [r8], rax
inc r8
cmp rcx, 14
jne %%mPopLoop

%endmacro


; --------------------------------------------------------------
;  Simple macro to display a string to the console.
;	Call:	printString  <stringAddr>

;	Arguments:
;		%1 -> <stringAddr>, string address

;  Count characters (excluding NULL).
;  Display string starting at address <stringAddr>

%macro	printString	1
	push	rax			; save altered registers
	push	rdi
	push	rsi
	push	rdx
	push	rcx

	mov	rdx, 0
	mov	rdi, %1
%%countLoop:
	cmp	byte [rdi], NULL
	je	%%countLoopDone
	inc	rdi
	inc	rdx
	jmp	%%countLoop
%%countLoopDone:

	mov	rax, SYS_write		; system call for write (SYS_write)
	mov	rdi, STDOUT		; standard output
	mov	rsi, %1			; address of the string
	syscall				; call the kernel

	pop	rcx			; restore registers to original values
	pop	rdx
	pop	rsi
	pop	rdi
	pop	rax
%endmacro

; ---------------------------------------------

section	.data

; -----
;  Define constants.

TRUE		equ	1
FALSE		equ	0

EXIT_SUCCESS	equ	0			; Successful operation

STDIN		equ	0			; standard input
STDOUT		equ	1			; standard output
STDERR		equ	2			; standard error

SYS_read	equ	0			; system call code for read
SYS_write	equ	1			; system call code for write
SYS_open	equ	2			; system call code for file open
SYS_close	equ	3			; system call code for file close
SYS_fork	equ	57			; system call code for fork
SYS_exit	equ	60			; system call code for terminate
SYS_creat	equ	85			; system call code for file open/create
SYS_time	equ	201			; system call code for get time

LF		equ	10
SPACE		equ	" "
NULL		equ	0
ESC		equ	27

; -----
;  Program specfic constants

STR_LENGTH	equ	15

; -----
;  Provided data

lst	dd	  147,  1123,  2245,  4440,   165
	dd	   69,   126,   571,   147,   228
	dd	   27,    90,   177,    75,    14
	dd	  181,    25,    15,    22,  1217
	dd	  127,    64,   140,   172,    24
	dd	 2161,   134,   151,    32,    12
	dd	 1113,  1232,  2146,  3376,  5120
	dd	 2356,  3164, 34565,  3155, 23157
	dd	 1001,   128,    33,   105,  8327
	dd	  101,   115,   108, 12233,  2115
	dd	 1227,  1226,  5129,   117,   107
	dd	  105,   109,   730,   150,  3414
	dd	 1107,  6103,  1245,  6440,   465
	dd	 2311,   254,  4528,   913,  6722
	dd	 1149,  2126,  5671,  4647,  4628
	dd	  327,  2390,   177,  8275,  5614
	dd	 3121,   415,   615,    22,  7217
	dd	 1221,    34,  6151,   432,   114
	dd	  629,   114,   522,  2413,   131
	dd	 5639,   126,    62,    41,   127
	dd	 2101,   133,   133,    50,  4532
	dd	 1219,  3116,    62,    17,   127
	dd	 6787,  4569,    79, 15675,    14
	dd	 7881,  8320,  3467,  4559,  1190
	dd	  186,   134,  1125,  5675,  3476
	dd	 2137,  2113,  1647,   114,    15
	dd	 6571,  7624,   128,   113,  3112
	dd	 1121,   320,  4540,  5679,  1190
	dd	 9125,   116,   122,   117,   127
	dd	 5677,   101,  3727,   125,  3184
	dd	 1104,   124,   112,   143,   176
	dd	 7534,  2126,  6112,   156,  1103
	dd	 6759,  6326,  2171,   147,  5628
	dd	 7527,  7569,  3177,  6785,  3514
	dd	 1156,   164,  4165,   155,  5156
	dd	 5634,  7526,  3413,  7686,  7563
	dd	 2147,   113,   143,   140,   165
	dd	 5721,  5615,  4568,  7813,  1231
	dd	 5527,  6364,   330,   172,    24
	dd	 7525,  5616,  5662,  6328,  2342

len	dd	200


min	dd	0
med	dd	0
max	dd	0
sum	dd	0
avg	dd	0

; -----
;  Misc. data definitions (if any).



; -----
;  Provided string definitions.

newLine		db	LF, NULL

hdr		db	LF, "---------------------------"
		db	"---------------------------"
		db	LF, ESC, "[1m", "CS 218 - Assignment #7", ESC, "[0m"
		db	LF, "Odd/Even Sort", LF, LF, NULL

hdrMin		db	"Minimum:  ", NULL
hdrMax		db	"Maximum:  ", NULL
hdrMed		db	"Median:   ", NULL
hdrSum		db	"Sum:      ", NULL
hdrAve		db	"Average:  ", NULL

; ---------------------------------------------

section .bss

tmpString	resb	STR_LENGTH

; ---------------------------------------------

section	.text
global	_start
_start:

; ******************************
;  function oddEvenSort(list) {
;	bool sorted = false;

;	while (!sorted) {
;		sorted = true;
;		for (var i=1; i < len-1; i+=2) {
;			if (list[i] > list[i+1]) {
;			swap(list, i, i+1);
;			sorted = false;
;			}
;		}
;		for (var i=0; i < len-1; i+=2) {
;			if (list[i] > list[i+1]) {
;				swap(list, i, i+1);
;				sorted = false;
;			}
;		}
;	}
;  }


;	YOUR CODE GOES HERE

mov r15, FALSE				;r15 is "sorted" variable
mov r8, lst					;r8 = array
mov r9d, dword[len]		;r9 = length
dec r9
loopStart:
mov r15, TRUE
mov rcx, 0					;rcx = i
oddLoop:
inc rcx
cmp rcx, r9
jae oddSkip
mov r10d, dword[r8+rcx*4]	;r10 = compare i
inc rcx
mov r11d, dword[r8+rcx*4]	;r11 = compare i+1
cmp r10d, r11d
jae oddLoop
mov dword[r8+rcx*4], r10d	;swap the two
dec rcx
mov dword[r8+rcx*4], r11d
inc rcx
mov r15, FALSE				;sorted = false
jmp oddLoop
oddSkip:
mov rcx, 0
evenLoop:
cmp rcx, r9
jae evenSkip
mov r10d, dword[r8+rcx*4]	;r10 = compare i
inc rcx
mov r11d, dword[r8+rcx*4]	;r11 = compare i+1
inc rcx
cmp r10d, r11d
jae evenLoop
dec rcx
mov dword[r8+rcx*4], r10d	;swap the two
dec rcx
mov dword[r8+rcx*4], r11d
inc rcx
inc rcx
mov r15, FALSE				;sorted = false
jmp evenLoop 
evenSkip:
cmp r15, FALSE				;check if sorted == TRUE
je loopStart


; ******************************
;  Find stats
;	minimum, maximum, median, sum, and average


;	YOUR CODE GOES HERE

mov rcx, lst
mov eax, dword[lst]
mov dword[min], eax			;min
mov rbx, 0
mov ebx, dword[len]
dec rbx
mov eax, dword[rcx+rbx*4]
mov dword[max], eax			;max
inc rbx
mov rax, rbx
mov rbx, 2					;len/2
div rbx
mov ebx, dword[rcx+rax*4]	;list/2
dec rax
add ebx, dword[rcx+rax*4]	;list/2 - 1
mov rax, rbx
mov rbx, 2
div ebx
cwd
mov dword[med], eax
;sum
mov rax, 0
mov rcx, 0
mov ecx,dword[len]
dec rcx
mov rdx, lst
sumLoop:
add eax, dword[rdx+rcx*4]
dec rcx
cmp rcx, 0
jge sumLoop
mov dword[sum], eax
cdq
mov ebx, dword[len]
div ebx
cwd
mov dword[avg], eax


; ******************************
;  Display results to screen in senary.

	printString	hdr

	printString	hdrMin
	int2aSenary	dword [min], tmpString
	printString	tmpString
	printString	newLine

	printString	hdrMax
	int2aSenary	dword [max], tmpString
	printString	tmpString
	printString	newLine

	printString	hdrMed
	int2aSenary	dword [med], tmpString
	printString	tmpString
	printString	newLine

	printString	hdrSum
	int2aSenary	dword [sum], tmpString
	printString	tmpString
	printString	newLine

	printString	hdrAve
	int2aSenary	dword [avg], tmpString
	printString	tmpString
	printString	newLine
	printString	newLine

; ******************************
;  Done, terminate program.

last:
	mov	rax, SYS_exit
	mov	rdi, EXIT_SUCCESS
	syscall

