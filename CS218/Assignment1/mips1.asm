###########################################################################
#  Name: Alec Zheng
#  NSHE ID: 2001982564
#  Section: 1004
#  Assignment: MIPS #1
#  Description: RISC Architecture concepts, the MIPS Architecture, and SPIM

################################################################################
#  data segment

.data

aSides:	.word	 121,  123,  131,  139,  141,  149,  153,  157,  163,  169
	.word	 201,  207,  212,  215,  223,  227,  231,  236,  241,  245
	.word	 251,  252,  262,  264,  271,  273,  287,  289,  293,  299
	.word	 301,  305,  312,  315,  326,  328,  332,  337,  341,  343
	.word	 401,  408,  411,  413,  421,  424,  431,  434,  445,  448
	.word	 453,  454,  460,  462,  474,  475,  486,  487,  491,  492
	.word	 501,  504,  515,  517,  524,  525,  535,  537,  543,  548
	.word	 551,  553,  563,  567,  577,  579,  582,  588,  593,  595

bSides:	.word	  75,   81,   83,   87,   89,   91,   94,   97,   99,  101
	.word	 107,  111,  120,  121,  137,  141,  157,  167,  177,  181
	.word	 191,  199,  202,  209,  215,  219,  223,  225,  231,  242
	.word	 244,  249,  251,  253,  266,  269,  271,  272,  280,  288
	.word	 291,  299,  301,  303,  307,  311,  321,  329,  330,  331
	.word	 332,  351,  376,  387,  390,  400,  411,  423,  432,  445
	.word	 469,  474,  477,  479,  482,  484,  486,  488,  492,  493
	.word	 557,  587,  599,  601,  623,  624,  625,  626,  627,  628

cSides:	.word	  13,   17,   21,   23,   33,   39,   47,   53,   63,   79
	.word	  81,   93,   99,  100,  103,  107,  109,  111,  121,  127
	.word	 132,  137,  142,  149,  154,  161,  167,  178,  186,  197
	.word	 206,  212,  222,  231,  246,  250,  254,  278,  288,  292
	.word	 303,  315,  321,  339,  348,  359,  362,  374,  380,  391
	.word	 400,  404,  406,  407,  424,  425,  426,  429,  448,  492
	.word	 501,  513,  524,  536,  540,  556,  575,  587,  590,  596
	.word	 634,  652,  674,  686,  697,  704,  716,  720,  736,  753
	.word	 782,  795,  807,  812,  817,  827,  837,  839,  841,  844

semiPerims:
	.space	320

length:	.word	80

sMin:	.word	0
sMid:	.word	0
sMax:	.word	0
sSum:	.word	0
sAve:	.word	0 


# -----

hdr:	.ascii	"MIPS Assignment #1 \n"
	.ascii	"Program to calculate the semi-perimeter of each right "
	.ascii	"triangle in a\n series of right triangles.  Also finds "
	.asciiz	"min, mid, max, sum, and average\n for the semi-perimeters.\n"

newLine:
	.asciiz	"\n"
blnks:	.asciiz	"  "

a1_st:	.asciiz	"\nSemi-Perimeters min = "
a2_st:	.asciiz	"\nSemi-Perimeters mid = "
a3_st:	.asciiz	"\nSemi-Perimeters max = "
a4_st:	.asciiz	"\nSemi-Perimeters sum = "
a5_st:	.asciiz	"\nSemi-Perimeters ave = "


###########################################################
#  text/code segment

.text
.globl main
.ent main
main:

# -----
#  Display header.

	la	$a0, hdr
	li	$v0, 4
	syscall				# print header

# -----


#	YOUR CODE GOES HERE

la $t0, aSides
la $t1, bSides
la $t2, cSides
lw $t3, length
move $t4, $zero				# semiPerims[n] saved in $t4
la $t5, semiPerims
move $t7, $zero				# sum saved in $t7

perimLoop:
lw $t6, ($t0) 
add $t4, $t4, $t6			# aside
lw $t6, ($t1) 
add $t4, $t4, $t6			# bside
lw $t6, ($t2) 
add $t4, $t4, $t6			# cside

addu $t0, $t0, 4
addu $t1, $t1, 4
addu $t2, $t2, 4

divu $t4, $t4, 2			# div 2
sw $t4, ($t5)
addu $t5, $t5, 4
add $t7, $t7, $t4			# sum saved in $t7
move $t4, $zero

sub $t3, $t3, 1
bnez $t3, perimLoop			# loop

sw $t7, sSum				# sum
lw $t3, length
divu $t7, $t7, $t3
sw $t7, sAve				# ave
la $t5, semiPerims
lw $t0, ($t5)
sw $t0, sMin				# min



addu $t5, $t5, 160
lw $t0, ($t5)
subu $t5, $t5, 4
lw $t1, ($t5)
addu $t0, $t0, $t1
divu $t0, $t0, 2
sw $t0, sMid				# mid
addu $t5, $t5, 160
lw $t0, ($t5)
sw $t0, sMax				# max


##########################################################
#  Display numbers (8 numbers per row) from the array.
lw $s0, length				# counts elements left
li $s1, 8					# counts for 8 per line
la $s2, semiPerims			# semiPerims in a saved register

dispalyLoop:
lw $a0, ($s2)
li $v0, 1
syscall

la $a0, blnks
li $v0, 4
syscall

addu $s2, $s2, 4
subu $s0, $s0, 1
subu $s1, $s1, 1

beqz $s0, displayExit		# exit condition

beqz $s1, newlinePrint
b dispalyLoop

newlinePrint:
li $s1, 8
la $a0, newLine
li $v0, 4
syscall
b dispalyLoop

displayExit:
la $a0, newLine
li $v0, 4
syscall

##########################################################
#  Display results.

	la	$a0, newLine		# print a newline
	li	$v0, 4
	syscall
	la	$a0, newLine		# print a newline
	li	$v0, 4
	syscall

#  Print min message followed by result.

	la	$a0, a1_st
	li	$v0, 4
	syscall				# print "min = "

	lw	$a0, sMin
	li	$v0, 1
	syscall				# print min

# -----
#  Print middle message followed by result.

	la	$a0, a2_st
	li	$v0, 4
	syscall				# print "med = "

	lw	$a0, sMid
	li	$v0, 1
	syscall				# print mid

# -----
#  Print max message followed by result.

	la	$a0, a3_st
	li	$v0, 4
	syscall				# print "max = "

	lw	$a0, sMax
	li	$v0, 1
	syscall				# print max

# -----
#  Print sum message followed by result.

	la	$a0, a4_st
	li	$v0, 4
	syscall				# print "sum = "

	lw	$a0, sSum
	li	$v0, 1
	syscall				# print sum

# -----
#  Print average message followed by result.

	la	$a0, a5_st
	li	$v0, 4
	syscall				# print "ave = "

	lw	$a0, sAve
	li	$v0, 1
	syscall				# print average

# -----
#  Done, terminate program.

endit:
	la	$a0, newLine		# print a newline
	li	$v0, 4
	syscall

	li	$v0, 10
	syscall				# all done!

.end main

