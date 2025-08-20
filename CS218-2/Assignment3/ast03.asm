;  Name: Alec Zheng
;  NSHE_ID: 2001982564
;  Section: 1003
;  Assignment: 3
;  Description: lots of assembly math


;  Focus on learning basic arithmetic operations
;  (add, subtract, multiply, and divide).
;  Ensure understanding of sign and unsigned operations.

; *****************************************************************
;  Data Declarations (provided).

section	.data
; -----
;  Define constants.

NULL		equ	0			; end of string

TRUE		equ	1
FALSE		equ	0

EXIT_SUCCESS	equ	0			; Successful operation
SYS_exit	equ	60			; call code for terminate

; -----
;  Assignment #3 data declarations

; byte data
bNum1		db	7
bNum2		db	17
bNum3		db	28
bNum4		db	39
bNum5		db	-7
bNum6		db	-17
bNum7		db	-24
bNum8		db	-34
bAns1		db	0
bAns2		db	0
bAns3		db	0
bAns4		db	0
bAns5		db	0
bAns6		db	0
bAns7		db	0
bAns8		db	0
bAns9		db	0
bAns10		db	0
wAns11		dw	0
wAns12		dw	0
wAns13		dw	0
wAns14		dw	0
wAns15		dw	0
bAns16		db	0
bAns17		db	0
bAns18		db	0
bRem18		db	0
bAns19		db	0
bAns20		db	0
bAns21		db	0
bRem21		db	0

; word data
wNum1		dw	127
wNum2		dw	255
wNum3		dw	327
wNum4		dw	421
wNum5		dw	149
wNum6		dw	-247
wNum7		dw	-325
wNum8		dw	-469
wAns1		dw	0
wAns2		dw	0
wAns3		dw	0
wAns4		dw	0
wAns5		dw	0
wAns6		dw	0
wAns7		dw	0
wAns8		dw	0
wAns9		dw	0
wAns10		dw	0
dAns11		dd	0
dAns12		dd	0
dAns13		dd	0
dAns14		dd	0
dAns15		dd	0
wAns16		dw	0
wAns17		dw	0
wAns18		dw	0
wRem18		dw	0
wAns19		dw	0
wAns20		dw	0
wAns21		dw	0
wRem21		dw	0

; double-word data
dNum1		dd	118236
dNum2		dd	258397
dNum3		dd	426726
dNum4		dd	614372
dNum5		dd	7871
dNum6		dd	-3296
dNum7		dd	-4357
dNum8		dd	-5277
dAns1		dd	0
dAns2		dd	0
dAns3		dd	0
dAns4		dd	0
dAns5		dd	0
dAns6		dd	0
dAns7		dd	0
dAns8		dd	0
dAns9		dd	0
dAns10		dd	0
qAns11		dq	0
qAns12		dq	0
qAns13		dq	0
qAns14		dq	0
qAns15		dq	0
dAns16		dd	0
dAns17		dd	0
dAns18		dd	0
dRem18		dd	0
dAns19		dd	0
dAns20		dd	0
dAns21		dd	0
dRem21		dd	0

; quadword data
qNum1		dq	1456789
qNum2		dq	2915775
qNum3		dq	3912602
qNum4		dq	5654879
qNum5		dq	14291
qNum6		dq	-145741
qNum7		dq	-244849
qNum8		dq	-461041
qAns1		dq	0
qAns2		dq	0
qAns3		dq	0
qAns4		dq	0
qAns5		dq	0
qAns6		dq	0
qAns7		dq	0
qAns8		dq	0
qAns9		dq	0
qAns10		dq	0
dqAns11		ddq	0
dqAns12		ddq	0
dqAns13		ddq	0
dqAns14		ddq	0
dqAns15		ddq	0
qAns16		dq	0
qAns17		dq	0
qAns18		dq	0
qRem18		dq	0
qAns19		dq	0
qAns20		dq	0
qAns21		dq	0
qRem21		dq	0

; *****************************************************************

