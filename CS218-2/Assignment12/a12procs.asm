; *****************************************************************
;  Name: Alec Zheng
;  NSHE_ID: 2001982564
;  Section: 1003
;  Assignment: 12
;  Description: Multi-threaded programs and smith numbers

; -----
;  Example Smith Number Count for 1 to 200: 8
;	4	22	27	58
;	85	94	121	166

; ***************************************************************

section	.data

; -----
;  Define standard constants.

LF		equ	10			; line feed
NULL		equ	0			; end of string
ESC		equ	27			; escape key

TRUE		equ	1
FALSE		equ	0

SUCCESS		equ	0			; Successful operation
NOSUCCESS	equ	1			; Unsuccessful operation

STDIN		equ	0			; standard input
STDOUT		equ	1			; standard output
STDERR		equ	2			; standard error

SYS_read	equ	0			; call code for read
SYS_write	equ	1			; call code for write
SYS_open	equ	2			; call code for file open
SYS_close	equ	3			; call code for file close
SYS_fork	equ	57			; call code for fork
SYS_exit	equ	60			; call code for terminate
SYS_creat	equ	85			; call code for file open/create
SYS_time	equ	201			; call code for get time

; -----
;  Globals (used by threads)

currentIndex	dq	1
myLock		dq	0

; -----
;  Local variables for thread function(s).

msgThread1	db	" ...Thread starting...", LF, NULL

; -----
;  Local variables for getArgs function

THREAD_MIN	equ	1
THREAD_MAX	equ	8
LIMIT_MIN	equ	10
LIMIT_MAX	equ	4000000000

errUsage	db	"Usage: ./smithNums -t <senaryNumber> ",
		db	"-l <senaryNumber>", LF, NULL
errOptions	db	"Error, invalid command line options."
		db	LF, NULL
errLSpec	db	"Error, invalid limit specifier."
		db	LF, NULL
errLValue	db	"Error, invalid limit value."
		db	LF, NULL
errLRange	db	"Error, limit out of range."
		db	LF, NULL
errTSpec	db	"Error, invalid thread count specifier."
		db	LF, NULL
errTValue	db	"Error, invalid thread count value."
		db	LF, NULL
errTRange	db	"Error, thread count out of range."
		db	LF, NULL

; -----
;  Local variables for aSenary2int function

qSix		dq	6
qTen		dq	10
tmpNum		dq	0


; ***************************************************************

section	.text

; ******************************************************************
;  Function getArgs()
;	Get, check, convert, verify range, and return the
;	sequential/parallel option and the limit.

;  Example HLL call:
;	stat = getArgs(argc, argv, &thdCount, &userLimit)

;  This routine performs all error checking, conversion of ASCII/senary
;  to integer, verifies legal range.
;  For errors, applicable message is displayed and FALSE is returned.
;  For good data, all values are returned via addresses with TRUE returned.

;  Command line format (fixed order):
;	-t <senaryNumber> -l <senaryNumber>

; -----
; *WARNING:*	The aSenary2int funciton returns a quad.
;		When returning the userLimit, return the full quad value.
;		When returning the thread count, return only the dword
;		portion of the quad result.

; -----
;  Arguments:
;	1) ARGC, value
;	2) ARGV, address
;	3) thread count (dword), address
;	4) user limit (qword), address
global getArgs
getArgs:

push rbp
mov rbp, rsp
push r15
push r14
push r13
push r12							;save preserved registers

;check argument count
cmp rdi, 1							;Check for 0 arguments
jne ARGC0Check
mov rdi, errUsage
call printString
jmp errEXIT
ARGC0Check:

cmp rdi, 5  						;Check for 3 arguments
je ARGCCheck						;if not 
mov rdi, errOptions
call printString
jmp errEXIT
ARGCCheck:



;check arguments
mov r12, rdi
mov r13, rdx
mov r14, rcx
mov rdx, qword[rsi+1*8]				;ARGV[1] check
mov r8b, [rdx]
cmp r8b, 0x2D						;check "-"
jne ARGV1Check
mov r8b, [rdx+1]
cmp r8b, 0x74						;check 't' 
jne ARGV1Check
mov r8b, [rdx+2]
cmp r8b, NULL						;check NULL 
jne ARGV1Check

mov rdx, qword[rsi+3*8]				;ARGV[3] check
mov r8b, [rdx]
cmp r8b, 0x2D						;check "-"
jne ARGV3Check
mov r8b, [rdx+1]
cmp r8b, 0x6C						;check 'l' 
jne ARGV3Check
mov r8b, [rdx+2]
cmp r8b, NULL						;check NULL
jne ARGV3Check



