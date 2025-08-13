###########################################################################
#  Name: Alec Zheng
#  NSHE ID: 2001982564
#  Section: 1004
#  Assignment: 4
#  Description:  Matrices and math on them


###########################################################
#  data segment

.data

hdr:	.asciiz	"\nMIPS Assignment #4\nProgram to perform matrix multiplication. \n\n"


# -----
#  Matrix Set #1 - MA(i,k), MB(k,j), MC(i,j)

idim1:		.word	1
jdim1:		.word	1
kdim1:		.word	4

matrix_a1:	.word	 10,  20,  30,  40	# MA(1,4)

matrix_b1:	.word	 50			# MB(4,1)
		.word	 60
		.word	 70
		.word	 80

matrix_c1:	.word	 0			# MC(1,1)

# -----
#  Matrix Set #2 - MA(i,k), MB(k,j), MC(i,j)

idim2:		.word	3
jdim2:		.word	3
kdim2:		.word	2

matrix_a2:	.word	 10,  20		# MA(3,2)
		.word	 30,  30
		.word	 50,  60

matrix_b2:	.word	 15,  25,  35		# MB(2,3)
		.word	 45,  55,  60

matrix_c2:	.word	 0,  0,  0		# MC(3,3)
		.word	 0,  0,  0
		.word	 0,  0,  0

# -----
#  Matrix Set #3 - MA(i,k), MB(k,j), MC(i,j)

idim3:		.word	2
jdim3:		.word	2
kdim3:		.word	3

matrix_a3:	.word	 2,  3,  4		# MA(2,3)
		.word	 3,  4,  5

matrix_b3:	.word	 2,  3			# MB(3,2)
		.word	 3,  4
		.word	 5,  6

matrix_c3:	.word	 0,  0			# MC(2,2)
		.word	 0,  0

# -----
#  Matrix Set #4 - MA(i,k), MB(k,j), MC(i,j)

idim4:		.word	2
jdim4:		.word	3
kdim4:		.word	4

matrix_a4:	.word	 1,  2,  3,  4		# MA(2,4)
		.word	 5,  6,  7,  8

matrix_b4:	.word	 1,  2,  3		# MB(4,3)
		.word	 4,  5,  6
		.word	 7,  8,  9
		.word	10, 11, 12

matrix_c4:	.word	 0,  0,  0		# MC(2,3)
		.word	 0,  0,  0

# -----
#  Matrix Set #5 - MA(i,k), MB(k,j), MC(i,j)

idim5:		.word	4
jdim5:		.word	4
kdim5:		.word	4

matrix_a5:	.word	110, 120, 130, 140	# MA(4,4)
		.word	150, 160, 170, 180
 		.word	190, 200, 210, 220
		.word	230, 240, 250, 260

matrix_b5:	.word	300, 310, 320, 330	# MB(4,4)
		.word	340, 350, 360, 370
		.word	380, 390, 400, 410
		.word	420, 430, 440, 450

matrix_c5:	.word	  0,   0,   0,   0	# MC(4,4)
		.word	  0,   0,   0,   0
		.word	  0,   0,   0,   0
		.word	  0,   0,   0,   0
		.word	  0,   0,   0,   0

# -----
#  Matrix Set #6 - MA(i,k), MB(k,j), MC(i,j)

idim6:		.word	5
jdim6:		.word	5
kdim6:		.word	5

matrix_a6:	.word	12, 23, 45, 32, 20	# MA(5,5)
		.word	24, 31, 51, 54, 41
		.word	32, 48, 67, 76, 60
		.word	48, 59, 75, 98, 88
		.word	50, 63, 82, 16, 91

matrix_b6:	.word	10, 23, 45, 52, 60	# MB(5,5)
		.word	53, 12, 13, 37, 21
		.word	27, 72, 31, 41, 82
		.word	14, 58, 28, 54, 77
		.word	49, 36, 53, 63, 46

matrix_c6:	.word	 0,  0,  0,  0,  0	# MC(5,5)
		.word	 0,  0,  0,  0,  0
		.word	 0,  0,  0,  0,  0
		.word	 0,  0,  0,  0,  0
		.word	 0,  0,  0,  0,  0