section	.text
global _start
_start:

; ----------------------------------------------
; Byte Operations

; unsigned byte additions
;	bAns1  = bNum1 + bNum2
;	bAns2  = bNum2 + bNum3
;	bAns3  = bNum3 + bNum4

mov r8b, byte[bNum1]
mov r9b, byte[bNum2]
mov r10b, byte[bNum3]
mov r11b, byte[bNum4]

mov al, r8b
add al, r9b
mov byte[bAns1], al		;bAns1
mov al, r9b
add al, r10b
mov byte[bAns2], al		;bAns2
mov al, r10b
add al, r11b
mov byte[bAns3], al		;bAns3
; -----
; signed byte additions
;	bAns4  = bNum5 + bNum6
;	bAns5  = bNum7 + bNum8
mov r12b, byte[bNum5]
mov r13b, byte[bNum6]
mov r14b, byte[bNum7]
mov r15b, byte[bNum8]

mov al, r12b
add al, r13b
mov byte[bAns4], al		;bAns4
mov al, r14b
add al, r15b
mov byte[bAns5], al		;bAns5

; -----
; unsigned byte subtractions
;	bAns6  = bNum2 - bNum1
;	bAns7  = bNum3 - bNum2
;	bAns8  = bNum4 - bNum3

mov al, r9b
sub al, r8b
mov byte[bAns6], al		;bAns6
mov al, r10b
sub al, r9b
mov byte[bAns7], al 	;bAns7
mov al, r11b
sub al, r10b
mov byte[bAns8], al 	;bAns8

; -----
; signed byte subtraction
;	bAns9  = bNum7 - bNum5
;	bAns10 = bNum8 - bNum6

mov al, r14b
sub al, r12b
mov byte[bAns9], al 	;bAns9
mov al, r15b
sub al, r13b
mov byte[bAns10], al 	;bAns10

; -----
; unsigned byte multiplication
;	wAns11  = bNum2 * bNum3
;	wAns12  = bNum3 * bNum4
;	wAns13  = bNum1 * bNum4

mov al, r9b
mul r10b
mov word[wAns11], ax	;wAns11
mov al, r10b
mul r11b
mov word[wAns12], ax	;wAns12
mov al, r8b
mul r11b
mov word[wAns13], ax	;wAns13



; -----
; signed byte multiplication
;	wAns14  = bNum5 * bNum7
;	wAns15  = bNum6 * bNum8

mov al, r12b
imul r14b
mov word[wAns14], ax	;wAns14
mov al, r13b
imul r15b
mov word[wAns15], ax	;wAns15


; -----
; unsigned byte division
;	bAns16 = bNum4 / bNum3
;	bAns17 = bNum3 / bNum2
;	bAns18 = wNum2 / bNum1
;	bRem18 = wNum2 % bNum1

movzx ax, r11b
div r10b
mov byte[bAns16], al	;bAns16
movzx ax, r10b
div r9b
mov byte[bAns17], al	;bAns17
mov ax, word[wNum2]
div r8b
mov byte[bAns18], al	;bAns18
mov byte[bRem18], ah	;bRem18

; -----
; signed byte division
;	bAns19 = bNum8 / bNum5
;	bAns20 = bNum7 / bNum6
;	bAns21 = wNum6 / bNum4
;	bRem21 = wNum6 % bNum4

movsx ax, r15b
idiv r12b
mov byte[bAns19], al	;bAns19
movsx ax, r14b
idiv r13b
mov byte[bAns20], al	;bAns20
mov ax, word[wNum6]
idiv r11b
mov byte[bAns21], al	;bAns21
mov byte[bRem21], ah

; *****************************************
; Word Operations

; -----
; unsigned word additions
;	wAns1  = wNum1 + wNum3
;	wAns2  = wNum2 + wNum4
;	wAns3  = wNum3 + wNum2

mov r8w, word[wNum1]
mov r9w, word[wNum2]
mov r10w, word[wNum3]
mov r11w, word[wNum4]

