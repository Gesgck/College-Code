; *****************************************************************
;  Name: Alec Zheng
;  NSHE_ID: 2001982564
;  Section: 1003
;  Assignment: 10
;  Description: Draw spirographs based off user input

; -----
;  Function: getRadii
;	Gets, checks, converts, and returns command line arguments.

;  Function: drawSpiro()
;	Plots spirograph formulas

; ---------------------------------------------------------

;	MACROS (if any) GO HERE

;macro to convert a sentary number to an integer
%macro	senary2int	2

mov rax, 0
mov rcx, 0
mov r10, 6
mov r11, %1				;loads string into rbx
%%convert6to10:
mov r8, 0
mov r8b, [r11+rcx]		;moves first character into r8b
cmp r8b, NULL			;check if null
je %%exit
inc rcx
cmp r8b, 0x20			;compares to space
je %%convert6to10		;jump back to start if character is a space
cmp r8b, 0x30			;checks if above 0
jl %%err
cmp r8b, 0x35			;checks if below 6
jg %%err
sub r8b, 0x30			;subtract ascii 0
add rax, r8				;adds value into rax
mov r9b , byte[r11+rcx]
cmp r9b, 0				;check if next char is null
je %%exit				;exits loop if it is
mul r10w				;multiplies by 6 if it isn't
jmp %%convert6to10		;and then jumps back to the start
%%err:
mov %2, -1
%%exit:
mov %2, rax
%endmacro
; ---------------------------------------------------------

section  .data

; -----
;  Define standard constants.

TRUE		equ	1
FALSE		equ	0

SUCCESS		equ	0			; successful operation
NOSUCCESS	equ	1

STDIN		equ	0			; standard input
STDOUT		equ	1			; standard output
STDERR		equ	2			; standard error

SYS_read	equ	0			; code for read
SYS_write	equ	1			; code for write
SYS_open	equ	2			; code for file open
SYS_close	equ	3			; code for file close
SYS_fork	equ	57			; code for fork
SYS_exit	equ	60			; code for terminate
SYS_creat	equ	85			; code for file open/create
SYS_time	equ	201			; code for get time

LF		equ	10
SPACE		equ	" "
NULL		equ	0
ESC		equ	27

; -----
;  OpenGL constants

GL_COLOR_BUFFER_BIT	equ	16384
GL_POINTS		equ	0
GL_POLYGON		equ	9
GL_PROJECTION		equ	5889

GLUT_RGB		equ	0
GLUT_SINGLE		equ	0

; -----
;  Define program specific constants.

R1_MIN		equ	0
R1_MAX		equ	250			; 250(10) = 1054(6)

R2_MIN		equ	1			; 1(10) = 1(13)
R2_MAX		equ	250			; 250(10) = 1054(6)

OP_MIN		equ	1			; 1(10) = 1(13)
OP_MAX		equ	250			; 250(10) = 1054(6)

SP_MIN		equ	1			; 1(10) = 1(13)
SP_MAX		equ	100			; 100(10) = 244(6)

X_OFFSET	equ	320
Y_OFFSET	equ	240

; -----
;  Variables for getRadii procedure.

errUsage	db	"Usage:  ./spiro -r1 <senary number> "
		db	"-r2 <senary number> -op <senary number> "
		db	"-sp <senary number> -cl <b/g/r/y/p/w>"
		db	LF, NULL
errBadCL	db	"Error, invalid or incomplete command line arguments."
		db	LF, NULL

errR1sp		db	"Error, radius 1 specifier incorrect."
		db	LF, NULL
errR1value	db	"Error, radius 1 value must be between 0 and 1054(6)."
		db	LF, NULL

errR2sp		db	"Error, radius 2 specifier incorrect."
		db	LF, NULL
errR2value	db	"Error, radius 2 value must be between 1 and 1054(6)."
		db	LF, NULL

errOPsp		db	"Error, offset position specifier incorrect."
		db	LF, NULL
