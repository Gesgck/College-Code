; *****************************************************************
;  Name: Alec Zheng
;  NSHE_ID: 2001982564
;  Section: 1003
;  Assignment: 11
;  Description: Image manipulation from command line arguments


; ***********************************************************************
;  Data declarations
;	Note, the error message strings should NOT be changed.
;	All other variables may changed or ignored...

; ***********************************************************************
;  Data declarations
;	Note, the error message strings should NOT be changed.
;	All other variables may changed or ignored...

section	.data

; -----
;  Define standard constants.

LF		equ	10			; line feed
NULL		equ	0			; end of string
SPACE		equ	0x20			; space

TRUE		equ	1
FALSE		equ	0

SUCCESS		equ	0			; Successful operation
NOSUCCESS	equ	1			; Unsuccessful operation

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

O_CREAT		equ	0x40
O_TRUNC		equ	0x200
O_APPEND	equ	0x400

O_RDONLY	equ	000000q			; file permission - read only
O_WRONLY	equ	000001q			; file permission - write only
O_RDWR		equ	000002q			; file permission - read and write

S_IRUSR		equ	00400q
S_IWUSR		equ	00200q
S_IXUSR		equ	00100q

; -----
;  Define program specific constants.

GRAYSCALE	equ	0
BRIGHTEN	equ	1
DARKEN		equ	2

MIN_FILE_LEN	equ	5
BUFF_SIZE	equ	2			; buffer size

; -----
;  Local variables for getArguments() function.

eof		db	FALSE

usageMsg	db	"Usage: ./imageCvt <-gr|-br|-dk> <inputFile.bmp> "
		db	"<outputFile.bmp>", LF, NULL
errIncomplete	db	"Error, incomplete command line arguments.", LF, NULL
errExtra	db	"Error, too many command line arguments.", LF, NULL
errOption	db	"Error, invalid image processing option.", LF, NULL
errReadName	db	"Error, invalid source file name.  Must be '.bmp' file.", LF, NULL
errWriteName	db	"Error, invalid output file name.  Must be '.bmp' file.", LF, NULL
errReadFile	db	"Error, unable to open input file.", LF, NULL
errWriteFile	db	"Error, unable to open output file.", LF, NULL

; -----
;  Local variables for processHeaders() function.

HEADER_SIZE	equ	54

errReadHdr	db	"Error, unable to read header from source image file."
		db	LF, NULL
errFileType	db	"Error, invalid file signature.", LF, NULL
errDepth	db	"Error, unsupported color depth.  Must be 24-bit color."
		db	LF, NULL
errCompType	db	"Error, only non-compressed images are supported."
		db	LF, NULL
errSize		db	"Error, bitmap block size inconsistent.", LF, NULL
errWriteHdr	db	"Error, unable to write header to output image file.", LF,
		db	"Program terminated.", LF, NULL

; -----
;  Local variables for getRow() function.

buffMax		dq	BUFF_SIZE
curr		dq	BUFF_SIZE
wasEOF		db	FALSE
pixelCount	dq	0

errRead		db	"Error, reading from source image file.", LF,
		db	"Program terminated.", LF, NULL

; -----
;  Local variables for writeRow() function.

errWrite	db	"Error, writting to output image file.", LF,
		db	"Program terminated.", LF, NULL


; ------------------------------------------------------------------------
;  Unitialized data

section	.bss

localBuffer	resb	BUFF_SIZE
header		resb	HEADER_SIZE


; ############################################################################

section	.text

; ***************************************************************
;  Routine to get arguments.
;	Check image conversion options
;	Verify files by atemptting to open the files (to make
;	sure they are valid and available).

;  NOTE:
;	ENUM vaiables are 32-bits.

;  Command Line format:
;	./imageCvt <-gr|-br|-dk> <inputFileName> <outputFileName>

; -----
;  Arguments:
;	argc (value)
;	argv table (address)
;	image option variable, ENUM type, (address)
;	read file descriptor (address)
;	write file descriptor (address)
;  Returns:
;	TRUE or FALSE


;	YOUR CODE GOES HERE
global getArguments
getArguments:

