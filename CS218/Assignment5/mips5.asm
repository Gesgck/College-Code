###########################################################################
#  Name: Alec Zheng
#  NSHE ID: 2001982564
#  Section: 1004
#  Assignment: MIPS #5
#  Description: MIPS procedure calling convention, and basic recursion.

#  Provided template

#####################################################################
#  data segment

.data

# -----
#  Constants

TRUE = 1
FALSE = 0

# -----
#  Variables for main

hdr:		.ascii	"\n**********************************************\n"
		.ascii	"MIPS Assignment #5\n"
		.asciiz	"Ways to Make Change Program\n"

endMsg:		.ascii	"\nYou have reached recursive nirvana.\n"
		.asciiz	"Program Terminated.\n"

amountMinimum:	.word	1		# $0.01 dollars or 1 cent
amountMaximum:	.word	500		# $10.00 dollars or 1000 cents
initialAmount:	.word	0
waysCount:	.word	0
errorLimit:	.word	3		# 3 errors allowed, 4th error exits

coins:		.word	500, 100, 50, 25, 10, 5, 1
coinsCount:	.word	7

# -----
#  Variables for showWays() function.

cntMsg1:	.asciiz	"\nFor an amount of $"
cntDot:		.asciiz	"."
cntMsg2:	.asciiz	", there are "
cntMsg3:	.asciiz	" ways to make change.\n"

# -----
#  Variables for readInitAmt() function.

amtPmt1:	.asciiz	"  Enter Amount ("
amtPmt2:	.asciiz	" - "
amtPmt3:	.asciiz	"): "

err1:		.ascii	"\nError, amount out of range. \n"
		.asciiz	"Please re-enter data.\n"

err2:		.ascii	"\nSorry your having problems.\n"
		.asciiz	"Please try again later.\n"

spc:		.asciiz	"   "

# -----
#  Variables for prtNewline function.

newLine:	.asciiz	"\n"


# -----
#  Variables for makeChange() function.


# -----
#  Variables for continue.

qPmt:		.asciiz	"\nTry another amount (y/n)? "
ansErr:		.asciiz	"Error, must answer with (y/n)."

ans:		.space	3


#####################################################################
#  text/code segment

.text

.globl main
.ent main
main:

# -----
#  Display program header.

	la	$a0, hdr
	li	$v0, 4
	syscall					# print header

# -----
#  Function to read and amount (1-AMT_MAX).

doAnother:
	sw	$zero, initialAmount		# re-set variables
	sw	$zero, waysCount

	lw	$a0, amountMinimum		# min
	lw	$a1, amountMaximum		# max
	lw	$a2, errorLimit			# allowed errors
	la	$a3, initialAmount
	jal	readInitAmt

	bne	$v0, TRUE, programDone		# if not TRUE, exit

# -----
#  call makeChange to determine how many ways change could be made.
#	Returns integer answer.
#	HLL Call:
#		waysCount = makeChange(denomCount, initialAmount)

	la	$a0, coins
	lw	$a1, coinsCount
	lw	$a2, initialAmount
	jal	makeChange

	sw	$v0, waysCount

# ----
#  Display results (formatted).

	lw	$a0, initialAmount
	lw	$a1, waysCount
	jal	showWays

# -----
#  See if user wants to do another?

	jal	continue
	beq	$v0, TRUE, doAnother

programDone:
	li	$v0, 4
	la	$a0, endMsg
	syscall

# -----
#  Done, terminate program.

	li	$v0, 10
	syscall					# all done...
.end main

# =================================================================
#  Very simple function to print a new line.
#	Note, this routine is optional.

.globl	prtNewline
.ent	prtNewline
prtNewline:
	la	$a0, newLine
	li	$v0, 4
	syscall

	jr	$ra
.end	prtNewline

# =================================================================
#  Function to print final result (formatted).

#  Formatted message:
#    For an amount of $xx.yy, there are zz ways to make change.

# -----
#  Arguments
#	$a0 - initial amount
#	$a1 - ways to make change



#	YOUR CODE GOES HERE
.globl	showWays
.ent	showWays
showWays:

move $t0, $a0
move $t1, $a1

la $a0, newLine						# new line
li $v0, 4
syscall		

la $a0, cntMsg1						# prompt
li $v0, 4
syscall

li $t3, 10							# check how many zeros are needed
blt $t0, $t3, twoZero
li $t3, 100
blt $t0, $t3, oneZero
j noZero

twoZero:							# less than 10 cents
li $a0, 0
li $v0, 1
syscall

la $a0, cntDot
li $v0, 4
syscall

li $a0, 0
li $v0, 1
syscall

move $a0, $t0
li $v0, 1
syscall
j zeroDone

oneZero:							# less than 1 dollar
li $a0, 0
li $v0, 1
syscall

la $a0, cntDot
li $v0, 4
syscall

move $a0, $t0
li $v0, 1
syscall
j zeroDone

noZero:								# 1 dollar or more
div $t3, $t0, 100					# div by 100 for dollars

