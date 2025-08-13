###########################################################################
#  Name: Alec Zheng
#  NSHE ID: 2001982564
#  Section: 1004
#  Assignment: MIPS #4
#  Description: indexing for multiple dimension arrays

#  MIPS assembly language program to calculate
#  the least cost path in a triangle from top
#  to bottom.

###########################################################
#  data segment

.data

TRUE = 1
FALSE = 0

hdr:	.ascii	"\nMIPS Assignment #4\n"
	.asciiz	"Program to Find Cost of Least Cost Path.\n\n"

# -----
#  Triangles.

bName1:	.asciiz	"Triangle #1 (example)\n"
bOrd1:	.word	4
brd1:	.word	3, 0, 0, 0
	.word	7, 4, 0, 0
	.word	4, 2, 6, 0
	.word	8, 2, 9, 5

bName2:	.asciiz	"Triangle #2 (small)\n"
bOrd2:	.word	5
brd2:	.word	5, 0, 0, 0, 0
	.word	6, 8, 0, 0, 0
	.word	3, 4, 7, 0, 0
	.word	5, 8, 2, 6, 0
	.word	8, 5, 1, 3, 9

bName3:	.asciiz	"Triangle #3 (small)\n"
bOrd3:	.word	6
brd3:	.word	3, 0, 0, 0, 0, 0
	.word	7, 4, 0, 0, 0, 0
	.word	4, 2, 6, 0, 0, 0
	.word	8, 2, 9, 5, 0, 0
	.word	9, 3, 6, 2, 7, 0
	.word	1, 2, 8, 4, 7, 3

bName4:	.asciiz	"Triangle #4 (medium)\n"
bOrd4:	.word	15
brd4:	.word	75,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	95, 64,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	17, 47, 82,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	18, 35, 87, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	20,  4, 82, 47, 65,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	19,  1, 23, 75,  3, 34,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	88,  2, 77, 73,  7, 63, 67,  0,  0,  0,  0,  0,  0,  0,  0
	.word	99, 65,  4, 28,  6, 16, 70, 92,  0,  0,  0,  0,  0,  0,  0
	.word	41, 41, 26, 56, 83, 40, 80, 70, 33,  0,  0,  0,  0,  0,  0
	.word	41, 48, 72, 33, 47, 32, 37, 16, 94, 29,  0,  0,  0,  0,  0
	.word	53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14,  0,  0,  0,  0
	.word	70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57,  0,  0,  0
	.word	91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48,  0,  0
	.word	63, 66, 04, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31,  0
	.word	 4, 62, 98, 27, 23,  9, 70, 98, 73, 93, 38, 53, 60,  4, 23


bName5:	.asciiz	"Triangle #5 (large)\n"
bOrd5:	.word	17
brd5:	.word	75,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	95, 64,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	17, 47, 82,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	18, 35, 87, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	20, 04, 82, 47, 65,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	19, 01, 23, 75, 03, 34,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	88, 02, 77, 73, 07, 63, 67,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	99, 65, 04, 28, 06, 16, 70, 92,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	41, 41, 26, 56, 83, 40, 80, 70, 33,  0,  0,  0,  0,  0,  0,  0,  0
	.word	41, 48, 72, 33, 47, 32, 37, 16, 94, 29,  0,  0,  0,  0,  0,  0,  0
	.word	53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14,  0,  0,  0,  0,  0,  0
	.word	70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57,  0,  0,  0,  0,  0
	.word	91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48,  0,  0,  0,  0
	.word	63, 66, 04, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31,  0,  0,  0
	.word	04, 62, 98, 27, 23, 09, 70, 98, 73, 93, 38, 53, 60, 04, 23,  0,  0
	.word	77, 22, 10, 81, 12, 94, 07, 22, 35, 80, 87, 70, 19, 03, 84, 34,  0
	.word	28, 33, 10, 38, 11, 99, 31, 43, 86, 19, 71, 72, 64, 41, 70, 44, 53


