###########################################################################
#  Name: Alec Zheng
#  NSHE ID: 2001982564
#  Section: 1004
#  Assignment: 5
#  Description:  recursion and pascal triangles



#####################################################################
#  data segment

.data

# -----
#  Define basic parameters

TRUE = 1
FALSE = 0
NUMSIZE = 6		# parameter for maximum number size (digits)

# -----
#  Local variables for main.

hdr:	.ascii	"\nMIPS Assignment #5\n"
	.asciiz	"Pascal's Triangle Program\n\n"

rows:	.word	0

# -----
#  Local variables for displayPascalTriangle routine.

rmsg1:	.asciiz	"\nrow "
rmsg2:	.asciiz	":    "

# -----
#  Local variables for readRows routine.

entN:	.asciiz	"\nEnter number of rows in triangle (1-25): "
badRow:	.asciiz	"\nError, valid row amount, please re-enter."

# -----
#  Local variables for prtPnum routine.

spc:	.asciiz	"   "

# -----
#  Local variables for prtBlanks routine.

spc1:	.asciiz	" "
nline:	.asciiz	"\n"

# -----
#  Local variables for checkAgain routine.

uAns:	.byte	0, 0, 0

ask:	.asciiz	"\n\nAnother Game (y/Y/n/N)? "
dMsg:	.asciiz	"\nGame Over. \nThank you for playing.\n\n"
badAns:	.asciiz	"Error, invalid input, please try again."


#####################################################################
#  text/code segment

.text

.globl main
.ent main
main:

# -----
#  Display header.

	la	$a0, hdr
	li	$v0, 4
	syscall					# print header

# -----
#  Read max rows (1-25).

doPascalAgain:
	jal	readRows
	sw	$v0, rows

# -----
#  Display the pascal triangle.

	lw	$a0, rows
	jal	displayPascalTriangle

# -----
#  Check for another triangle?

	jal	checkAgain
	beq	$v0, TRUE, doPascalAgain

# -----
#  Done, terminate program.

	la	$a0, nline
	li	$v0, 4
	syscall
	la	$a0, nline
	li	$v0, 4
	syscall

	li	$v0, 10
	syscall					# au revoir...

.end main


#####################################################################
#  Display the pascal triangle.
#	Routine must compute the Pascal number (via call),
#	display approriate row headers (see example), and
#	then print the pascal numbers.  Since the pascal()
#	function computes a single Pascal number, the pascal()
#	function will need to be called in a nested loop
#	(rows and columns).

# -----
#    Arguments:
#	$a0 - rows (value)

#    Returns:
#	nothing


#	YOUR CODE GOES HERE
.globl displayPascalTriangle
.ent displayPascalTriangle
displayPascalTriangle:

sub $sp, $sp, 16
sw $s0, ($sp)
sw $s1, 4($sp)
sw $s2, 8($sp)
sw $ra, 12($sp)

move $s0, $a0
li $s1, 1		# k
li $s2, 1		# n

displayLoop:
sub $t0, $s0, $s2				# leading spaces

displayLoop1:
la $a0, spc 					# space
li $v0, 4
syscall

sub $t0, $t0, 1
bgtz $t0, displayLoop1

jal printPnum



lw $s0, ($sp)
lw $s1, 4($sp)
lw $s2, 8($sp)
lw $ra, 12($sp)
jr $ra


.end displayPascalTriangle
#####################################################################
#  MIPS assembly language function, readRows()
#	Reads a number from the user and ensure that the number
#	is between 1 and 25 (inclusive).
#	Includes prompting and error checking.
#	Re-prompts for incorrect input.

# -----
#    Arguments:
#	none

#    Returns:
#	$v0 - n (between 1-25)


#	YOUR CODE GOES HERE
.globl readRows
.ent readRows
readRows:

la $a0, entN					# header
li $v0, 4
syscall

li $v0, 5
syscall

move $t0, $zero
blt $v0, $t0, rowError
li $t0, 25
bgt $v0, $t0, rowError

jr $ra

rowError:
la $a0, badRow
li $v0, 4
syscall

j readRows

.end readRows
#####################################################################
#  Pascal's triangle.
#  Compute the kth element of the nth row.
#  Note, k and n are 0-based

#	Pascal(n,k)
#	   if k = 0 or k = n then
#	      return 1
#	   else
#	      return Pascal(n-1,k-1) + Pascal(n-1, k)

# -----
#    Arguments:
#	$a0 - n
#	$a1 - k

#    Returns:
#	$v0 - pascal(n,k)


#	YOUR CODE GOES HERE
# base cases
.globl Pascal
.ent Pascal
Pascal:

beq $a0, $a1, eqOne
beqz $a1, eqOne

subu $sp, $sp, 16
sw $ra, ($sp)
sw $s0, 4($sp)
sw $s1, 8($sp)
sw $s2, 12($sp)

move $s0, $a0
move $s1, $a1

sub $a0, $a0, 1					# pascal (n−1 , k−1)
sub $a1, $a1, 1
jal Pascal
move $s2, $v0
move $a0, $s0					# pascal (n−1 , k)
move $a1, $s1
sub $a0, $a0, 1
jal Pascal

# return pascal (n−1 , k−1)+pascal (n−1 , k)
add $v0, $v0, $s2
lw $ra, ($sp)
lw $s0, 4($sp)
lw $s1, 8($sp)
lw $s2, 12($sp)
addu $sp, $sp, 16
jr $ra

eqOne:
li $v0, 1
jr $ra

.end Pascal
#####################################################################
#  Print pascal number as per asst #5 specificiations.
#	In order to provide the correct triangle output the
#	number will need to be printed in a formatted manner.

#	This funtion uses a function to
#	    1) print the leading blanks (spc * row
#	    2) print the pascal number.

# -----
#  Arguments:
#	$a0 - n (value)
#	$a1 - pascal number (value)

#  Returns
#	nothing


#	YOUR CODE GOES HERE
.globl printPnum
.ent printPnum
printPnum:



.end printPnum
#####################################################################
#  Utility function to prompt user if they
#	want to display another pascal's
#	triangle.  Expected response is Y/y/N/n.


#	YOUR CODE GOES HERE
.globl checkAgain
.ent checkAgain
checkAgain:

la $a0, ask						# header
li $v0, 4
syscall

la $a0, uAns
li $a1, 3
li $v0, 8
syscall

la $a0, nline
li $v0, 4
syscall

# get first char of string
la $t1, uAns
lb $t2, ($t1)

li $t0, 0x59						# check for Y/y
beq $t2, $t0, yes
li $t0, 0x79
beq $t2, $t0, yes
li $t0, 0x4E
beq $t2, $t0, no
li $t0, 0x6E
beq $t2, $t0, no

# bad answer
la $a0, badAns	
li $v0, 4
syscall
j readRows

yes:
li $v0, TRUE
jr $ra

no:
la $a0, dMsg	
li $v0, 4
syscall

li $v0, FALSE
jr $ra


.end checkAgain


#####################################################################