push rbp
mov rbp, rsp
push r15
push r14
push r13
push r12							;save preserved registers

;check arguments
cmp rdi, 1							;Check for 0 arguments
jne ARGC0Check
mov rdi, usageMsg
call printString
jmp errEXIT
ARGC0Check:

cmp rdi, 4  						;Check for 3 arguments
jl ARGClow
jg ARGChigh
jmp ARGCCheck
ARGClow:							;if less
mov rdi, errIncomplete
call printString
jmp errEXIT
ARGChigh:							;if high
mov rdi, errExtra
call printString
jmp errEXIT
ARGCCheck:



;checking if specifiers are present and correct
mov r12, rdx
mov r13, rcx
mov r14, r8
mov r15, rsi
mov rdx, qword[rsi+1*8]				;ARGV[1] check
mov r8b, [rdx]
cmp r8b, 0x2D						;check "-"
jne ARGV1Check

mov r8b, [rdx+1]					;check "-gr"
cmp r8b, 0x67						;check "g"
jne ARGV1first
mov r8b, [rdx+2]
cmp r8b, 0x72						;check "r"
jne ARGV1Check
mov r8b, [rdx+3]
cmp r8b, NULL						;check NULL
jne	ARGV1Check
mov dword[r12], GRAYSCALE
jmp ARGV1

ARGV1first:							;if not "-gr" check if "-br"
mov r8b, [rdx+1]
cmp r8b, 0x62						;check "b"
jne ARGV1second
mov r8b, [rdx+2]
cmp r8b, 0x72						;check "r"
jne ARGV1Check
mov r8b, [rdx+3]
cmp r8b, NULL						;check NULL
jne	ARGV1Check
mov dword[r12], BRIGHTEN
jmp ARGV1

ARGV1second:						;if not "-br", check "-dk"
mov r8b, [rdx+1]
cmp r8b, 0x64						;check "d"
jne ARGV1Check
mov r8b, [rdx+2]
cmp r8b, 0x6B						;check "k"
jne ARGV1Check
mov r8b, [rdx+3]
cmp r8b, NULL						;check NULL
jne	ARGV1Check
mov dword[r12], DARKEN
jmp ARGV1

ARGV1Check:							;none of the above or fails a check
mov rdi, errOption
call printString
jmp errEXIT
ARGV1:



;check input file format
mov r10, qword[rsi+2*8]
mov r11, 0
mov r11b, byte[r10]
periodLoop:
cmp r11b, 0x2E						;loop to get to where the period is
je periodExit
cmp r11b, NULL						;if there is no period at all
je ARGV2name
inc r10
mov r11b, byte[r10]
jmp periodLoop
periodExit:

inc r10								;check file format
mov r11b, byte[r10]
cmp r11b, 0x62						;check 'b'
jne ARGV2name
inc r10
mov r11b, byte[r10]
cmp r11b, 0x6D						;check 'm'
jne ARGV2name
inc r10
mov r11b, byte[r10]
cmp r11b, 0x70						;check 'p'
jne ARGV2name
jmp ARGV2namegood

ARGV2name:							;if name is wrong
mov rdi, errReadName
call printString
jmp errEXIT
ARGV2namegood:



;check output file format
mov r10, qword[rsi+3*8]
mov r11b, byte[r10]
period2Loop:
cmp r11b, 0x2E						;loop to get to where the period is
je period2Exit
cmp r11b, NULL						;if there is no period at all error out
je ARGV3name
inc r10
mov r11b, byte[r10]
jmp period2Loop
period2Exit:	

inc r10								;check file format
mov r11b, byte[r10]
cmp r11b, 0x62						;check 'b'
jne ARGV3name
inc r10
mov r11b, byte[r10]
cmp r11b, 0x6D						;check 'm'
jne ARGV3name
inc r10
mov r11b, byte[r10]
cmp r11b, 0x70						;check 'p'
jne ARGV3name
jmp ARGV3namegood

ARGV3name:							;if name is wrong
mov rdi, errWriteName
call printString
jmp errEXIT
ARGV3namegood:



;Attempt to open input file
mov rax, SYS_open					;ARGV[2] check
mov rdi, qword[r15+2*8]
mov rsi, O_RDONLY
syscall

cmp rax, 0							;check if open success
jl ARGV2Check
mov dword[r13], eax
jmp ARGV2

ARGV2Check:
mov rdi, errReadFile
call printString
jmp errEXIT
ARGV2:



;Attempt to open output file
mov rax, SYS_creat					;ARGV[3] check
mov rdi, qword[r15+3*8]
mov rsi, S_IRUSR | S_IWUSR
syscall

cmp rax, 0							;check if open success
jl ARGV3Check
mov dword[r14], eax
jmp ARGV3

ARGV3Check:
mov rdi, errWriteFile
call printString
jmp errEXIT
ARGV3:



;EXIT
pop r12
pop r13
pop r14
pop r15
pop rbp
mov rax, TRUE
ret

errEXIT:							;All errors exit here
pop r12
pop r13
pop r14
pop r15
pop rbp
mov rax, FALSE
ret

; ***************************************************************
;  Read and verify header information
;	status = processHeaders(readFileDesc, writeFileDesc,
;				fileSize, picWidth, picHeight)

; -----
;  2 -> BM				(+0)
;  4 file size				(+2)
;  4 skip				(+6)
;  4 header size			(+10)
;  4 skip				(+14)
;  4 width				(+18)
;  4 height				(+22)
;  2 skip				(+26)
;  2 depth (16/24/32)			(+28)
;  4 compression method code		(+30)
;  4 bytes of pixel data		(+34)
;  skip remaing header entries

; -----
;   Arguments:
;	read file descriptor (value)
;	write file descriptor (value)
;	file size (address)
;	image width (address)
;	image height (address)

;  Returns:
;	file size (via reference)
;	image width (via reference)
;	image height (via reference)
;	TRUE or FALSE


;	YOUR CODE GOES HERE
global processHeaders
processHeaders:
	push rbp
	mov rbp, rsp
    push r15
	push r14
	push r13
	push r12							;save preserved registers

	mov r12, rsi
	mov r13, rdx
	mov r14, rcx
	mov r15, r8							;save arguments from syscall

	mov rax, SYS_read					;read the header into the buffer
	lea rsi, byte[header]
	mov rdx, HEADER_SIZE
	syscall

	cmp rax, HEADER_SIZE				;make sure it read it all
	jne headerBad

	lea r8, byte[header]

	;check for "BM" signature
	mov r10b, byte[r8]
	cmp r10b, 0x42
	jne sigErr
	mov r10b, byte[r8+1]
	cmp r10b, 0x4D
	jne sigErr
	jmp sign
	sigErr:
	mov rdi, errFileType
	call printString
	jmp headererrExit
	sign:

	;save the file size
	add r8, 2							
	mov r10d, dword[r8]
	mov dword[r13], r10d

	;header save for later
	add r8, 8
	mov r11d, dword[r8]

	;chech the color depth
	add r8, 18
	mov r10w, word[r8]
	cmp r10w, 24
	jne colorerror
	jmp color
	colorerror:
	mov rdi, errDepth
	call printString
	jmp headererrExit
	color:

	;check compression
	add r8, 2
	mov r10d, dword[r8]
	cmp r10d, 0
	jne compErr
	jmp comp
	compErr:
	mov rdi, errCompType
	call printString
	jmp headererrExit
	comp:

	;add size of img to header size and check it
	add r8, 4
	add r11d, dword[r8]
	mov r10d, dword[r13]
	cmp r10d, r11d
	jne sizeErr
	jmp sizeGood
	sizeErr:
	mov rdi, errSize
	call printString
	jmp headererrExit
	sizeGood:

	;save width and height
	sub r8, 16
	mov r10d, dword[r8]
	mov dword[r14], r10d						;width
	add r8, 4
	mov r10d, dword[r8]
	mov dword[r15], r10d						;height
	sub r8, 22									;mov r8 back to the begining for the next part

	;write header to the output
	mov rax, SYS_write
	mov rdi, r12
	mov rsi, r8
	mov rdx, HEADER_SIZE
	syscall

	cmp rax, 0
	jl headerWriteErr

	headerExit:
	pop r12
	pop r13
	pop r14
	pop r15
	mov rsp, rbp
	pop rbp
	mov rax, TRUE
	ret

	headerBad:
	mov rdi, errReadHdr					;error reading header
	call printString
	jmp headererrExit

	headerWriteErr:
	mov rdi, errWriteHdr
	syscall

	headererrExit:
	pop r12
	pop r13
	pop r14
	pop r15
	mov rsp, rbp
	pop rbp
	mov rax, FALSE
	ret

