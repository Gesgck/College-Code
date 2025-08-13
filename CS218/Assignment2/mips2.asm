###########################################################################
#  Name: Alec Zheng
#  NSHE ID: 2001982564
#  Section: 1004
#  Assignment: MIPS #2
#  Description: RISC Architecture concepts, the MIPS Architecture, and SPIM

###########################################################
#  data segment

.data

aSides:	.word	  233,   214,   273,   231,   255 
	.word	  264,   273,   274,   223,   256 
	.word	  244,   252,   231,   242,   256 
	.word	  255,   224,   236,   275,   246 
	.word	  253,   223,   253,   267,   235 
	.word	  254,   229,   264,   267,   234 
	.word	  256,   253,   264,   253,   265 
	.word	  226,   252,   257,   267,   234 
	.word	  217,   254,   217,   225,   253 
	.word	  223,   273,   235,   261,   259 
	.word	  225,   224,   263,   247,   223 
	.word	  234,   234,   256,   264,   242 
	.word	  236,   252,   232,   231,   246 
	.word	  250,   254,   278,   288,   292 
	.word	  282,   295,   247,   252,   257 
	.word	  257,   267,   279,   288,   294 
	.word	  234,   252,   274,   286,   297 
	.word	  244,   276,   242,   236,   253 
	.word	  232,   251,   236,   287,   290 
	.word	  220,   241,   223,   232,   245 

bSides:	.word	  157,   187,   199,   111,   123 
	.word	  124,   125,   126,   175,   194 
	.word	  149,   126,   162,   131,   127 
	.word	  177,   199,   197,   175,   114 
	.word	  164,   141,   142,   173,   166 
	.word	  104,   146,   123,   156,   163 
	.word	  121,   118,   177,   143,   178 
	.word	  112,   111,   110,   135,   110 
	.word	  127,   144,   210,   172,   124 
	.word	  125,   116,   162,   128,   192 
	.word	  117,   114,   115,   172,   124 
	.word	  125,   116,   162,   138,   192 
	.word	  121,   183,   133,   130,   137 
	.word	  142,   135,   158,   123,   135 
	.word	  127,   126,   126,   127,   227 
	.word	  177,   199,   177,   175,   114 
	.word	  194,   124,   112,   143,   176 
	.word	  134,   126,   132,   156,   163 
	.word	  124,   119,   122,   183,   110 
	.word	  191,   192,   129,   129,   122 

rtAreas:
	.space	400 

len:	.word	100 

rtMin:	.word	0 
rtMid:	.word	0 
rtMax:	.word	0 
rtSum:	.word	0 
rtAve:	.word	0 

LN_CNTR	= 8


# -----

hdr:	.ascii	"MIPS Assignment #2 \n"
	.ascii	"  Right Triangle Areas Program:\n"
	.ascii	"  Also finds minimum, middle value, maximum, sum,\n"
	.asciiz	"  and average for the areas.\n\n"

a1_st:	.asciiz	"\nAreas Minimum = "
a2_st:	.asciiz	"\nAreas Median  = "
a3_st:	.asciiz	"\nAreas Maximum = "
a4_st:	.asciiz	"\nAreas Sum     = "
a5_st:	.asciiz	"\nAreas Average = "

newLn:	.asciiz	"\n"
blnks:	.asciiz	"  "


###########################################################
#  text/code segment

# --------------------
#  Compute right triangle areas.
#  Then find middle, max, sum, and average for the areas.

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
lw $t2, len
move $t3, $zero				# math register
la $t4, rtAreas
move $t5, $zero				# sum saved in $t5

areaLoop:
lw $t6, ($t0) 
add $t3, $t3, $t6			# aside
lw $t6, ($t1) 
mul $t3, $t3, $t6			# bside

addu $t0, $t0, 4
addu $t1, $t1, 4

divu $t3, $t3, 2			# div 2
sw $t3, ($t4)
addu $t4, $t4, 4
addu $t5, $t5, $t3
move $t3, $zero

subu $t2, $t2, 1
bnez $t2, areaLoop

sw $t5, rtSum				# sum saved
lw $t2, len
divu $t5, $t5, $t2
sw $t5, rtAve				# ave saved

# insertion sort
li $t0, 1					# i in $t0
lw $t1, len
subu $t1, $t1, 1			# length-1 in $t1
la $t2, rtAreas				# rtAreas in $t2
add $t2, $t2, 4				# start at arr[1]

insertSort:
bgtu $t0, $t1, sortExit		# for i=1 to length-1
add $t0, $t0, 1
lw $t3, ($t2)				# value = arr[i]
move $t5, $t2				# whileLoop arr[j]
move $t7, $t5				# arr[j+1] in $t7
sub $t5, $t5, 4
add $t2, $t2, 4
move $t4, $t0
sub $t4, $t4, 1				# j = i-1
# HERE
whileLoop:
bltz $t4, insert			# while (j>_0)
lw $t6, ($t5)				# value of arr[j] in $t6
blt $t6, $t3, insert		# arr[j] > value
sw $t6, ($t7)				# arr[j+1] = arr[j]
sub $t7, $t7, 4
sub $t5, $t5, 4
sub $t4, $t4, 1				# j = j-1
j whileLoop
insert:
sw $t3, ($t7)				# arr[j+1] = value
j insertSort
# HERE
sortExit:

la $t0, rtAreas
lw $t1, ($t0)
sw $t1, rtMin				# min saved
add $t0, $t0, 200
lw $t1, ($t0)
sub $t0, $t0, 4
lw $t2, ($t0)
add $t1, $t1, $t2
divu $t1, $t1, 2
sw $t1, rtMid				# mid saved
add $t0, $t0 200
lw $t1, ($t0)
sw $t1, rtMax				# max saved

# Display rtAreas array

lw $s0, len					# counts elements left
li $s1, 8					# counts for 8 per line
la $s2, rtAreas				# semiPerims in a saved register

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
j dispalyLoop

newlinePrint:
li $s1, 8
la $a0, newLn
li $v0, 4
syscall
j dispalyLoop

displayExit:



##########################################################
#  Display results.

	la	$a0, newLn		# print a newline
	li	$v0, 4
	syscall

#  Print min message followed by result.

	la	$a0, a1_st
	li	$v0, 4
	syscall				# print "min = "

	lw	$a0, rtMin
	li	$v0, 1
	syscall				# print min

# -----
#  Print middle message followed by result.

	la	$a0, a2_st
	li	$v0, 4
	syscall				# print "med = "

	lw	$a0, rtMid
	li	$v0, 1
	syscall				# print mid

# -----
#  Print max message followed by result.

	la	$a0, a3_st
	li	$v0, 4
	syscall				# print "max = "

	lw	$a0, rtMax
	li	$v0, 1
	syscall				# print max

# -----
#  Print sum message followed by result.

	la	$a0, a4_st
	li	$v0, 4
	syscall				# print "sum = "

	lw	$a0, rtSum
	li	$v0, 1
	syscall				# print sum

# -----
#  Print average message followed by result.

	la	$a0, a5_st
	li	$v0, 4
	syscall				# print "ave = "

	lw	$a0, rtAve
	li	$v0, 1
	syscall				# print average

# -----
#  Done, terminate program.

endit:
	la	$a0, newLn		# print a newline
	li	$v0, 4
	syscall

	li	$v0, 10
	syscall				# all done!

.end main

