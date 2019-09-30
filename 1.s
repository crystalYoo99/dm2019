.data
    message : .asciiz "sum = "
.text
.globl main

main : 
    addi $t0, $0, 1000
    add $t1, $0, $0
    add $t2, $0, $0

loop : 
    beq $t1, $t0, end
    add $t2, $t2, $t1
    addi $t1, $t1, 1
    j loop

end :
    li $v0, 4
    la $a0, message
    syscall

    li $v0, 1
    move $a0, $t2
    syscall

exit :
    li $v0, 10
    syscall
    
.end