mov r10, [rsi+2*8]					;ARGV[2] Check
mov rax, 0
mov rcx, 6
mov r8, 0
ARGV2Loop:
mov r8b, [r10]
cmp r8b, 0x30						;cmp to ascii 0
jl ARGV2Value
cmp r8b, 0x35						;cmp to ascii 5
jg ARGV2Value						;mul rax by 6 before adding the new number
sub r8b, 0x30						;subtract ascii 0
add rax, r8							;adds value into rax
inc r10
mov r8b, [r10]
cmp r8b, NULL
je ARGV2Exit
mul rcx
jmp ARGV2Loop
ARGV2Exit:
cmp rax, THREAD_MAX					;check if over
jg ARGV2Range
cmp rax, THREAD_MIN					;or under
jl ARGV2Range
mov dword[r13], eax

mov r10, [rsi+4*8]					;ARGV[4] value check
ARGV4Loop:
mov r8b, [r10]
cmp r8b, NULL						;cmp r8 to null
je ARGV4Exit						;exit loop if true
cmp r8b, 0x30						;cmp to ascii 0
jl ARGV4Value
cmp r8b, 0x35						;cmp to ascii 5
jg ARGV4Value
inc r10
jmp ARGV4Loop
ARGV4Exit:

mov rdi, [rsi+4*8]					;ARGV[4] conversion and range check
mov rsi, r14
call aSenary2int
cmp rax, FALSE
je ARGV4Range



;EXIT
pop r12
pop r13
pop r14
pop r15
mov rsp, rbp
pop rbp
mov rax, TRUE
ret

ARGV1Check:						;invalid t spec
mov rdi, errTSpec
call printString
jmp errEXIT

ARGV2Value:						;invalid t value
mov rdi, errTValue
call printString
jmp errEXIT

ARGV2Range:						;invalid t range
mov rdi, errTRange
call printString
jmp errEXIT

ARGV3Check:						;invalid l spec
mov rdi, errLSpec
call printString
jmp errEXIT

ARGV4Value:						;invalid l value
mov rdi, errLValue	
call printString
jmp errEXIT

ARGV4Range:						;invalid l range
mov rdi, errLRange	
call printString

errEXIT:							;All errors exit here
pop r12
pop r13
pop r14
pop r15
mov rsp, rbp
pop rbp
mov rax, FALSE
ret

; ******************************************************************
;  Function: Check and convert ASCII/senary to integer.

;  Example HLL Call:
;	bool = aSenary2int(senaryStr, &num);
global aSenary2int
aSenary2int:

mov rax, 0
mov rcx, 0
mov r10, 6
convert6to10:
mov r8, 0
mov r8b, [rdi+rcx]		;moves first character into r8b
inc rcx
sub r8b, 0x30			;subtract ascii 0
add rax, r8				;adds value into rax
mov r9b , byte[rdi+rcx]
cmp r9b, NULL			;check if next char is null
je exit					;exits loop if it is
mul r10d				;multiplies by 6 if it isn't
jmp convert6to10		;and then jumps back to the start

exit:
cmp rax, LIMIT_MAX		;check limit is in bounds
ja err
cmp rax, LIMIT_MIN
jl err
mov qword[rsi], rax
mov rax, TRUE
ret

err:
mov rax, FALSE
ret



; ******************************************************************
;  Thread function, findSmithNumberCount()
;	Determine count of smith numbers for all values between
;	1 and userLimit (globally available)

; -----
;  Arguments:
;	N/A (global variable accessed)
;  Returns:
;	N/A (global variable accessed)

common	userLimit		1:8
common	smithNumberCount	1:8


global findSmithNumberCount
findSmithNumberCount:
push r12
push r13
push r14

mov rdi, msgThread1						;print starting message
call printString

start:
call spinLock						
mov r12, qword[currentIndex]			;get currentIndex
mov r11, qword[userLimit]
cmp r12, r11							;check it against user limit
ja smithExit
inc r12
mov qword[currentIndex], r12			;inc currentIndex
dec r12
call spinUnlock

mov rdi, r12							;isPrime call
call isPrime
cmp rax, TRUE
je start

mov rdi, r12							;findSumOfDigits call
call findSumOfDigits
mov r13, rax							;r13 = findSumofDigits

mov rdi, r12							;findSumPrimeFactors
call findSumPrimeFactors
mov r14, rax							;r14 = findSumPrimeFactors           

cmp r13, r14
jne start

call spinLock							
mov rax, qword[smithNumberCount]		;inc numbercount by 1
inc rax
mov qword[smithNumberCount], rax
call spinUnlock

jmp start


smithExit:
call spinUnlock
pop r14
pop r13
pop r12
ret



; ******************************************************************
;  Check if prime function -> isPrime()

;	if (n <= 1)
;		return false;
;	for (int i = 2; i <= n/2; i++)
;		if (n % i == 0)
;			return false;
;	return true;

; -----
; Arguments
;	number

; Returns
;	TRUE / FALSE
global isPrime
isPrime:

cmp rdi, 1
jle primeFalse

mov rax, rdi
mov rdx, 0
mov r10, 2
div r10
mov r10, rax							;r10 = n/2
mov r11, 2								;r11 = i

