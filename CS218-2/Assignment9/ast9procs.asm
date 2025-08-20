; *****************************************************************
;  Name: Alec Zheng
;  NSHE_ID: 2001982564
;  Section: 1003
;  Assignment: 9
;  Description: Read base 6 inputs and do math on them

; --------------------------------------------------------------------
;  Write some assembly language functions.

;  The value returning function estimatedMedian() returns the
;  median for a list of unsorted numbers.

;  The void function, oddEvenSort(), sorts the numbers into
;  ascending order (small to large).  Uses the odd/even sort
;  algorithm from assignment #7 (with sort order modified).

;  The void function, lstStats(), finds the sum, average, minimum,
;  maximum, and median for a list of numbers.  Results returned
;  via reference.

;  The value returning function, estimatedSkew(), computes the
;  skew statictic for the data set.  Summation for the
;  dividend must be performed as a quad.

; ******************************************************************************

section	.data

; -----
;  Define standard constants.

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
;  Define program specific constants.

SUCCESS 	equ	0
NOSUCCESS	equ	1
OUTOFRANGEMIN	equ	2
OUTOFRANGEMAX	equ	3
INPUTOVERFLOW	equ	4
ENDOFINPUT	equ	5

MIN_NUM		equ	1
MAX_NUM		equ	50000

BUFFSIZE	equ	50			; 50 chars including NULL

; -----
;  NO static local variables allowed...


; ****************************************************************************

section	.text

; -----------------------------------------------------------------------------
;  Read an ASCII senary number from the user.
;  Performs all error checking.

; -----
;  Call:
;	status = readSenaryNum(&numberRead);

;  Arguments Passed:
;	1) numberRead, addr

;  Returns:
;	number read (via reference)
;	return code

;  Return codes:
;	SUCCESS		Successful conversion and number within required range
;	NOSUCCESS	Invalid input entered (i.e., not a valid senaray number)
;	OUTOFRANGEMIN	Valid tetradecimal number, but below minimum value
;	OUTOFRANGEMAX	Valid tetradecimal number, but above maximum value
;	INPUTOVERFLOW	User entry character count exceeds maximum length
;	ENDOFINPUT	Return entered, no characters (for end of the input)



;	YOUR CODE GOES HERE
global readSenaryNum
readSenaryNum:
    push r14
    push r12
    push rbx                    ;save preserved registers
    push rbp
    mov rbp, rsp
    sub rsp, BUFFSIZE			;allocate locals
    dec rsp                     ;rsp = where the input is put before the buffer
    lea rbx, byte[rbp-BUFFSIZE]	;start of local array
    mov r12, 0                  ;r12 keeps track of how many inputs
    mov r14, rdi                ;numberRead moves to r14

    start:                      ;begin input loop
    mov rax, SYS_read
    mov rdi, STDIN
    lea rsi, byte[rsp]
    mov rdx, 1
    syscall                     ;call system input

    mov rcx, 0
    mov cl, byte[rsp]
    cmp cl, LF					;linefeed check
    je finish

	;size check
	inc r12
    cmp r12, BUFFSIZE			
    jg start                    ;if overflow then dont add to buffer

    dec r12	
    mov byte[rbx+r12], cl		;move input into buffer if everything is okay
	inc r12
    jmp start

    finish:
    cmp r12, 0                  ;checks if anything was put in before LF
    jne read                    ;if there are process the input
    mov rax, ENDOFINPUT			;if there is no more inputs
    jmp exitRead				;jump to the end
    read:
    cmp r12, BUFFSIZE           ;check the buffsize
    ja errorOver                

    ;Beginning of input proccessing
    mov byte[rbx+r12], NULL      ;adds a NULL to the end of the input
    mov r10, 0                   ;r10 checks if a space is between numbers
    mov rdx, 0

    legalCheck:
    mov al, byte[rbx+rdx]        ;check if the inputs are legal
    inc rdx
    cmp al, NULL                 ;if NULL exit loop
    je  legalExit
    cmp al, SPACE
    je spaceCheck                ;if the inout is a space check if legal
    cmp al, 0x30                 ;if less than 0 exit
    jl errorInvalid
    cmp al, 0x35                 ;if greater than 5 exit
    jg errorInvalid
    mov r10, 1
    jmp legalCheck
    legalExit:

    ;convert sentary number to base 10
    mov rax, 0
    mov rcx, 0
    mov r10, 6
    convert6to10:
	mov r8, 0
    mov r8b, byte[rbx+rcx]	    ;moves first character into al
    inc rcx
    cmp r8b, SPACE			    ;compares to space
    je convert6to10			    ;jump back to start if character is a space
    sub r8b, 0x30			    ;subtract ascii 0 if not
    add rax, r8				    ;adds value into rax
    mov r9b, byte[rbx+rcx]
    cmp r9b, NULL			    ;check if next char is null
    je convertExit			    ;exits loop if it is
	mov rdx, 0
    mul r10 				    ;multiplies by 6 if it isn't
    jmp convert6to10		    ;and then jumps back to the start
    convertExit:
    cmp rax, MIN_NUM            ;check if too small
    jl errMin
    cmp rax, MAX_NUM            ;check if too big
    jg errMax
    mov dword[r14], eax         ;if everything is good put it into the memory address
    mov rax, SUCCESS
    jmp exitRead

    errorOver:                  ;buffer overflow
    mov rax, INPUTOVERFLOW
    jmp exitRead

    errorInvalid:               ;invalid input
    mov rax, NOSUCCESS
    jmp exitRead

    errMin:                     ;below minimum
    mov rax, OUTOFRANGEMIN
    jmp exitRead

    errMax:                     ;above maximum
    mov rax, OUTOFRANGEMAX
    jmp exitRead

    spaceCheck:                 ;spaces checker
    cmp r10, 0
    jne errorInvalid
    jmp legalCheck

    exitRead:                   ;function will always exit here
    mov rsp, rbp
    pop rbp
    pop rbx
    pop r12
    pop r14
    ret