# -----
#  Matrix Set #7 - MA(i,k), MB(k,j), MC(i,j)

idim7:		.word	3
jdim7:		.word	5
kdim7:		.word	7

matrix_a7:	.word	 72,  9, 92,  6, 68,  4, 81	# MC(3,7)
		.word	  7, 91,  9, 86,  5, 62, 91
		.word	 89,  4, 65,  7, 77, 82,  6

matrix_b7:	.word	820, 221,   9,  34, 123		# MA(7,5)
		.word	  1, 183, 833,  52, 687
		.word	 62, 723,   4, 922,   5
		.word	  3, 824,  25, 212, 312
		.word	114, 425,  66,  43,  54
		.word	  5,  26, 637,  71, 291
		.word	916, 527, 738, 792,  32

matrix_c7:	.word	 0,  0,  0,  0,  0		# MB(3,5)
		.word	 0,  0,  0,  0,  0
		.word	 0,  0,  0,  0,  0

# -----
#  Matrix Set #8 - MA(i,k), MB(k,j), MC(i,j)

idim8:		.word	5
jdim8:		.word	6
kdim8:		.word	10

matrix_a8:	.word	 21, 11, 72,  1, 76, 12, 26,  7, 12, 67	 # MA(5,10)
		.word	 54, 65, 54,  4, 31, 54, 56,  3, 34, 23
		.word	  3, 65,  6, 16, 68, 34, 75,  2, 10, 80
		.word	 11,  5, 45, 87, 30,  2, 13, 31, 56,  3
		.word	  9, 43, 60,  5, 45, 12, 90, 12,  1, 20

matrix_b8:	.word	 12,  3, 70, 32, 13, 51		# MB(10,6)
		.word	  2, 12, 34,  2, 65,  6
		.word	 57, 34,  6, 13,  5,  3
		.word	 64,  4, 34, 98, 67,  1
		.word	  5, 23,  9, 34,  8, 45
		.word	 36,  5, 58,  2, 89,  8
		.word	  8, 65,  5, 49,  9, 56
		.word	 95,  8, 45, 12, 52,  4
		.word	  3, 30,  6, 67,  5, 34
		.word	 36,  2, 81,  4, 56,  7

matrix_c8:	.word	 0,  0,  0,  0,  0,  0		# MC(5,6)
		.word	 0,  0,  0,  0,  0,  0
		.word	 0,  0,  0,  0,  0,  0
		.word	 0,  0,  0,  0,  0,  0
		.word	 0,  0,  0,  0,  0,  0

# -----

mhdr:	.ascii	"\n----------------------------------------"
	.asciiz	"\nMatrix Set #"

msg_c:	.asciiz	"\nMatrix MC = (Matrix MA * Matrix MB) \n\n"


# -----
#  Local variables for multMatrix function.

msg_a:	.asciiz	"\n\nMatrix MA \n\n"
msg_b:	.asciiz	"Matrix MB \n\n"


# -----
#  Local variables for matrixPrint function.

new_ln:	.asciiz	"\n"

blnks1:	.asciiz	" "
blnks2:	.asciiz	"  "
blnks3:	.asciiz	"   "
blnks4:	.asciiz	"    "
blnks5:	.asciiz	"     "
blnks6:	.asciiz	"      "


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
#  Set data set counter.

	li	$s0, 1

# -----
#  Matrix Set #1
#  Multiply Matrix MA and MB, save in Matrix MC, and print.

	la	$a0, mhdr
	li	$v0, 4
	syscall
	move	$a0, $s0
	li	$v0, 1
	syscall

	la	$a0, matrix_a1
	la	$a1, matrix_b1
	la	$a2, matrix_c1
	lw	$a3, idim1
	lw	$t0, jdim1
	lw	$t1, kdim1
	subu	$sp, $sp, 8
	sw	$t0, ($sp)
	sw	$t1, 4($sp)

	jal	multMatrix

	addu	$sp, $sp, 8

	la	$a0, msg_c
	li	$v0, 4
	syscall

	la	$a0, matrix_c1			# matrix C
	lw	$a1, idim1			# i dimension
	lw	$a2, jdim1			# j dimension
	jal	matrixPrint

