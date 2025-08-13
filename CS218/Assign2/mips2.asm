###########################################################################
#  Name: Alec Zheng
#  NSHE ID: 2001982564
#  Section: 1004
#  Assignment: MIPS #2
#  Description: find the volume of cubes



###########################################################
#  data segment

.data

lengths:
	.word	  327,   344,   310,   372,   324 
	.word	  325,   316,   362,   328,   392 
	.word	  317,   314,   315,   372,   324 
	.word	  325,   316,   362,   338,   392 
	.word	  321,   383,   333,   330,   337 
	.word	  342,   335,   358,   323,   335 
	.word	  327,   326,   326,   327,   227 
	.word	  357,   387,   399,   311,   323 
	.word	  324,   325,   326,   375,   394 
	.word	  349,   326,   362,   331,   327 
	.word	  377,   399,   397,   375,   314 
	.word	  364,   341,   342,   373,   366 
	.word	  304,   346,   323,   356,   363 
	.word	  321,   318,   377,   343,   378 
	.word	  312,   311,   310,   335,   310 
	.word	  377,   399,   377,   375,   314 
	.word	  394,   324,   312,   343,   376 
	.word	  334,   326,   332,   356,   363 
	.word	  324,   319,   322,   383,   310 
	.word	  391,   392,   329,   329,   322 

widths:
	.word	  226,   252,   257,   267,   234 
	.word	  217,   254,   217,   225,   253 
	.word	  223,   273,   235,   261,   259 
	.word	  225,   224,   263,   247,   223 
	.word	  234,   234,   256,   264,   242 
	.word	  233,   214,   273,   231,   255 
	.word	  264,   273,   274,   223,   256 
	.word	  244,   252,   231,   242,   256 
	.word	  255,   224,   236,   275,   246 
	.word	  253,   223,   253,   267,   235 
	.word	  254,   229,   264,   267,   234 
	.word	  256,   253,   264,   253,   265 
	.word	  236,   252,   232,   231,   246 
	.word	  250,   254,   278,   288,   292 
	.word	  282,   295,   247,   252,   257 
	.word	  257,   267,   279,   288,   294 
	.word	  234,   252,   274,   286,   297 
	.word	  244,   276,   242,   236,   253 
	.word	  232,   251,   236,   287,   290 
	.word	  220,   241,   223,   232,   245 

heights:
	.word	  124,   119,   122,   183,   110
	.word	  191,   192,   129,   129,   122
	.word	  135,   226,   162,   137,   127
	.word	  127,   159,   177,   175,   144
	.word	  179,   153,   136,   140,   235
	.word	  117,   114,   115,   172,   124
	.word	  125,   116,   162,   138,   192
	.word	  111,   183,   133,   130,   127
	.word	  111,   115,   158,   113,   115
	.word	  117,   126,   116,   117,   227
	.word	  177,   199,   177,   175,   114
	.word	  194,   124,   112,   143,   176
	.word	  134,   126,   132,   156,   163
	.word	  112,   154,   128,   113,   132
	.word	  161,   192,   151,   213,   126
	.word	  269,   114,   122,   115,   131
	.word	  194,   124,   114,   143,   176
	.word	  134,   126,   122,   156,   163
	.word	  149,   144,   114,   134,   167
	.word	  143,   129,   161,   165,   136

len:	.word	100 

volumes:
	.space	400 

vMin:	.word	0 
vMid:	.word	0 
vMax:	.word	0 
vSum:	.word	0 
vAve:	.word	0 

# -----

hdr:	.ascii	"MIPS Assignment #2 \n"
	.ascii	"  Rectangular Prism Volumes Program:\n"
	.ascii	"  Also finds minimum, middle value, maximum, sum,"
	.asciiz	" and average for the volumes.\n\n"

a1_st:	.asciiz	"\nVolumes Minimum      = "
a2_st:	.asciiz	"\nVolumes Est. Median  = "
a3_st:	.asciiz	"\nVolumes Maximum      = "
a4_st:	.asciiz	"\nVolumes Sum          = "
a5_st:	.asciiz	"\nVolumes Average      = "

newLn:	.asciiz	"\n"
blnks:	.asciiz	"  "