; ****************************************************************************
;  Sort data using odd/even sort.
;	Note, must update the odd/even sort algorithm to sort
;	in asending order

; -----
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

; -----
;  HLL Call:
;	oddEvenSort(list, len)

;  Arguments Passed:
;	- list, addr
;	- length, value

;  Returns:
;	sorted list (list passed by reference)


;	YOUR CODE GOES HERE
global oddEvenSort
oddEvenSort:
	push r15					;save r15
	push rbp
	mov rbp, rsp

	mov r15, FALSE				;r15 is "sorted" variable
	mov r8, rdi					;r8 = array
	mov r9d, esi				;r9 = length
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
	jbe oddLoop
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
	jbe evenLoop
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

	mov rsp, rbp
	pop rbp
	pop r15
	ret



; *******************************************************************************
;  Find the minimum, maximum, median, sum and average for a list of integers

;  Note, for an odd number of items, the median value is defined as
;  the middle value.  For an even number of values, it is the integer
;  average of the two middle values.

;  Note, assumes the list is already sorted in desending order.

; -----
;  HLL Call:
;	listStats(list, len, &min, &max, &med)

;  Arguments Passed:
;	- list, addr
;	- length, value
;	- minimum, addr
;	- maximum, addr
;	- median, addr
;	- sum, addr
;	- ave, addr (stack)
;  Returns:
;	minimum, maximum, median, sum, and average (via reference)


;	YOUR CODE GOES HERE
global listStats
listStats:
    push rbp
	mov rbp, rsp

	mov r10d, dword[rdi]
	mov dword[rdx], r10d			;max
	mov r11, 0
	mov r11d, esi
	dec r11d
	mov r10d, dword[rdi+r11*4]
	mov dword[rcx], r10d			;min
	call estimatedMedian			;reuse estMed function 
	mov dword[r8], eax				;estMed
	mov r10, 0
	mov r11, 0
	mov r11d, esi
	dec r11
	listSum:						;sum loop
	cmp r11, 0
	jl sumExit
	add r10d, dword[rdi+r11*4]
	dec r11
	jmp listSum
	sumExit:
	mov dword[r9], r10d
	mov r11d, esi 
	mov rax, r10
	mov rdx, 0
	div r11d						;average divide
	mov r11, qword[rbp+16]
	mov dword[r11], eax				;average

	pop rbp
	ret

; *******************************************************************************
;  Find the estimated median (before sort)

;  Even formula
;	est median = (arr[len/2] + arr[len/2-1]) / 2
;  Odd formula
;	est median = arr[len/2]

; -----
;  HLL Call:
;	estMed = estimatedMedian(list, len)

;  Arguments Passed:
;	- list, addr
;	- length, value

;  Returns:
;	estimated median (in eax)


;	YOUR CODE GOES HERE
global estimatedMedian
estimatedMedian:

	mov rax, 0
	mov r10, 0
	mov eax, esi
	mov rdx, 0
	mov r10, 2
	div r10d					;length / 2
	mov r10d, dword[rdi+rax*4]	;arr[len/2]
	cmp rdx, 0					;if length is even, add len/2-1
	jne medEvenSkip
	dec rax
	add r10d, dword[rdi+rax*4] 	;arr[len/2-1]
	mov r11, 2
	mov eax, r10d
	mov rdx, 0                  ;div even len lists by 2
	div r11d
	ret
	medEvenSkip:                ;skip above if odd len
	mov rax, r10

	ret


; ****************************************************************************
;  Function to calculate the estimated skew value based on the 
;  formula:
;			  sum (lst[i] - average)^2
;		 skew  =  ------------------------
;				  len * 3

;   The subtraction (lst[i]-average may result in a negative value
;   and an IMIL must be used for perform the squaring which will
;   result in a positive value.
;   The summation must be performed as a quad-word.

; -----
;  HLL Call:
;	skew = estimatedSkew(list, len, ave)

;  Arguments Passed:
;	- list, addr
;	- length, value
;	- average, value

;  Returns:
;	skew value (in eax)


;	YOUR CODE GOES HERE
global estimatedSkew
estimatedSkew:
	mov r9, rdx						;mov average out of a used register
	mov rcx, 0
	mov rcx, rsi					;move length to rcx for counting
	mov rax, 0
	mov r10, 0
	skewLoop:
	dec rcx							
	mov eax, dword[rdi+rcx*4]		;eax = list(i)
	sub rax, r9						;list(i) - ave
	imul eax	 					;(list(i) - ave)^2
	add r10, rax					;r10 is sum register
	cmp rcx, 0
	jg skewLoop
	mov rax, rsi
	mov rcx, 3						;len*3
	imul rcx
	mov rcx, rax
	mov rax, r10
	idiv rcx						;all that/len*3
	ret

; ****************************************************************************

