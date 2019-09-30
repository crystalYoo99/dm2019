.text
.globl main

main : 
    li $v0, 4
    la $a0, msg1
    syscall
    la $a1, array
    li $t0, 5
    li $t1, 0

loop1 : 
    li $v0, 5
    syscall
    sll $t2, $t1, 2
    add $s0, $a1, $t2
    sw $v0, 0($s0)
    addi $t0, $t0, -1
    addi $t1, $t1, 1
    bgtz $t0, loop1
    li $v0, 4
    la $a0, msg2
    syscall
    li $t0, 5
    li $t1, 0

loop2 : 
    sll $t2, $t1, 2
    add $t3, $a1, $t2
    lw $t4, 0($t3)
    la $a0, msg4
    syscall
    li $v0, 1
    addi $a0, $t4, 1
    syscall

    addi $t0, $t0, -1
    addi $t1, $t1, 1
    bgtz $t0, loop2
    li $v0, 4
    la $a0, msg3
    syscall
    li $v0, 10
    syscall

.data
    msg1 : .asciiz "\n5개 초기 정수값 입력\n"
    msg2 : .asciiz "\n5개 계산된 정수 값 출력\n"
    msg3 : .asciiz "\n프로그램 종료\n"
    msg4 : .asciiz "\n출력 값\n"
    array : .space 20

exit : 
    li $v0, 10
    syscall



.end
