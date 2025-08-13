#  Name: Alec Zheng
#  NSHE ID: 2001982564

.data

ask:   .asciiz      "\nEnter a number: "
res1:   .asciiz     "\nThe numbers are the same"
res2:   .asciiz     "\nThe numbers are not the same"

.text
.globl main
.ent main
main:
    li $v0, 4
    la $a0, ask
    syscall    

    li $v0, 5
    syscall

    move $s0, $v0

    li $v0, 4
    la $a0, ask
    syscall    

    li $v0, 5
    syscall

    move $s1, $v0   

    beq $s0, $s1, same

    li $v0, 4
    la $a0, res2
    syscall     

    j end

    same:
    li $v0, 4
    la $a0, res1
    syscall 

    end:
	li	$v0, 10
	syscall
.end main