errOPvalue	db	"Error, offset position value must be between 1 and 1054(6)."
		db	LF, NULL

errSPsp		db	"Error, speed specifier incorrect."
		db	LF, NULL
errSPvalue	db	"Error, speed value must be between 1 and 244(6)."
		db	LF, NULL

errCLsp		db	"Error, color specifier incorrect."
		db	LF, NULL
errCLvalue	db	"Error, color value must be b, g, r, p, or w. "
		db	LF, NULL

; -----
;  Variables for spirograph routine.

fltOne		dd	1.0
fltZero		dd	0.0
fltTmp1		dd	0.0
fltTmp2		dd	0.0

t		dd	0.0			; loop variable
s		dd	1.0			; phase variable
tStep		dd	0.005			; t step
sStep		dd	0.0			; s step
x		dd	0			; current x
y		dd	0			; current y

r1		dd	0.0			; radius 1 (float)
r2		dd	0.0			; radius 2 (float)
ofp		dd	0.0			; offset position (float)
radii		dd	0.0			; tmp location for (radius1+radius2)

scale		dd	5000.0			; speed scale
limit		dd	360.0			; for loop limit
iterations	dd	0			; set to 360.0/tStep

red		db	0			; 0-255
green		db	0			; 0-255
blue		db	0			; 0-255

; ------------------------------------------------------------

section  .text

; -----
;  External references for openGL routines.

extern	glutInit, glutInitDisplayMode, glutInitWindowSize, glutInitWindowPosition
extern	glutCreateWindow, glutMainLoop
extern	glutDisplayFunc, glutIdleFunc, glutReshapeFunc, glutKeyboardFunc
extern	glutSwapBuffers, gluPerspective, glutPostRedisplay
extern	glClearColor, glClearDepth, glDepthFunc, glEnable, glShadeModel
extern	glClear, glLoadIdentity, glMatrixMode, glViewport
extern	glTranslatef, glRotatef, glBegin, glEnd, glVertex3f, glColor3f
extern	glVertex2f, glVertex2i, glColor3ub, glOrtho, glFlush, glVertex2d

extern	cosf, sinf

; ******************************************************************
;  Function getRadii()
;	Gets radius 1, radius 2, offset positionm and rottaion
;	speedvalues and color code letter from the command line.

;	Performs error checking, converts ASCII/senary string
;	to integer.  Required ommand line format (fixed order):
;	  "-r1 <senary numberl> -r2 <senary number> -op <senary number> 
;			-sp <senary number> -cl <color>"

; HLL
;	stat = getRadii(argc, argv, &radius1, &radius2, &offPos,
;						&speed, &color);

; -----
;  Arguments:
;	- ARGC
;	- ARGV
;	- radius 1, double-word, address
;	- radius 2, double-word, address
;	- offset Position, double-word, address
;	- speed, double-word, address
;	- circle color, byte, address




;	YOUR CODE GOES HERE

global getRadii
getRadii:

push rbp
mov rbp, rsp

push r15
push r14
push r13
push r12							;save preserved registers

;Checks for arguments present
cmp rdi, 1							;Check for 0 arguments
jne ARGC0Check
mov rdi, errUsage
call printString
jmp errEXIT
ARGC0Check:

cmp rdi, 11							;Check for 10 arguments
je ARGCCheck
mov rdi, errBadCL
call printString
jmp errEXIT
ARGCCheck:

;checking if specifiers are present and correct
mov r12, rdx
mov r13, rcx
mov r14, r8
mov r15, r9
mov rdx, qword[rsi+1*8]				;ARGV[1] check
mov r8b, [rdx]
cmp r8b, 0x2D						;check "-"
jne ARGV1Check
mov r8b, [rdx+1]
cmp r8b, 0x72						;check "r"
jne ARGV1Check
mov r8b, [rdx+2]
cmp r8b, 0x31						;check "1"
jne ARGV1Check
mov r8b, [rdx+3]
cmp r8b, NULL
jne	ARGV1Check
jmp ARGV1
ARGV1Check:
mov rdi, errR1sp
call printString
jmp errEXIT
ARGV1:

