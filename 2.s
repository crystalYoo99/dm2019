.data
    array: .space 40
    message : .asciiz " => "
    
.text
.globl main


main : 
    addi $s1, $0, 10    #s0 is a constant 10
    add $s2, $0, $0     #s1 is i
    la $t0, array   #t0 is array reference
    add $t1, $t0, $0

loop1 : 
    beq $s2, $s1, end1  #if i == 10, go to end1
    li $v0, 5   #scanf
    syscall
    sw $v0, 0($t1)  #save to array
    addi $t1, $t1, 4    #move reference
    addi $s2, $s2, 1    #i++
    j loop1

end1 : 
    move $t1, $t0 #set reference
    lw $v0, 0($t1)  #save a[0] to v0
    add $s3, $0, $v0    #save a[0] to min (s3 is min)
    addi $s2, $0, 1 #i is 1
    addi $t1, $t1, 4

loop2 :
    add $t2, $0, $0
    beq $s2, $s1, end2  #if i == 10, go to end2
    lw $v0, 0($t1)  #load a[i] to v0
    slt $t2, $v0, $s3   #if a[i] < min, t2 is 1
    bne $t2, $0, condition  #if t2 is 1, go to condition
    addi $t1, $t1, 4    #move reference
    addi $s2, $s2, 1    #i++
    j loop2

condition : 
    add $s3, $0, $v0    #min is a[i] 
    add $s4, $0, $s2    #k is i (s4 is k)
    addi $t1, $t1, 4    #move reference
    addi $s2, $s2, 1    #i++
    j loop2

end2 : 
    li $v0, 1
    move $a0, $s4
    syscall

    li $v0, 4
    la $a0, message
    syscall

    li $v0, 1
    move $a0, $s3
    syscall

exit :
    li $v0, 10
    syscall

.end