# -----
#  Matrix Set #2
#  Multiply Matrix A and B, save in Matrix C, and print.

	add	$s0, $s0, 1
	la	$a0, mhdr
	li	$v0, 4
	syscall
	move	$a0, $s0
	li	$v0, 1
	syscall

	la	$a0, matrix_a2
	la	$a1, matrix_b2
	la	$a2, matrix_c2
	lw	$a3, idim2
	lw	$t0, jdim2
	lw	$t1, kdim2
	subu	$sp, $sp, 8
	sw	$t0, ($sp)
	sw	$t1, 4($sp)

	jal	multMatrix

	addu	$sp, $sp, 8

	la	$a0, msg_c
	li	$v0, 4
	syscall

	la	$a0, matrix_c2			# matrix C
	lw	$a1, idim2			# i dimension
	lw	$a2, jdim2			# j dimension
	jal	matrixPrint

# -----
#  Matrix Set #3
#  Multiply Matrix A and B, save in Matrix C, and print.

	add	$s0, $s0, 1
	la	$a0, mhdr
	li	$v0, 4
	syscall
	move	$a0, $s0
	li	$v0, 1
	syscall

	la	$a0, matrix_a3
	la	$a1, matrix_b3
	la	$a2, matrix_c3
	lw	$a3, idim3
	lw	$t0, jdim3
	lw	$t1, kdim3
	subu	$sp, $sp, 8
	sw	$t0, ($sp)
	sw	$t1, 4($sp)

	jal	multMatrix

	addu	$sp, $sp, 8

	la	$a0, msg_c
	li	$v0, 4
	syscall

	la	$a0, matrix_c3			# matrix C
	lw	$a1, idim3			# i dimension
	lw	$a2, jdim3			# j dimension
	jal	matrixPrint

# -----
#  Matrix Set #4
#  Multiply Matrix A and B, save in Matrix C, and print.

	add	$s0, $s0, 1
	la	$a0, mhdr
	li	$v0, 4
	syscall
	move	$a0, $s0
	li	$v0, 1
	syscall

	la	$a0, matrix_a4
	la	$a1, matrix_b4
	la	$a2, matrix_c4
	lw	$a3, idim4
	lw	$t0, jdim4
	lw	$t1, kdim4
	subu	$sp, $sp, 8
	sw	$t0, ($sp)
	sw	$t1, 4($sp)

	jal	multMatrix

	addu	$sp, $sp, 8

	la	$a0, msg_c
	li	$v0, 4
	syscall

	la	$a0, matrix_c4			# matrix C
	lw	$a1, idim4			# i dimension
	lw	$a2, jdim4			# j dimension
	jal	matrixPrint

# -----
#  Matrix Set #5
#  Multiply Matrix A and B, save in Matrix C, and print.

	add	$s0, $s0, 1
	la	$a0, mhdr
	li	$v0, 4
	syscall
	move	$a0, $s0
	li	$v0, 1
	syscall

	la	$a0, matrix_a5
	la	$a1, matrix_b5
	la	$a2, matrix_c5
	lw	$a3, idim5
	lw	$t0, jdim5
	lw	$t1, kdim5
	subu	$sp, $sp, 8
	sw	$t0, ($sp)
	sw	$t1, 4($sp)

	jal	multMatrix

	addu	$sp, $sp, 8

	la	$a0, msg_c
	li	$v0, 4
	syscall

	la	$a0, matrix_c5			# matrix C
	lw	$a1, idim5			# i dimension
	lw	$a2, jdim5			# j dimension
	jal	matrixPrint

# -----
#  Matrix Set #6
#  Multiply Matrix A and B, save in Matrix C, and print.

	add	$s0, $s0, 1
	la	$a0, mhdr
	li	$v0, 4
	syscall
	move	$a0, $s0
	li	$v0, 1
	syscall

	la	$a0, matrix_a6
	la	$a1, matrix_b6
	la	$a2, matrix_c6
	lw	$a3, idim6
	lw	$t0, jdim6
	lw	$t1, kdim6
	subu	$sp, $sp, 8
	sw	$t0, ($sp)
	sw	$t1, 4($sp)

	jal	multMatrix

	addu	$sp, $sp, 8

	la	$a0, msg_c
	li	$v0, 4
	syscall

	la	$a0, matrix_c6			# matrix C
	lw	$a1, idim6			# i dimension
	lw	$a2, jdim6			# j dimension
	jal	matrixPrint