mov rdx, qword[rsi+3*8]				;ARGV[3] check
mov r8b, [rdx]
cmp r8b, 0x2D						;"-"
jne ARGV3Check
mov r8b, [rdx+1]
cmp r8b, 0x72						;"r"
jne ARGV3Check
mov r8b, [rdx+2]
cmp r8b, 0x32						;check "2"
jne ARGV1Check
mov r8b, [rdx+3]
cmp r8b, NULL
jne	ARGV3Check
jmp ARGV3
ARGV3Check:
mov rdi, errR2sp
call printString
jmp errEXIT
ARGV3:

mov rdx, qword[rsi+5*8]				;ARGV[5] check
mov r8b, [rdx]
cmp r8b, 0x2D						;check "-"
jne ARGV5Check
mov r8b, [rdx+1]
cmp r8b, 0x6F						;check "o"
jne ARGV5Check
mov r8b, [rdx+2]
cmp r8b, 0x70						;check "p"
jne ARGV5Check
mov r8b, [rdx+3]
cmp r8b, NULL
jne	ARGV5Check
jmp ARGV5
ARGV5Check:
mov rdi, errOPsp
call printString
jmp errEXIT
ARGV5:

mov rdx, qword[rsi+7*8]				;ARGV[7] check
mov r8b, [rdx]
cmp r8b, 0x2D						;check "-"
jne ARGV7Check
mov r8b, [rdx+1]
cmp r8b, 0x73						;check "s"
jne ARGV7Check
mov r8b, [rdx+2]
cmp r8b, 0x70						;check "p"
jne ARGV7Check
mov r8b, [rdx+3]
cmp r8b, NULL
jne	ARGV7Check
jmp ARGV7
ARGV7Check:
mov rdi, errSPsp
call printString
jmp errEXIT
ARGV7:

mov rdx, qword[rsi+9*8]				;ARGV[9] check
mov r8b, [rdx]
cmp r8b, 0x2D						;check "-"
jne ARGV9Check
mov r8b, [rdx+1]
cmp r8b, 0x63						;check "c"
jne ARGV9Check
mov r8b, [rdx+2]
cmp r8b, 0x6C						;check "l"
jne ARGV9Check
mov r8b, [rdx+3]
cmp r8b, NULL
jne	ARGV9Check
jmp ARGV9
ARGV9Check:
mov rdi, errCLsp
call printString
jmp errEXIT
ARGV9:



;---------------
;checking if values are present and legal

mov r11, qword[rsi+2*8]				;ARGV[2] conversion/check
senary2int r11, rax
cmp rax, R1_MAX
jg ARGV2err
cmp rax, R1_MIN
jl ARGV2err
jmp ARGV2
ARGV2err
mov rdi, errR1value
call printString
jmp errEXIT
ARGV2:
mov dword[r12], eax;

mov r11, qword[rsi+4*8]				;ARGV[4] conversion/check
senary2int r11, rax
cmp rax, R2_MAX
jg ARGV4err
cmp rax, R2_MIN
jl ARGV4err
jmp ARGV4
ARGV4err:
mov rdi, errR2value
call printString
jmp errEXIT
ARGV4:
mov dword[r13], eax

mov r11, qword[rsi+6*8]				;ARGV[6] conversion/check
senary2int r11, rax
cmp rax, OP_MAX
jg ARGV6err
cmp rax, OP_MIN
jl ARGV6err
jmp ARGV6
ARGV6err:
mov rdi, errOPvalue
call printString
jmp errEXIT
ARGV6:
mov dword[r14], eax