bName6:	.asciiz	"Triangle #6 (largest)\n"
bOrd6:	.word	20
brd6:	.word	59,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	73, 41,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	52, 40, 09,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	26, 53, 06, 34,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	10, 51, 87, 86, 81,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	61, 95, 66, 57, 25, 68,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	90, 81, 80, 38, 92, 67, 73,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	30, 28, 51, 76, 81, 18, 75, 44,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	84, 14, 95, 87, 62, 81, 17, 78, 58,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	21, 46, 71, 58, 02, 79, 62, 39, 31, 09,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	56, 34, 35, 53, 78, 31, 81, 18, 90, 93, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0
	.word	78, 53, 04, 21, 84, 93, 32, 13, 97, 11, 37, 51,  0,  0,  0,  0,  0,  0,  0,  0
	.word	45, 03, 81, 79, 05, 18, 78, 86, 13, 30, 63, 99, 95,  0,  0,  0,  0,  0,  0,  0
	.word	39, 87, 96, 28, 03, 38, 42, 17, 82, 87, 58, 07, 22, 57,  0,  0,  0,  0,  0,  0
	.word	06, 17, 51, 17, 07, 93, 09, 07, 75, 97, 95, 78, 87, 08, 53,  0,  0,  0,  0,  0
	.word	67, 66, 59, 60, 88, 99, 94, 65, 55, 77, 55, 34, 27, 53, 78, 28,  0,  0,  0,  0
	.word	76, 40, 41, 04, 87, 16, 09, 42, 75, 69, 23, 97, 30, 60, 10, 79, 87,  0,  0,  0
	.word	12, 10, 44, 26, 21, 36, 32, 84, 98, 60, 13, 12, 36, 16, 63, 31, 91, 35,  0,  0
	.word	70, 39, 06, 05, 55, 27, 38, 48, 28, 22, 34, 35, 62, 62, 15, 14, 94, 89, 86,  0
	.word	66, 56, 68, 84, 96, 21, 34, 34, 34, 81, 62, 40, 65, 54, 62, 05, 98, 03, 02, 60


# -----
#  Variables for displayTriangle() function.

brdHdr:		.asciiz	"***********************************************\n"
newLine:	.asciiz	"\n"
blnk:		.asciiz	" "
blnk2:		.asciiz	"  "
zer:		.asciiz	"0"

# -----
#  Variables for findLeastCost() function.

LCmsg:		.asciiz	"Least Cost Traversal: "
PSmsg:		.asciiz	"Possible Solutions: "


###########################################################
#  text/code segment

.text

.globl main
.ent main
main:

# -----
#  Display main program header.

	la	$a0, hdr
	li	$v0, 4
	syscall					# print header

# -----
#  Display triangle and find least cost for each triangle.

	lw	$a0, bOrd1
	la	$a1, brd1
	la	$a2, bName1
	jal	displayTriangle

	lw	$a0, bOrd1
	la	$a1, brd1
	jal	findLeastCost


	lw	$a0, bOrd2
	la	$a1, brd2
	la	$a2, bName2
	jal	displayTriangle

	lw	$a0, bOrd2
	la	$a1, brd2
	jal	findLeastCost


	lw	$a0, bOrd3
	la	$a1, brd3
	la	$a2, bName3
	jal	displayTriangle

	lw	$a0, bOrd3
	la	$a1, brd3
	jal	findLeastCost


	lw	$a0, bOrd4
	la	$a1, brd4
	la	$a2, bName4
	jal	displayTriangle

	lw	$a0, bOrd4
	la	$a1, brd4
	jal	findLeastCost


	lw	$a0, bOrd5
	la	$a1, brd5
	la	$a2, bName5
	jal	displayTriangle

	lw	$a0, bOrd5
	la	$a1, brd5
	jal	findLeastCost


	lw	$a0, bOrd6
	la	$a1, brd6
	la	$a2, bName6
	jal	displayTriangle

	lw	$a0, bOrd6
	la	$a1, brd6
	jal	findLeastCost

# -----
#  Done, terminate program.

	li	$v0, 10
	syscall
.end main

######################################################################
#  Function to print a formatted triangle (as per assignment).

# -----
#  Formula for multiple dimension array indexing:
#	addr(r,c) = baseAddr + (r * colSize + c) * dataSize

# -----
#  Arguments:
#	$a0 - order (size) of the triangle
#	$a1 - triangle address
#	$a2 - title address
.globl	displayTriangle
.ent	displayTriangle
displayTriangle:

subu $sp, $sp, 28			# saving registers on stack
sw $s0, ($sp)
sw $s1, 4($sp)
sw $s2, 8($sp)
sw $s3, 12($sp)
sw $ra, 16($sp)
sw $fp, 20($sp)
sw $s4, 24($sp)
addu $fp, $sp, 28 			# set frame pointer

move $s0, $a0				# save arguments
move $s1, $a1
move $s2, $a2

la $a0, brdHdr				# print boarder
li $v0, 4
syscall

move $a0, $s2				# print title
li $v0, 4
syscall

la $a0, newLine				# print new line
li $v0, 4
syscall
la $a0, newLine				# print new line
li $v0, 4
syscall

# start of display code

move $t0, $s0
move $t1, $zero
move $t2, $zero
li $t3, 10
li $t5, 1					# counts how many numbers to display per row
move $t6, $zero				# col index
move $t7, $zero				# row index


displayLoop:				# start of loop
beqz $t0, displayExit