# -----
#  Matrix Set #7
#  Multiply Matrix A and B, save in Matrix C, and print.

	add	$s0, $s0, 1
	la	$a0, mhdr
	li	$v0, 4
	syscall
	move	$a0, $s0
	li	$v0, 1
	syscall

	la	$a0, matrix_a7
	la	$a1, matrix_b7
	la	$a2, matrix_c7
	lw	$a3, idim7
	lw	$t0, jdim7
	lw	$t1, kdim7
	subu	$sp, $sp, 8
	sw	$t0, ($sp)
	sw	$t1, 4($sp)

	jal	multMatrix

	addu	$sp, $sp, 8

	la	$a0, msg_c
	li	$v0, 4
	syscall

	la	$a0, matrix_c7			# matrix C
	lw	$a1, idim7			# i dimension
	lw	$a2, jdim7			# j dimension
	jal	matrixPrint

# -----
#  Matrix Set #8
#  Multiply Matrix MA and MB, save in Matrix MC, and print.

	add	$s0, $s0, 1
	la	$a0, mhdr
	li	$v0, 4
	syscall
	move	$a0, $s0
	li	$v0, 1
	syscall

	la	$a0, matrix_a8
	la	$a1, matrix_b8
	la	$a2, matrix_c8
	lw	$a3, idim8
	lw	$t0, jdim8
	lw	$t1, kdim8
	subu	$sp, $sp, 8
	sw	$t0, ($sp)
	sw	$t1, 4($sp)

	jal	multMatrix

	addu	$sp, $sp, 8

	la	$a0, msg_c
	li	$v0, 4
	syscall

	la	$a0, matrix_c8			# matrix C
	lw	$a1, idim8			# i dimension
	lw	$a2, jdim8			# j dimension
	jal	matrixPrint

# -----
#  Done, terminate program.

	li	$v0, 10
	syscall

.end main

# -------------------------------------------------------
#  function to multiply two matrix's.

# -----
#  Matrix multiplication formula:

#	for (i=0; i<iDIM; i++)
#		for j=0; j<jDIM; j++)
#			for (k=0; k<kDIM<; k++)
#				MC(i,j) = MC(i,j) + MA(i,k) * MB(k,j)
#			end_for
#		end_for
#	end_for

# -----
#  Formula for multiple dimension array indexing:
#	addr of ARRY(x,y) = [ (x * y_dimension) + y ] * data_size

# -----
#  Arguments
#	$a0 - address matrix a
#	$a1 - address matrix b
#	$a2 - address matrix c
#	$a3 - value, i dimension
#	stack, ($fp) - value, j dimension 
#	stack, 4($fp) - value, k dimension



#	YOUR CODE GOES HERE
.globl multMatrix
.ent multMatrix
multMatrix:

sub $sp, $sp, 24
sw $s0, ($sp)
sw $s1, 4($sp)
sw $s2, 8($sp)
sw $s3, 12($sp)
sw $fp, 16($sp)
sw $ra, 20($sp)
add $fp, $sp, 24

move $s0, $a0
move $s1, $a1
move $s2, $a2
move $s3, $a3

# print MA
la $a0, msg_a					# MA header
li $v0, 4
syscall

move $a0, $s0					# print MA
lw $a2, 4($fp)
move $a1, $s3
jal matrixPrint

# print MB
la $a0, msg_b					# MB header
li $v0, 4
syscall

move $a0, $s1					# print MB
lw $a2, ($fp)
lw $a1, 4($fp)
jal matrixPrint

# do math
li $t0, -1						# $t0 = i
lw $t3, ($fp)					# j dimension
lw $t4, 4($fp)					# k dimension

jSkip:
add $t0, $t0, 1
bge $t0, $s3, forExit			# for(i)
li $t1, -1