primeLoop:
cmp r11, r10							;check if i > n/2
ja primeExit
mov rax, rdi
mov rdx, 0
div r11									;div n by i
cmp rdx, 0								;check remainder
je primeFalse
inc r11
jmp primeLoop

primeExit:								;if the number passes spec
mov rax, TRUE
ret

primeFalse:								;if rem = 0 at any point
mov rax, FALSE
ret



; ******************************************************************
;  Find sum of digits for given number -> findSumOfDigits()
;  Sum digits for number.
;	set sumDigits = 0
;	set tmp = n
;	while tmp > 0 repeat
;		set sumDigits = sumDigits + (tmp mod 10)
;		set tmp = tmp / 10

; -----
;  Arguments:
;	number

;  Returns
;	sum (in rax)
global findSumOfDigits
findSumOfDigits:

mov r10, 0					;sum variable
mov r11, 10
mov rax, rdi

sumLoop:
cmp rax, 0					;while n > 0
jle sumExit
mov rdx, 0
div r11						;n/10
add r10, rdx				;sum += n%10
jmp sumLoop

sumExit:
mov rax, r10
ret



; ******************************************************************
;  Find sum of prime factors -> findSumPrimeFactors()

;	int i = 2, sum = 0;
;	while (n > 1) {
;		if (n % i == 0) {
;			sum = sum + findSumOfDigit(i);
;			n = n / i;
;		} else {
;			do {
;				i++;
;			} while (!isPrime(i));
;		}
;	}
;	return sum;

; -----
;  Arguments:
;	number

;  Returns
;	sum (in rax)

global findSumPrimeFactors
findSumPrimeFactors:
	push	rbx
	push	r12
	push	r13

	mov	rbx, rdi			; save n
	mov	r12, 2				; i=2
	mov	r13, 0				; sum=0

;	while (n > 1) {
primeFactorsLoop:
	cmp	rbx, 1
	jle	primeFactorsDone

;	if ((n % i) == 0) {
	mov	rax, rbx
	mov	rdx, 0
	div	r12
	cmp	rdx, 0
	jne	notDivisible

primeDigitsLoop:
	mov	rdi, r12
	call	findSumOfDigits
	add	r13, rax			; sum += findSumOfDigit(i);

;	n = n / i;
	mov	rax, rbx
	mov	rdx, 0
	div	r12
	mov	rbx, rax
	jmp	primeIfDone

notDivisible:					; } else {
;	do { i++; } while (!isPrime(i));
	inc	r12
	mov	rdi, r12
	call	isPrime
	cmp	rax, TRUE
	jne	notDivisible

primeIfDone:
	jmp	primeFactorsLoop		;; // end while

primeFactorsDone:
	mov	rax, r13			; return sum;

	pop	r13
	pop	r12
	pop	rbx
	ret

; ******************************************************************
;  Mutex lock
;	checks lock (shared global variable)
;		if unlocked, sets lock
;		if locked, lops to recheck until lock is free

global	spinLock1
spinLock:
	mov	rax, 1			; Set the REAX register to 1.

lock	xchg	rax, qword [myLock]	; Atomically swap the RAX register with
					;  the lock variable.
					; This will always store 1 to the lock, leaving
					;  the previous value in the RAX register.

	test	rax, rax	        ; Test RAX with itself. Among other things, this will
					;  set the processor's Zero Flag if RAX is 0.
					; If RAX is 0, then the lock was unlocked and
					;  we just locked it.
					; Otherwise, RAX is 1 and we didn't acquire the lock.

	jnz	spinLock		; Jump back to the MOV instruction if the Zero Flag is
					;  not set; the lock was previously locked, and so
					; we need to spin until it becomes unlocked.
	ret

; ******************************************************************
;  Mutex unlock
;	unlock the lock (shared global variable)

global	spinUnlock
spinUnlock:
	mov	rax, 0			; Set the RAX register to 0.

	xchg	rax, qword [myLock]	; Atomically swap the RAX register with
					;  the lock variable.
	ret

; ******************************************************************
;  Generic function to display a string to the screen.
;  String must be NULL terminated.
;  Algorithm:
;	Count characters in string (excluding NULL)
;	Use syscall to output characters

;  Arguments:
;	- address, string
;  Returns:
;	nothing

global	printString
printString:

; -----
; Count characters to write.

	mov	rdx, 0
strCountLoop:
	cmp	byte [rdi+rdx], NULL
	je	strCountLoopDone
	inc	rdx
	jmp	strCountLoop
strCountLoopDone:
	cmp	rdx, 0
	je	printStringDone

; -----
;  Call OS to output string.

	mov	rax, SYS_write			; system code for write()
	mov	rsi, rdi			; address of characters to write
	mov	rdi, STDOUT			; file descriptor for standard in
						; rdx=count to write, set above
	syscall					; system call

; -----
;  String printed, return to calling routine.

printStringDone:
	ret

; ******************************************************************

