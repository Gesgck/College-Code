;  Name: Alec Zheng
;  NSHE_ID: 2001982564
;  Section: 1003
;  Assignment: 4
;  Description: arithmetic, control, compare, and conditional jump instructions
;

; *****************************************************************
;  Static Data Declarations (initialized)

section	.data

; -----
;  Define standard constants.

NULL		equ	0			; end of string

TRUE		equ	1
FALSE		equ	0

EXIT_SUCCESS	equ	0			; Successful operation
SYS_exit	equ	60			; call code for terminate

; -----
;  Initialized Static Data Declarations.

;	Place data declarations here...

list		dd	 2140,  1116,  1540,  1240,  1677,  1635,  2426,  1820
		dd	 1614,  2418,  2513,  1420,  2119,  1215,  1525,  1712
		dd	 1441,  3622,  1731,  1729,  1615,  1724,  1217,  1224
		dd	 1580,  1147,  2324,  1425,  1816,  1262,  2718,  2192
  		dd	 1432,  1235,  2764,  1615,  1310,  1765,  1954,  1967
		dd	 1515,  3556,  1342,  7321,  1556,  2727,  1227,  1927
		dd	 1382,  1465,  3955,  1435,  1225,  2419,  2534,  1345
		dd	 2467,  1315,  1961,  1335,  2856,  2553,  1032,  1835
		dd	 1246,  2330,  2317,  1115,  2726,  2140,  2565,  2871
		dd	 1464,  1915,  1810,  1465,  1554,  1267,  1615,  1656
		dd	 2192,  1825,  1925,  2312,  1725,  2517,  1498,  1677
		dd	 1475,  2034,  1223,  1883,  1173,  1350,  1415,  1335
		dd	 1125,  1118,  1713,  3025
length		dd	100

listMin		dd	0
listEstMed		dd	0
listMax		dd	0
listSum		dd	0
listAve		dd	0

evenCnt		dd	0
evenSum		dd	0
evenAve		dd	0

tenCnt		dd	0
tenSum		dd	0
tenAve		dd	0



; *****************************************************************

section	.text
global _start
_start:

mov rdi, list
mov r10d, 0
mov ecx, dword[length]


sumLoop:	;Finds the sum of all numbers
	dec ecx
	add r10d, dword[list+rcx*4]
	cmp ecx, 0
	jne sumLoop
mov dword[listSum], r10d


mov r8d, dword[list+100*4]
mov ecx, dword[length]
lstMax:	;Finds the largets value of all numbers
	dec ecx
	cmp r8d, dword[list+rcx*4]
	jge skipMax
	mov r8d, dword[list+rcx*4]
	skipMax:
	cmp rcx, 0
	jne lstMax
mov dword[listMax], r8d


mov r8d, dword[list+eax*4]
mov ecx, dword[length]
lstMin:	;Finds the smallest value of all numbers
	dec ecx
	cmp r8d, dword[list+rcx*4]
	jle skipMin
	mov r8d, dword[list+rcx*4]
	skipMin:
	cmp rcx, 0
	jne lstMin
mov dword[listMin], r8d


;Finds the estimated median
mov eax, dword[length]
cdq
mov r13d, 2
div r13d
mov r15d, eax
mov eax, 0
add eax, dword[list+r15d*4]
dec r15d 
add eax, dword[list+r15d*4]
cdq
mov r13d, 2
div r13d
mov dword[listEstMed], eax


;Finds the average of the list
mov eax, dword[listSum]
cdq
div dword[length]
mov dword[listAve], eax
	

;Finds the number and sum of even numbers
mov ecx, dword[length]
mov ebx, 2
mov r9d, 0
mov r10d, 0
evenLoop:
	dec ecx
	cmp cl, 0xff
	je evenLoopExit
	mov eax, dword[list+rcx*4]
	cdq
	idiv ebx
	cmp edx, 0
	jne evenLoop
	add r10d, dword[list+rcx*4]
	inc r9d
	jmp evenLoop
evenLoopExit:
mov dword[evenCnt], r9d
mov dword[evenSum], r10d


;Finds the average of even numbers
mov eax, dword[evenSum]
cdq 
div dword[evenCnt]
mov dword[evenAve], eax


mov ecx, dword[length]
mov ebx, 10
mov r9d, 0
mov r10d, 0
tenLoop:;Finds the number and sum of 10 divisible numbers
	dec ecx
	cmp cl, 0xff
	je tenLoopExit
	mov eax, dword[list+rcx*4]
	cdq
	idiv ebx
	cmp edx, 0
	jne tenLoop
	add r10d, dword[list+rcx*4]
	inc r9d
	jmp tenLoop
tenLoopExit:
mov dword[tenCnt], r9d
mov dword[tenSum], r10d


;Finds the average of the 10 divisible numbers
mov eax, r10d
cdq
div dword[tenCnt]
mov dword[tenAve], eax

; *****************************************************************
;	Done, terminate program.

last:
	mov	rax, SYS_exit		; call call for exit (SYS_exit)
	mov	rdi, EXIT_SUCCESS	; return code of 0 (no error)
	syscall