kSkip:
add $t1, $t1, 1
bge $t1, $t3, jSkip				# for(j)
li $t2, -1

kLoop:
add $t2, $t2, 1
bge $t2, $t4, kSkip				# for(k)



# MC(i,j) = MC(i,j) + MA(i,k) * MB(k,j)
# MA(i,k)
mul $t5, $t0, $t4				# (i*k)
add $t5, $t5, $t2				# ^+k
mul $t5, $t5, 4					# ^ * data size
add $t5, $s0, $t5				# MA(i,k)
lw $t5, ($t5)
# MB(k,j)
mul $t6, $t2, $t3				# (k*j)
add $t6, $t6, $t1				# ^+j
mul $t6, $t6, 4					# ^ * data size
add $t6, $s1, $t6				# MB(k,j)
lw $t6, ($t6)
mul $t7, $t5, $t6				# MA*MB
# MC(i,j)
mul $t8, $t0, $t3				# (i*j)
add $t8, $t8, $t1				# ^+j
mul $t8, $t8, 4					# ^ * data size
add $t8, $s2, $t8				# MC(i,j)
lw $t9,($t8)
add $t9, $t9, $t7				# MC+(MA*MB)
sw $t9, ($t8)
j kLoop

forExit:
lw $s0, ($sp)
lw $s1, 4($sp)
lw $s2, 8($sp)
lw $s3, 12($sp)
lw $fp, 16($sp)
lw $ra, 20($sp)
add $sp, $sp, 24
jr $ra

.end multMatrix
# ---------------------------------------------------------
#  Print matrix - M(i,j)

#  Arguments:
#	$a0 - starting address of matrix to ptint
#	$a1 - i dimension of matrix
#	$a2 - j dimension of matrix


#	YOUR CODE GOES HERE
.globl matrixPrint
.ent matrixPrint
matrixPrint:

subu $sp, $sp, 20
sw $s0, ($sp)
sw $s1, 4($sp)
sw $s2, 8($sp)
sw $s3, 12($sp)
sw $s4, 16($sp)

move $s0, $a0
move $s1, $a1
move $s2, $a2
li $s3, -1							# s3 - i
li $s4, 0							# s4 - j


printLoop:

la $a0, new_ln
li $v0, 4
syscall

add $s3, $s3, 1
move $s4, $zero
bge $s3, $s1, printExit
printI:
bge $s4, $s2 printLoop
mul $t0, $s3, $s2					# i*j
add $t0, $t0, $s4					# (i*j)+j
mul $t0, $t0, 4						# ^ * 4
add $t1, $s0, $t0					# + address

# spaces check
lw $t0, ($t1)
li $t3, 10							# if less than 10
bge $t0, $t3, biggerTen

la $a0, blnks6						# print 6 spaces
li $v0, 4
syscall
j printNum

biggerTen:
li $t3, 100
bge $t0, $t3, biggerHun				# if less than 100

la $a0, blnks5						# print 5 spaces
li $v0, 4
syscall
j printNum

biggerHun:
li $t3, 1000
bge $t0, $t3, biggerthous				# if less than 1000

la $a0, blnks4						# print 4 spaces
li $v0, 4
syscall
j printNum

biggerthous:
li $t3, 10000
bge $t0, $t3, biggerTenTh			# if less than 10000

la $a0, blnks3						# print 3 spaces
li $v0, 4
syscall
j printNum

biggerTenTh:
li $t3, 100000
bge $t0, $t3, biggerHunTh				# if less than 100000

la $a0, blnks2						# print 2 spaces
li $v0, 4
syscall
j printNum

biggerHunTh:
li $t3, 1000000
bge $t0, $t3, printNum				# if less than 1000000

la $a0, blnks1						# print 1 space
li $v0, 4
syscall

printNum:
lw $a0, ($t1)
li $v0, 1
syscall

add $s4, $s4, 1
j printI


printExit:

lw $s0, ($sp)
lw $s1, 4($sp)
lw $s2, 8($sp)
lw $s3, 12($sp)
lw $s4, 16($sp)
addu $sp, $sp, 20
jr $ra

.end matrixPrint