mov ax, r8w
add ax, r10w
mov word[wAns1], ax		;wAns1
mov ax, r9w
add ax, r11w
mov word[wAns2], ax		;wAns2
mov ax, r10w
add ax, r9w
mov word[wAns3], ax		;wAns3

; -----
; signed word additions
;	wAns4  = wNum7 + wNum6
;	wAns5  = wNum8 + wNum5

mov r12w, word[wNum5]
mov r13w, word[wNum6]
mov r14w, word[wNum7]
mov r15w, word[wNum8]

mov ax, r14w
add ax, r13w
mov word[wAns4], ax		;wAns4
mov ax, r15w
add ax, r12w
mov word[wAns5], ax		;wAns5

; -----
; unsigned word subtractions
;	wAns6  = wNum3 - wNum1
;	wAns7  = wNum4 - wNum2
;	wAns8  = wNum2 - wNum1

mov ax, r10w
sub ax, r8w
mov word[wAns6], ax		;wAns6
mov ax, r11w
sub ax, r9w
mov word[wAns7], ax		;wAns7
mov ax, r9w
sub ax, r8w
mov word[wAns8], ax		;wAns8

; -----
; signed word subtraction
;	wAns9  = wNum8 - wNum6
;	wAns10  = wNum7 - wNum5

mov ax, r15w
sub ax, r13w
mov word[wAns9], ax		;wAns9
mov ax, r14w
sub ax, r12w
mov word[wAns10], ax		;wAns10

; -----
; unsigned word multiplication
;	dAns11 = wNum2 * wNum2
;	dAns12  = wNum3 * wNum2
;	dAns13  = wNum4 * wNum1

mov ax, r9w
mul r9w
mov word[dAns11], ax
mov word[dAns11+2], dx		;wAns11
mov ax, r10w
mul r9w
mov word[dAns12], ax		
mov word[dAns12+2], dx		;wAns12
mov ax, r11w
mul r8w
mov word[dAns13], ax		
mov word[dAns13+2], dx		;wAns13

; -----
; signed word multiplication
;	dAns14  = wNum7 * wNum5
;	dAns15  = wNum8 * wNum6

mov ax, r14w
imul r12w
mov word[dAns14], ax		
mov word[dAns14+2], dx		;wAns14
mov ax, r15w
imul r13w
mov word[dAns15], ax		
mov word[dAns15+2], dx		;wAns15

; -----
; unsigned word division
;	wAns16 = wNum4 / wNum2
;	wAns17 = wNum3 / wNum2
;	wAns18 = dNum2 / wNum1
;	wRem18 = dNum2 % wNum1

mov ax, r11w
cwd
div r9w
mov word[wAns16], ax		;wAns16
mov ax, r10w
cwd
div r9w
mov word[wAns17], ax		;wAns17
mov ax, word[dNum2]
mov dx, word[dNum2+2]
div r8w
mov word[wAns18], ax		;wAns18
mov word[wRem18], dx		;wRem18

; -----
; signed word division
;	wAns19 = wNum6 / wNum5
;	wAns20 = wNum8 / wNum7
;	wAns21 = dNum7 / wNum5
;	wRem21 = dNum7 % wNum5

mov ax, r13w
cwd
idiv r12w
mov word[wAns19], ax		;wAns19
mov ax, r15w
cwd
idiv r14w
mov word[wAns20], ax		;wAns20
mov ax, word[dNum7]
mov dx, word[dNum7+2]
idiv r12w
mov word[wAns21], ax		;wAns21
mov word[wRem21], dx

; *****************************************
; Double-Word Operations

; -----
; unsigned double-word additions
;	dAns1  = dNum4 + dNum1
;	dAns2  = dNum3 + dNum2
;	dAns3  = dNum2 + dNum4

mov r8d, dword[dNum1]
mov r9d, dword[dNum2]
mov r10d, dword[dNum3]
mov r11d, dword[dNum4]