###########################################################
#  text/code segment

# --------------------
#  Compute volumes.
#  Then find middle, max, sum, and average for the volumes.

.text
.globl main
.ent main
main:

# ******************************
#  Display header.

	la	$a0, hdr
	li	$v0, 4
	syscall				# print header

# ******************************




#	YOUR CODE GOES HERE

la $t0, lengths			# load necessary addresses
la $t1, widths
la $t2, heights
la $t3, volumes
lw $t4, len

volLoop:
lw $t5, ($t0)
lw $t6, ($t1)
mul $t5, $t5, $t6		# length * width
lw $t6, ($t2)
mul $t5, $t5, $t6		# above * height
sw $t5, ($t3)
add $t0, $t0, 4
add $t1, $t1, 4
add $t2, $t2, 4
add $t3, $t3, 4
sub $t4, $t4, 1
bnez $t4, volLoop		# exit condition



# print results
la $s0, volumes
lw $s1, len

printLoop:
lw	$a0, ($s0)
li	$v0, 1
syscall

la	$a0, blnks
li	$v0, 4
syscall

add $s0, 4
sub $s1, $s1, 1
bnez $s1, printLoop 



# find stats
la $t0, volumes
lw $t1, len
lw $t3, ($t0)			# minimum
lw $t4, ($t0)			# maximum
lw $t5, ($t0)

statsLoop:
add $t0, $t0, 4			# inc volumes
sub $t1, $t1, 1
beqz $t1, statsExit
lw $t2, ($t0)
add $t5, $t5, $t2		# add up sum
bgtu $t2, $t4, bigger	# check bigger
bltu $t2, $t3, smaller	# check smaller
j statsLoop

bigger:
move $t4, $t2
j statsLoop

smaller:
move $t3, $t2
j statsLoop

statsExit:
sw $t3, vMin			# min
sw $t4, vMax			# max
sw $t5, vSum			# sum
lw $t0, len
div $t0, $t5, $t0		# average
sw $t0, vAve



# est med
la $t0, volumes
lw $t1, len
sub $t1, $t1, 1
lw $t2, ($t0)
mul $t1, $t1, 4			# length * 4
addu $t0, $t0, $t1
lw $t3, ($t0)
addu $t2, $t2, $t3		# first + last element of volumes

lw $t0, len
remu $t0, $t0, 2		# find if even or odd
beqz $t0, evenMed

# odd length
lw $t0, len
mul $t0, $t0, 4
divu $t0, $t0, 2
la $t1, volumes
add $t1, $t1, $t0		# middle value
lw $t3, ($t1)
add $t2, $t2, $t3
divu $t2, $t2, 3
sw $t2, vMid
j medExit

# even length
evenMed:
lw $t0, len
mul $t0, $t0, 4
divu $t0, $t0, 2
la $t1, volumes
add $t1, $t1, $t0		# middle value
lw $t3, ($t1)
add $t2, $t2, $t3
sub $t1, $t1, 4			# middle value + 1
lw $t3, ($t1)
add $t2, $t2, $t3
divu $t2, $t2, 4
sw $t2 vMid

medExit:

# ******************************
#  Display results.

	la	$a0, newLn		# print a newline
	li	$v0, 4
	syscall

#  Print min message followed by result.

	la	$a0, a1_st
	li	$v0, 4
	syscall				# print "min = "

	lw	$a0, vMin
	li	$v0, 1
	syscall				# print min

# -----
#  Print middle message followed by result.

	la	$a0, a2_st
	li	$v0, 4
	syscall				# print "est med = "

	lw	$a0, vMid
	li	$v0, 1
	syscall				# print mid

# -----
#  Print max message followed by result.

	la	$a0, a3_st
	li	$v0, 4
	syscall				# print "max = "

	lw	$a0, vMax
	li	$v0, 1
	syscall				# print max

# -----
#  Print sum message followed by result.

	la	$a0, a4_st
	li	$v0, 4
	syscall				# print "sum = "

	lw	$a0, vSum
	li	$v0, 1
	syscall				# print sum

# -----
#  Print average message followed by result.

	la	$a0, a5_st
	li	$v0, 4
	syscall				# print "ave = "

	lw	$a0, vAve
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