; ***************************************************************.
;  Return a row from read buffer
;	This routine performs all buffer management

; ----
;  HLL Call:
;	status = getRow(readFileDesc, picWidth, rowBuffer);

;   Arguments:
;	read file descriptor (value)
;	image width (value)
;	row buffer (address)
;  Returns:
;	TRUE or FALSE

; -----
;  This routine returns TRUE when row has been returned
;	and returns FALSE only if there is an
;	error on read (which would not normally occur)
;	or the end of file.

;  The read buffer itself and some misc. variables are used
;  ONLY by this routine and as such are not passed.


;	YOUR CODE GOES HERE
global getRow
getRow:
	push rbp
	mov rbp, rsp
	push r12
	push r13
	push r14
	push r15

	mov r12, rdi					;save file descriptor
	mov r14, rdx					;save row buffer
	mov rax, rsi
	mov rcx, 3
	mul rcx
	mov r13, rax					;save width * 3mak
	mov qword[pixelCount], 0		;set pixelcount to 0 every function call


	mov r10, qword[curr]			;check if more data needs to be read
	mov r11, qword[buffMax]
	cmp r10, r11
	jl proccessingproto


	read:
	cmp byte[eof], TRUE				;check if eof
	je readFalse
	mov rax, SYS_read				;read BUFF_SIZE bytes into localBuffer
	mov rdi, r12
	mov rsi, localBuffer
	mov rdx, BUFF_SIZE
	syscall

	cmp rax, 0						;error checking
	jl readErr

	cmp rax, BUFF_SIZE				;check if eof
	je	noteof
	mov byte[eof], TRUE				;set flag if eof
	mov qword[buffMax], rax

	noteof:
	mov qword[curr], 0				;reset curr after a read


	proccessingproto:
	mov r8, qword[curr]				;set up registers for the proccessing loop
	mov r9, qword[pixelCount]
	lea r10, qword[localBuffer]
	mov r11, r14

	proccessing:
	cmp r8, qword[buffMax]			;check if curr has passed buffMax
	jge read
	mov cl, byte[r10+r8]			;pull a byte from localBuffer
	mov byte[r14+r9], cl			;and put it into rowBuffer
	inc r8
	inc r9
	mov qword[curr], r8				;inc curr
	mov qword[pixelCount], r9		;and pixelcount
	cmp qword[pixelCount], r13		;check if rowBuffer is full
	jl proccessing
	;change the program so that BUFF_SIZE = width * 3 and make it so each call is a rowBuffer, 
	;see what happens when you dont have to do the curr stuff


	readTrue:
	pop r15
	pop r14
	pop r13
	pop r12
	mov rsp, rbp
	pop rbp
	mov rax, TRUE
	ret

	readErr:						;err message
	mov rdi, errRead
	call printString

	readFalse:						;err or eof
	pop r15
	pop r14
	pop r13
	pop r12
	mov rsp, rbp
	pop rbp
	mov rax, FALSE
	ret

; ***************************************************************
;  Write image row to output file.
;	Writes exactly (width*3) bytes to file.
;	No requirement to buffer here.

; -----
;  HLL Call:
;	status = writeRow(writeFileDesc, pciWidth, rowBuffer);

;  Arguments are:
;	write file descriptor (value)
;	image width (value)
;	row buffer (address)

;  Returns:
;	TRUE or FALSE

; -----
;  This routine returns TRUE when row has been written
;	and returns FALSE only if there is an
;	error on write (which would not normally occur).


;	YOUR CODE GOES HERE
global writeRow
writeRow:

mov r10, rdx
mov rax, rsi
mov rcx, 3
mul rcx
mov rdx, rax
mov rsi, r10
mov rax, SYS_write
syscall

cmp rax, 0
jl writeErr
je writeFalse

mov rax, TRUE
ret

writeErr:
mov rdi, errWrite
call printString
jmp writeFalse

writeFalse:
mov rax, FALSE
ret

; ***************************************************************
;  Convert pixels to grayscale.

; -----
;  HLL Call:
;	status = imageCvtToBW(picWidth, rowBuffer);

;  Arguments are:
;	image width (value)
;	row buffer (address)
;  Returns:
;	updated row buffer (via reference)


;	YOUR CODE GOES HERE
global imageCvtToBW
imageCvtToBW:

	lea r10, byte[rsi]					;load buffer into r10
	mov r11, 0
	mov rcx, 3
	
	
	BWLoop:
	cmp r11, rdi						;check if end of width
	jg BWExit
	movzx ax, byte[r10]					;add red
	movzx dx, byte[r10+1]				;green
	add ax, dx
	movzx dx, byte[r10+2]				;blue
	add ax, dx							
	div cl								;then div by 3
	mov byte[r10], al					;move quotient back
	mov byte[r10+1], al
	mov byte[r10+2], al
	add r10, 3							;mov r10 over to the next pixel
	inc r11
	jmp BWLoop

	BWExit:
ret

; ***************************************************************
;  Update pixels to increase brightness

; -----
;  HLL Call:
;	status = imageBrighten(picWidth, rowBuffer);

;  Arguments are:
;	image width (value)
;	row buffer (address)
;  Returns:
;	updated row buffer (via reference)


;	YOUR CODE GOES HERE
global imageBrighten
imageBrighten:

	lea r10, byte[rsi]					;load buffer into r10
	mov r11, 0

	mov rax, rdi						;mul width by 3
	mov rcx, 3
	mul rcx
	mov rdi, rax
	mov rax, 0
	mov r8, 0

	brightLoop:
	cmp r11, rdi						;check if last pixel
	jge brightExit
	movzx ax, byte[r10]					;mov color to rax
	movzx r8w, byte[r10]					;save currentcolor for later
	mov cx, 2
	div cx								;div by 2
	mov rdx, 0
	add ax, r8w							;add back old color
	cmp ax, 255
	jl nooverflow
	mov al, 255
	nooverflow:
	mov byte[r10], al					;save it
	inc r10
	inc r11
	jmp brightLoop

	brightExit:
ret

; ***************************************************************
;  Update pixels to darken (decrease brightness)

; -----
;  HLL Call:
;	status = imageDarken(picWidth, rowBuffer);

;  Arguments are:
;	image width (value)
;	row buffer (address)
;  Returns:
;	updated row buffer (via reference)


;	YOUR CODE GOES HERE
global imageDarken
imageDarken:

	lea r10, byte[rsi]					;load buffer into r10
	mov r11, 0

	mov rax, rdi						;mul width by 3
	mov rcx, 3
	mul rcx
	mov rdi, rax

	mov rcx, 2
	darkLoop:
	cmp r11, rdi						;check if last pixel
	jg darkExit
	mov rax, 0
	mov al, byte[r10]	
	div cl								;div currentcolor by 2
	mov byte[r10], al
	inc r10
	inc r11
	jmp darkLoop

	darkExit:

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
	push	rbx

; -----
;  Count characters in string.

	mov	rbx, rdi			; str addr
	mov	rdx, 0
strCountLoop:
	cmp	byte [rbx], NULL
	je	strCountDone
	inc	rbx
	inc	rdx
	jmp	strCountLoop
strCountDone:

	cmp	rdx, 0
	je	prtDone

; -----
;  Call OS to output string.

	mov	rax, SYS_write			; system code for write()
	mov	rsi, rdi			; address of characters to write
	mov	rdi, STDOUT			; file descriptor for standard in
						; EDX=count to write, set above
	syscall					; system call

; -----
;  String printed, return to calling routine.

prtDone:
	pop	rbx
	ret

; ******************************************************************