move $a0, $t3
li $v0, 1
syscall

la $a0, cntDot
li $v0, 4
syscall

rem $t3, $t0, 100

li $t4, 10
bge $t3, $t4, noZeroPrint

li $a0, 0
li $v0, 1
syscall

noZeroPrint:

move $a0, $t3						# rem for cents
li $v0, 1
syscall

zeroDone:

la $a0, cntMsg2
li $v0, 4
syscall

move $a0, $t1						# print # ways to make change
subu $a0, $a0, 1
li $v0, 1
syscall

la $a0, cntMsg3
li $v0, 4
syscall

jr $ra

.end showWays
# =================================================================
#  Function to prompt for and read initial amount.
#  Ensure that amount is between min cents (passed)
#  and max cents (passed).

# -----
#  HLL Call:
#	bool = readInitAmt(min, max, errLimit, &initAmt)

# -----
#    Arguments:
#	$a0 - minimum amount
#	$a1 - maximum amount
#	$a2 - error limit
#	$a3 - initial amount
#    Returns:
#	$v0 - n value



#	YOUR CODE GOES HERE
.globl	readInitAmt
.ent	readInitAmt
readInitAmt:

move $t0, $a0
move $t1, $a1
move $t2, $a2
move $t3, $a3				# save arguemnts
li $t5, 0

startLoop:
la $a0, amtPmt1				# start prompt
li $v0, 4
syscall

move $a0, $t0
li, $v0, 1
syscall

la $a0, amtPmt2
li $v0, 4
syscall

move $a0, $t1
li, $v0, 1
syscall

la $a0, amtPmt3				# prompt finsished 
li $v0, 4
syscall

li $v0, 5					# read integer
syscall

move $t6, $v0				# input saved in $t6	

# bound checking
lw $t4, amountMinimum
blt $t6, $t4, errorCheck
lw $t4, amountMaximum
bgt $t6, $t4, errorCheck
j checkGood

errorCheck:					# error found
addu $t5, $t5, 1
lw $t4, errorLimit			# check error limit
bgt $t5, $t4, errorExit

la $a0, err1
li $v0, 4
syscall	

j startLoop

checkGood:					# no errors
sw $t6, ($t3)				# save value

li $v0, TRUE				# exit TRUE
jr $ra

errorExit:					# error limit exceeded
la $a0, err2				# final error message
li $v0, 4
syscall	

lw $v0, FALSE				# exit with false
jr $ra

.end readInitAmt
#####################################################################
#  Function to count the number of ways that change can be made
#  given our standard US monetary denominations (cent,
#  nickel, dime, quarter, etc.).

# -----
#  Arguments:
#	$a0 - coins array
#	$a1 - denomCnt
#	$a2 - currentAmount
#  Returns:
#	$v0 - ways count

#	YOUR CODE GOES HERE
.globl	makeChange
.ent	makeChange
makeChange:

subu $sp, $sp, 8
sw $ra, ($sp)					# save return address
sw $a2, 4($sp)

# base cases
beqz $a2, oneExit				# if amt = 0
bltz $a2, zeroExit				# if amt < 0
blez $a1, zeroExit				# if cCnt <_ 0

subu $a1, $a1, 1
jal makeChange
mul $t0, $a1, 4
add $t1, $a0, $t0
lw $t2, ($t1)
lw $a2, 4($sp)
sub $a2, $a2, $t2
addu $a1, $a1, 1
jal makeChange


zeroExit:
lw $ra, ($sp)
lw $a2, 4($sp)
addu $sp, $sp, 8
jr $ra							# add nothing to $v0

oneExit:
lw $ra, ($sp)
lw $a2, 4($sp)
addu $sp, $sp, 8
add $v0, $v0, 1					# add 1 to $v0
jr $ra

.end makeChange
#####################################################################
#  Function to ask user if they want to continue.

#  Basic flow:
#	prompt user
#	read user answer (as character)
#		if y -> return TRUE
#		if n -> return FALSE
#	otherwise, display error and loop to re-prompt

# -----
#  Arguments:
#	none
#  Returns:
#	$v0 - TRUE/FALSE




#	YOUR CODE GOES HERE
.globl	continue
.ent	continue
continue:

la $a0, newLine				# new line
li $v0, 4
syscall		
la $a0, newLine				# new line
li $v0, 4
syscall		

la $a0, qPmt				# prompt
li $v0, 4
syscall

li $v0, 8
la $a0, ans
li $a1, 3					
syscall

la $a0, newLine				# new line
li $v0, 4
syscall	

li $v0, TRUE
la $t2, ans
lb $t0, ($t2)
li $t1, 0x79
beq $t0, $t1, contAfter		# check for y
li $t1, 0x6e
bne $t0, $t1, contError		# check for n
li $v0, FALSE
contAfter:
jr $ra

contError:
la $a0, ansErr				# error prompt
li $v0, 4
syscall
j continue

.end continue
#####################################################################