mov eax, r11d
add eax, r8d
mov dword[dAns1], eax		;dAns1
mov eax, r10d
add eax, r9d
mov dword[dAns2], eax		;dAns2
mov eax, r9d
add eax, r11d
mov dword[dAns3], eax		;dAns3

; -----
; signed double-word additions
;	dAns4  = dNum7 + dNum6
;	dAns5  = dNum7 + dNum5

mov r12d, dword[dNum5]
mov r13d, dword[dNum6]
mov r14d, dword[dNum7]
mov r15d, dword[dNum8]

mov eax, r14d
add eax, r13d
mov dword[dAns4], eax		;dAns4
mov eax, r14d
add eax, r12d
mov dword[dAns5], eax		;dAns5

; -----
; unsigned double-word subtractions
;	dAns6  = dNum4 - dNum2
;	dAns7  = dNum3 - dNum1
;	dAns8  = dNum2 - dNum1

mov eax, r11d
sub eax, r9d
mov dword[dAns6], eax		;dAns6
mov eax, r10d
sub eax, r8d
mov dword[dAns7], eax		;dAns7
mov eax, r9d
sub eax, r8d
mov dword[dAns8], eax		;dAns8

; -----
; signed double-word subtraction
;	dAns9  = dNum7 - dNum6
;	dAns10 = dNum7 – dNum5

mov eax, r14d
sub eax, r13d
mov dword[dAns9], eax		;dAns9
mov eax, r14d
sub eax, r12d
mov dword[dAns10], eax		;dAns10

; -----
; unsigned double-word multiplication
;	qAns11  = dNum3 * dNum3
;	qAns12  = dNum2 * dNum3
;	qAns13  = dNum1 * dNum4

mov eax, r10d
mul r10d
mov dword[qAns11], eax
mov dword[qAns11+4], edx	;qAns11
mov eax, r9d
mul r10d
mov dword[qAns12], eax
mov dword[qAns12+4], edx	;qAns12
mov eax, r8d
mul r11d
mov dword[qAns13], eax
mov dword[qAns13+4], edx	;qAns13

; -----
; signed double-word multiplication
;	qAns14  = dNum8 * dNum5
;	qAns15  = dNum7 * dNum6

mov eax, r15d
imul r12d
mov dword[qAns14], eax
mov dword[qAns14+4], edx	;qAns14
mov eax, r14d
mul r13d
mov dword[qAns15], eax
mov dword[qAns15+4], edx	;qAns15

; -----
; unsigned double-word division
;	dAns16 = dNum3 / dNum2
;	dAns17 = dNum4 / dNum1
;	dAns18 = qNum4 / dNum2
;	dRem18 = qNum4 % dNum2

mov eax, r10d
cdq
div r9d
mov dword[dAns16], eax		;dAns16
mov eax, r11d
cdq
div r8d
mov dword[dAns17], eax		;dAns17
mov eax, dword[qNum4]
mov edx, dword[qNum4+4]
div r9d
mov dword[dAns18], eax		;dAns18
mov dword[dRem18], edx		;dRem18

; -----
; signed double-word division
; signed double-word division
;	dAns19 = dNum8 / dNum6
;	dAns20 = dNum7 / dNum6
;	dAns21 = qNum8 / dNum5
;	dRem21 = qNum8 % dNum5

mov eax, r15d
cdq
idiv r13d
mov dword[dAns19], eax		;dAns19
mov eax, r14d
cdq
idiv r13d
mov dword[dAns20], eax		;dAns20
mov eax, dword[qNum8]
mov edx, dword[qNum8+4]
idiv r12d
mov dword[dAns21], eax		;dAns21
mov dword[dRem21], edx		;dRem21

; *****************************************
; QuadWord Operations

; -----
; unsigned quadword additions
;	qAns1  = qNum4 + qNum2
;	qAns2  = qNum3 + qNum1
;	qAns3  = qNum1 + qNum4

