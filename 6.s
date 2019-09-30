.data

  array: .space 40  #declare array which size is 10
  str: .asciiz "=>"
    

 .text
 .globl main

main:
 
    addi $s1, $0, 10     #loop 제약조건
    add $s2, $0, $0      #loop의 count
    la $t0, array  #get reference of array
    move $t1, $t0
 
loop:
   
    beq $s2, $s1, Jump   #count 값과 10이 같으면 jump
                        #그렇지 않다면
    #slti  $t3, $s2, 10  #s2(count) < 10 -->1
    #beq   $0, $t3, Jump

    li $v0,5             #scan call
    syscall
    #move $t4, $v0
   
    sw $v0,0($t1)        #array[i] = n 입력받은값할당      
    addi $t1, $t1, 4     #array가리키는 포인터 한칸 전진       
    addi $s2, $s2, 1     ##count +1 효과
    j loop        

Jump:
li $v0, 4
la $a0, str
syscall
    
PRINT: 
       

EIXT:
    li $v0,10
    syscall
.end