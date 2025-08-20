;  Name: Alec Zheng
;  NSHE_ID: 2001982564
;  Section: 1003
;  Assignment: 5
;  Description: find information about hexagons
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

sideLens	dd	 1145,  1135,  1123,  1123,  1123
		dd	 1254,  1454,  1152,  1164,  1542
		dd	 1353,  1457,  1182,  1142,  1354
		dd	 1364,  1134,  1154,  1344,  1142
		dd	 1173,  1543,  1151,  1352,  1434
		dd	 1355,  1037,  1123,  1024,  1453
		dd	 1134,  2134,  1156,  1134,  1142
		dd	 1267,  1104,  1134,  1246,  1123
		dd	 1134,  1161,  1176,  1157,  1142
		dd	 1153,  1193,  1184,  1142,  2034

apothemLens	dw	  133,   114,   173,   131,   115
		dw	  164,   173,   174,   123,   156
		dw	  144,   152,   131,   142,   156
		dw	  115,   124,   136,   175,   146
		dw	  113,   123,   153,   167,   135
		dw	  114,   129,   164,   167,   134
		dw	  116,   113,   164,   153,   165
		dw	  126,   112,   157,   167,   134
		dw	  117,   114,   117,   125,   153
		dw	  123,   173,   115,   106,   113

length		dd	50

perimMin	dd	0
perimEstMed	dd	0
perimMax	dd	0
perimSum	dd	0
perimAve	dd	0

areaMin		dd	0
areaEstMed	dd	0
areaMax		dd	0
areaSum		dd	0
areaAve		dd	0

; -----
;  Additional variables

ddTwo		dd	2

; ----------------------------------------------
;  Uninitialized Static Data Declarations.

section	.bss

;	Place data declarations for uninitialized data here...
;	(i.e., large arrays that are not initialized)

hexPerims	resd	50
hexAreas	resd	50

; *****************************************************************

section	.text
global _start
_start:


; -----
;	YOUR CODE GOES HERE...

;loop to find the perimeters
mov ecx, dword[length]
mov r8, sideLens
mov r9, hexPerims
mov rsi, 0
mov r10, 6
mov r11, 0
perimLoop:							;perimLoop
mov eax, dword[r8+rsi*4]
mul r10d
mov dword[r9+rsi*4], eax
add r11d, eax						;add up the sum
inc rsi
loop perimLoop

;find the perims stuff
mov dword[perimSum], r11d			;sum
mov eax, dword[perimSum]
cdq
mov ecx, dword[length]
div ecx
mov dword[perimAve], eax			;ave
;find the min and max
mov r10d, dword[hexPerims]
mov r11d, dword[hexPerims]
mov ecx, dword[length]
mov rsi, 0
perimMaxMin:						;perimMax
cmp r10d, dword[r9+rsi*4]
jae notMax
mov r10d, dword[r9+rsi*4]
notMax:
cmp r11d, dword[r9+rsi*4]			;perimMin
jbe notMin
mov r11d, dword[r9+rsi*4]
notMin:
inc rsi
loop perimMaxMin
mov dword[perimMax], r10d
mov dword[perimMin], r11d
;Estimated Median
mov eax, dword[length]
mov rdx, 0
mov r8, 2
div r8w
mov r12d, dword[r9+rax*4] 
dec rax
add r12d, dword[r9+rax*4]
mov eax, r12d
cdq
div r8d
mov dword[perimEstMed], eax

;loop to find the areas
mov r8, apothemLens
mov r10, hexAreas
mov rsi, 0
mov ecx, dword[length]
mov r11d, 2
mov r12, 0
areaLoop:							;loop start
movzx eax, word[r8+rsi*2]
mov ebx, dword[r9+rsi*4]
mul ebx
div r11d
mov dword[r10+rsi*4], eax
add r12, rax						;add up area sum
inc rsi
loop areaLoop

;do things for area
mov dword[areaSum], r12d
mov eax, r12d
cdq
mov ecx, dword[length]
div ecx
mov dword[areaAve], eax				;ave
mov r9, hexAreas
mov r10d, dword[hexAreas]
mov r11d, dword[hexAreas]
mov ecx, dword[length]
mov rsi, 0
;area Min and Max
areaMaxMin:							;areaMax
cmp r10d, dword[r9+rsi*4]
jae anotMax
mov r10d, dword[r9+rsi*4]
anotMax:
cmp r11d, dword[r9+rsi*4]			;areaMin
jbe anotMin
mov r11d, dword[r9+rsi*4]
anotMin:
inc rsi
loop areaMaxMin
mov dword[areaMax], r10d
mov dword[areaMin], r11d
;Estimated Median
mov eax, dword[length]
mov rdx, 0
mov r8, 2
div r8w
mov r12d, dword[r9+rax*4] 
dec rax
add r12d, dword[r9+rax*4]
mov eax, r12d
cdq
div r8d
mov dword[areaEstMed], eax

; *****************************************************************
;	Done, terminate program.

last:
	mov	rax, SYS_exit		; call call for exit (SYS_exit)
	mov	rdi, EXIT_SUCCESS	; return code of 0 (no error)
	syscall