mov r8, qword[qNum1]
mov r9, qword[qNum2]
mov r10, qword[qNum3]
mov r11, qword[qNum4]

mov rax, r11
add rax, r9
mov qword[qAns1], rax		;qAns1
mov rax, r10
add rax, r8
mov qword[qAns2], rax		;qAns2
mov rax, r8
add rax, r11
mov qword[qAns3], rax		;qAns3

; -----
; signed quadword additions
;	qAns4  = qNum7 + qNum6
;	qAns5  = qNum8 + qNum5

mov r12, qword[qNum5]
mov r13, qword[qNum6]
mov r14, qword[qNum7]
mov r15, qword[qNum8]

mov rax, r14
add rax, r13
mov qword[qAns4], rax		;qAns4
mov rax, r15
add rax, r12
mov qword[qAns5], rax		;qAns5

; -----
; unsigned quadword subtractions
;	qAns6  = qNum4 - qNum3
;	qAns7  = qNum2 - qNum1
;	qAns8  = qNum3 - qNum2

mov rax, r11
sub rax, r10
mov qword[qAns6], rax		;qAns6
mov rax, r9
sub rax, r8
mov qword[qAns7], rax		;qAns7
mov rax, r10
sub rax, r9
mov qword[qAns8], rax		;qAns8

; -----
; signed quadword subtraction
;	qAns9  = qNum7 - qNum5
;	qAns10 = qNum8 - qNum6

mov rax, r14
sub rax, r12
mov qword[qAns9], rax		;qAns9
mov rax, r15
sub rax, r13
mov qword[qAns10], rax		;qAns10

; -----
; unsigned quadword multiplication
;	dqAns11  = qNum4 * qNum3
;	dqAns12  = qNum3 * qNum2
;	dqAns13  = qNum1 * qNum1

mov rax, r11
mul r10
mov qword[dqAns11], rax
mov qword[dqAns11+8], rdx	;dqAns11
mov rax, r10
mul r9
mov qword[dqAns12], rax
mov qword[dqAns12+8], rdx	;dqAns12
mov rax, r8
mul r8
mov qword[dqAns13], rax
mov qword[dqAns13+8], rdx	;dqAns13

; -----
; signed quadword multiplication
;	dqAns14  = qNum7 * qNum5
;	dqAns15  = qNum8 * qNum6
mov rax, r14
imul r12
mov qword[dqAns14], rax
mov qword[dqAns14+8], rdx	;dqAns14
mov rax, r15
imul r13
mov qword[dqAns15], rax
mov qword[dqAns15+8], rdx	;dqAns15

; -----
; unsigned quadword division
;	qAns16 = qNum4 / qNum2
;	qAns17 = qNum3 / qNum1
;	qAns18 = dqAns13 / qNum3
;	qRem18 = dqAns13 % qNum3

mov rax, r11
cqo
div r9
mov qword[qAns16], rax		;qAns16
mov rax, r10
cqo
div r8
mov qword[qAns17], rax		;qAns17
mov rax, qword[dqAns13]
mov rdx, qword[dqAns13+8]
div r10
mov qword[qAns18], rax		;qAns18
mov qword[qRem18], rdx		;qRem18

; -----
; signed quadword division
;	qAns19 = qNum7 / qNum5
;	qAns20 = qNum8 / qNum6
;	qAns21 = dqAns15 / qNum5
;	qRem21 = dqAns15 % qNum5

mov rax, r14
cqo
idiv r12
mov qword[qAns19], rax		;qAns19
mov rax, r15
cqo
idiv r13
mov qword[qAns20], rax		;qAns20
mov rax, qword[dqAns15]
mov rdx, qword[dqAns15+8]
idiv r12
mov qword[qAns21], rax		;qAns21
mov qword[qRem21], rdx		;qRem21

; *****************************************************************
;	Done, terminate program.

last:
	mov	rax, SYS_exit			; system call for exit (SYS_exit)
	mov	rdi, EXIT_SUCCESS		; return C/C++ style code (0)
	syscall

