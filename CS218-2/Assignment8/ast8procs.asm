; *****************************************************************************
;  Name: Alec Zheng
;  NSHE_ID: 2001982564
;  Section: 1003
;  Assignment: 8
;  Description: program control instructions, function handling, and stack usage.


; --------------------------------------------------------------------
;  Write assembly language functions.

;  * Function oddEvenSort() sorts the numbers into descending order
;	(large to small).

;  * Function listStats() finds the minimum, maximum, and median for a
;	list of numbers.

;  * Function listSum() to find and return the sum of a list of numbers.

;  * Function estimatedMedian() to find and return the estimated median
;	of a list of numbers.

;  * Function estimatedSkew() finds the estimated skew value based on the 
;	formula:
;			  sum (lst[i] - average)^2
;		 skew  =  --------------------------
;				  len * 3
;	The summation must be performed as a quad-word.


; ============================================================================

section	.data

; -----
;  Define constants.

TRUE		equ	1
FALSE		equ	0

; -----
;  Local variables for oddEvenSort() function.

weight		dd	12
dtwo		dd	2
ddTen		dd	10
ddTwelve	dd	12
dNine		dd	9

; -----
;  Local variables for lstStats() function (if any).



section	.bss

; -----
;  Unitialized variables.

qSum		resq	1
qTmp		resq	1


; ============================================================================

section	.text

; *****************************************************************************
;  Sort data using odd/even sort.
;	Note, must update the odd/even sort algorithm to sort
;	in desending order

; -----
;  function oddEvenSort(list) {
;	bool sorted = false;

;	while (!sorted) {
;		sorted = true;
;		for (var i=1; i < len-2; i+=2) {
;			if (list[i] > list[i+1]) {
;			swap(list, i, i+1);
;			sorted = false;
;			}
;		}
;		for (var i=0; i < len-2; i+=2) {
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

global	oddEvenSort
oddEvenSort:


;	YOUR CODE GOES HERE
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

	mov rsp, rbp
	pop rbp
	pop r15
	ret

; *****************************************************************************
;  Find the minimum, maximum, median, sum and average for a list of integers

;  Note, for an odd number of items, the median value is defined as
;  the middle value.  For an even number of values, it is the integer
;  average of the two middle values.

;  Note, assumes the list is already sorted in desending order.

; -----
;  HLL Call:
;	listStats(list, len, &min, &max, &med)

;  Arguments Passed:
;	- list, addr - rdi
;	- length, value - esi
;	- minimum, addr - rdx
;	- maximum, addr - rcx
;	- median, addr - r8
;	- sum, addr - r9
;	- ave, addr - stack
;  Returns:
;	minimum, maximum, median, sum, and average (via reference)

global listStats
listStats:


;	YOUR CODE GOES HERE
	push rbp
	mov rbp, rsp

	mov r10d, dword[rdi]
	mov dword[rcx], r10d			;max
	mov r11, 0
	mov r11d, esi
	dec r11d
	mov r10d, dword[rdi+r11*4]
	mov dword[rdx], r10d			;min
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

; *****************************************************************************
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

global estimatedMedian
estimatedMedian:


;	YOUR CODE GOES HERE
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
	add r10d, dword[rdi+rax*4] 	;;arr[len/2-1]
	mov r11, 2
	mov eax, r10d
	mov rdx, 0
	div r11d
	ret
	medEvenSkip:
	mov rax, r10

	ret


; *****************************************************************************
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

global estimatedSkew
estimatedSkew:


;	YOUR CODE GOES HERE
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

; *****************************************************************************