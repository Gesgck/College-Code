#  Name: Alec Zheng
#  NSHE ID: 2001982564

.data

header: .asciiz     "Area and perimeter of a rectangle"
askL:   .asciiz     "\nenter a length: "
askW:   .asciiz     "\nenter a width: "
end1:   .asciiz     "\nArea = "
end2:   .asciiz     ", Perimeter = "

length: .word       0
width:  .word       0
area:   .word       0
perim:  .word       0

.text
.globl main
.ent main
main:

    li $v0, 4               # print header
    la $a0, header
    syscall

    li $v0, 4               # print ask length 
    la $a0, askL
    syscall

    li $v0, 5               # get length
    syscall

    sw $v0, length

    li $v0, 4               # print ask width
    la $a0, askW
    syscall

    li $v0, 5               # get width
    syscall

    sw $v0, width

    ###########################################
    # math

    lw $t0, length
    lw $t1, width

    mul $s0, $t0, $t1       # area = l * w
    mul $t0, $t0, 2
    mul $t1, $t1, 2
    add $s1, $t0, $t1       # perim = (2*l)+(2*w)

    # ending

    li $v0, 4               # print "area = "
    la $a0, end1
    syscall

    li $v0, 1               # print area
    move $a0, $s0
    syscall

    li $v0, 4               # print ", perimeter = "
    la $a0, end2
    syscall

    li $v0, 1               # print perimeter
    move $a0, $s1
    syscall

	li	$v0, 10
	syscall					# return 0
.end main