mov r11, qword[rsi+8*8]				;ARGV[8] conversion/check
senary2int r11, rax
cmp rax, SP_MAX
jg ARGV8err
cmp rax, SP_MIN
jl ARGV8err
jmp ARGV8
ARGV8err:
mov rdi, errSPvalue
call printString
jmp errEXIT
ARGV8:
mov dword[r15], eax

mov r11, 0
mov r10, 0
mov r11, qword[rsi+10*8]				;ARGV[10] check
mov r10b, byte[r11+1]					;check if only one character
cmp r10b, NULL
jne ARGV10err
mov r10b, byte[r11]
cmp r10b, 0x62						;check if b
je ARGV10
cmp r10b, 0x67						;check if g
je ARGV10
cmp r10b, 0x72						;check if r
je ARGV10
cmp r10b, 0x79						;check if y
je ARGV10
cmp r10b, 0x70						;check if p
je ARGV10
cmp r10b, 0x77						;check if w
je ARGV10
ARGV10err:							;not any of the above
mov rdi, errCLvalue
call printString
jmp errEXIT
ARGV10:
mov r11, qword[rbp+16]
mov byte[r11], r10b


; -----
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
; ******************************************************************
;  Spirograph Plotting Function.

; -----
;  Color Code Conversion:
;	'r' -> red=255, green=0, blue=0
;	'g' -> red=0, green=255, blue=0
;	'b' -> red=0, green=0, blue=255
;	'p' -> red=255, green=0, blue=255
;	'y' -> red=255 green=255, blue=0
;	'w' -> red=255, green=255, blue=255
;  Note, set color before plot loop.

; -----
;  The loop is from 0.0 to 360.0 by tStep, can calculate
;  the number if iterations via:  iterations = 360.0 / tStep
;  This eliminates needing a float compare (a hassle).

; -----
;  Basic flow:
;	Set openGL drawing initializations
;	Loop initializations
;		Set draw color (i.e., glColor3ub)
;		Convert integer values to float for calculations
;		set 'sStep' variable
;		set 'iterations' variable
;	Plot the following spirograph equations:
;	     for (t=0.0; t<360.0; t+=step) {
;	         radii = (r1+r2)
;	         x = (radii * cos(t)) + (offPos * cos(radii * ((t+s)/r2)))
;	         y = (radii * sin(t)) + (offPos * sin(radii * ((t+s)/r2)))
;	         t += tStep
;	         plot point (x, y)
;	     }
;	Close openGL plotting (i.e., glEnd and glFlush)
;	Update s for next call (s += sStep)
;	Ensure openGL knows to call again (i.e., glutPostRedisplay)

; -----
;  The animation is accomplished by plotting a static
;	image, exiting the routine, and replotting a new
;	slightly different image.  The 's' variable controls
;	the phase or animation.

; -----
;  Global variables accessed
;	There are defined and set in the main, accessed herein by
;	name as per the below declarations.

common	radius1		1:4		; radius 1, dword, integer value
common	radius2		1:4		; radius 2, dword, integer value
common	offPos		1:4		; offset position, dword, integer value
common	speed		1:4		; rortation speed, dword, integer value
common	color		1:1		; color code letter, byte, ASCII value

global drawSpiro
drawSpiro:
	push	r12

; -----
;  Prepare for drawing
	; glClear(GL_COLOR_BUFFER_BIT);
	mov	rdi, GL_COLOR_BUFFER_BIT
	call	glClear

	; glBegin();
	mov	rdi, GL_POINTS
	call	glBegin

; -----
;  Set draw color(r,g,b)
;	Convert color letter to color values
;	Note, only legal color letters should be
;		passed to this procedure
;	Note, color values should be store in local
;		variables red, green, and blue

;	YOUR CODE GOES HERE

mov r10, 0
mov r10b, byte[color]
cmp r10b, 0x72					;find the color and set it
je colorRed
cmp r10b, 0x67
je colorBlue
cmp r10b, 0x62
je colorGreen
cmp r10b, 0x70
je colorPurple
cmp r10b, 0x79
je colorYellow
cmp r10b, 0x77
je colorWhite