la $a0, blnk2				# print space
li $v0, 4
syscall

printSpaces:
la $a0, blnk2				# print space
li $v0, 4
syscall
addu $t2, $t2, 1
bne $t2, $t0, printSpaces

# print numbers here
printNumbers:
beq $t6, $t5, numbersExit	# exit condition
move $t8, $zero
move $t4, $zero				# address math register is $t4
mul $t4, $s0, $t7			# (rowIdx * colSize
add $t4, $t4, $t6			# + colIdx)
mul $t4, $t4, 4				# * dataSize
add $t8, $s1, $t4			# + base address

lw $t9, ($t8)

bge $t9, $t3, printZeroSkip

la $a0, zer					# print zero if num < 10
li $v0, 4
syscall

printZeroSkip:

move $a0, $t9				# print number
li $v0, 1
syscall

la $a0, blnk2				# print space
li $v0, 4
syscall

add $t6, $t6, 1
j printNumbers

numbersExit:
subu $t0, $t0, 1 			# count down to exit
beqz $t0, displayLoop

la $a0, newLine				# print new line
li $v0, 4
syscall

move $t2, $zero

addu $t7, $t7, 1			# move to next row
move $t6, $zero				# restart col index
add $t5, 1					# add one more element to next row
j displayLoop

displayExit:

# #####################################################################

la $a0, newLine				# print new line
li $v0, 4
syscall

la $a0, newLine				# print new line
li $v0, 4
syscall

lw $s0, ($sp)				# restore saved registers
lw $s1, 4($sp)
lw $s2, 8($sp)
lw $s3, 12($sp)
lw $ra, 16($sp)				
lw $fp, 20($sp)
lw $s4, 24($sp)
addu $sp, $sp, 28
jr $ra

.end displayTriangle
######################################################################
#  Function to find the value of least cost path.

# -----
#  Formula for multiple dimension array indexing:
#	addr(r,c) = baseAddr + (r * colSize + c) * dataSize

# -----
#    Arguments:
#	$a0 - triangle order
#	$a1 - triangle address

#    Returns:
#	nothing

.globl	findLeastCost
.ent	findLeastCost
findLeastCost:

subu $sp, $sp, 12			# saving registers on stack
sw $s0, ($sp)
sw $s1, 4($sp)
sw $s2, 8($sp)

move $s0, $a0
move $s1, $a1

la $a0, LCmsg
li $v0, 4
syscall

move $t7, $s0

costStart:
sub $t7, $t7, 1
move $t3, $t7				# row index - 1 in $t3
move $t4, $zero				# col index reset to 0

costLoop:

beqz $t3, costExit			# exit condition0
mul $t2, $s0, $t3			# (rowIdx * colSize
add $t2, $t2, $t4			# + colIdx)
mul $t2, $t2, 4				# * dataSize
add $t5, $s1, $t2			# + base address

lw $t0, ($t5)				# move first value into $t0

add $t4, $t4, 1

mul $t2, $s0, $t3			# (rowIdx * colSize
add $t2, $t2, $t4			# + colIdx)
mul $t2, $t2, 4				# * dataSize
add $t5, $s1, $t2			# + base address

lw $t1, ($t5)				# move second value into $t1

sub $t4, $t4, 1
sub $t3, $t3, 1
mul $t2, $s0, $t3			# (rowIdx * colSize
add $t2, $t2, $t4			# + colIdx)
mul $t2, $t2, 4				# * dataSize
add $t5, $s1, $t2			# + base address
add $t4, $t4, 1
add $t3, $t3, 1

lw $t6, ($t5)				# move top value into $t6

blt $t0, $t1, compareBranch # compare $t0 and $t1

add $t6, $t6, $t1			# if $t1 is smaller
j compareAfter

compareBranch:
add $t6, $t6, $t0			# if $t0 is smaller

compareAfter:
sw $t6, ($t5)

beq $t3, $t4, costStart
j costLoop

costExit:

move $a0, $t6				# print least cost
li $v0, 1
syscall

la $a0, newLine				# print new line
li $v0, 4
syscall

la $a0, PSmsg				# print possible solutions message
li $v0, 4
syscall

li $t0, 2
subu $s0, $s0, 2
psLoop:
subu $s0, $s0, 1
mul $t0, $t0, 2
bnez $s0, psLoop


move $a0, $t0				# print possible solutions
li $v0, 1
syscall

la $a0, newLine				# print new line
li $v0, 4
syscall
la $a0, newLine				# print new line
li $v0, 4
syscall

#stuff
lw $s0, ($sp)				# restore saved registers
lw $s1, 4($sp)
lw $s2, 8($sp)
addu $sp, $sp, 12
jr $ra

.end findLeastCost
######################################################################