colorRed:								;red
mov rdi, 255
mov rsi, 0
mov rdx, 0
call glColor3ub
jmp colorSet
colorBlue:								;blue
mov rdi, 0
mov rsi, 0
mov rdx, 255
call glColor3ub
jmp colorSet
colorGreen:								;green
mov rdi, 0
mov rsi, 255
mov rdx, 0
call glColor3ub
jmp colorSet
colorPurple:							;urple
mov rdi, 255
mov rsi, 0
mov rdx, 255
call glColor3ub
jmp colorSet
colorYellow:							;yellow
mov rdi, 255
mov rsi, 255
mov rdx, 0
call glColor3ub
jmp colorSet
colorWhite:								;white
mov rdi, 255
mov rsi, 255
mov rdx, 255
call glColor3ub
colorSet:

; -----
;  Loop initializations and main plotting loop

;	YOUR CODE GOES HERE

mov r10, 0
mov r10d, dword[radius1]				;radius conversions
cvtsi2ss xmm2, r10d
movss dword[r1], xmm2
mov r10d, dword[radius2]
cvtsi2ss xmm2, r10d
movss dword[r2], xmm2
addss xmm2, dword[r1]					;r1 + r2
movss dword[radii], xmm2



movss xmm4, dword[limit]
divss xmm4, dword[tStep]
cvtss2si ecx, xmm4						;ecx = iterations
mov dword[iterations], ecx

mov r10d, dword[offPos]
cvtsi2ss xmm4, r10d						;offPos
movss dword[ofp], xmm4

spiroLoop:
mov r10d, dword[iterations]				;loop exit check
cmp r10d, 0
jl spiroExit

movss xmm0, dword[t]
call cosf
movss dword[x], xmm0					;cos(t)
movss xmm0, dword[t]
call sinf
movss dword[y], xmm0					;sin(t)

movss xmm0, dword[radii]
mulss xmm0, dword[x]					; x = (radii*cos(t))
movss dword[x], xmm0
movss xmm0, dword[radii]
mulss xmm0, dword[y]
movss dword[y], xmm0					; y = (radii*sin(t))

;cos(r1+r2*(t+s)/r2)
movss xmm0, dword[t]					;t
addss xmm0, dword[s]					;t+s
divss xmm0, dword[r2]					;t+s/r2
mulss xmm0, dword[radii]				;r1+r2 * above
call cosf
mulss xmm0, dword[ofp]					;offPos * cos(above)

movss xmm1, dword[x]
addss xmm0, xmm1
movss dword[x], xmm0					;x = what it should

;sin(r1+r2*(t+s)/r2)
movss xmm0, dword[t]					;t
addss xmm0, dword[s]					;t+s
divss xmm0, dword[r2]					;t+s/r2
mulss xmm0, dword[radii]				;r1+r2 * above
call sinf
mulss xmm0, dword[ofp]					;offPos * sin(above)

movss xmm1, dword[y]
addss xmm0, xmm1
movss dword[y], xmm0					;y = what it should

movss xmm1, dword[t]
addss xmm1, dword[tStep]
movss dword[t], xmm1					;t += tStep

movss xmm0, dword[x]
movss xmm1, dword[y]
call glVertex2f

mov r10d, dword[iterations]
dec r10d
mov dword[iterations], r10d

jmp spiroLoop

spiroExit:



; -----
;  Plotting done.

	call	glEnd
	call	glFlush

; -----
;  Update s for next call.

;	YOUR CODE GOES HERE
mov r10d, dword[speed]
cvtsi2ss xmm3, r10d
divss xmm3, dword[scale]				;sStep
movss dword[sStep], xmm3

movss xmm0, dword[s]
addss xmm0, dword[sStep]
movss dword[s], xmm0					;s += sStep

; -----
;  Ensure openGL knows to call again

	call	glutPostRedisplay

	pop	r12
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
	ret

; ******************************************************************

