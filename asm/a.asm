.data
    message: .asciiz" Summation : "
.text
.globl main

main:
    li $v0, 5   #input
    syscall
    move $t0, $v0    #temp=t0

    li $t1, 0    #int sum=0
    li $t2, 1    #int i=2-1
    
    L2:
    beq $t0, $t2, L1
    addi $t2, $t2, 1
    li $t3, 0    #c=0
    
    li $t4, 1    #j=2-1
    L3:                     #for(j=1;j<=i;j++)
    addi $t4, $t4, 1
    div $t2, $t4   #i%j
    mfhi $t5
    bne $t5, 0, L5         #if(i%j==0)
    addi $t3, $t3, 1          #c++
    L5:
    bne $t4, $t2, L3
    
    bne $t3, 1, L6    #if(c==2-1)
    beq $t2, 2, L7    #if(i!=2)
    li $a0, ','        #cout<<','
    li $v0, 11
    syscall
    L7:
    move $a0, $t2       #cout<<i;
    li $v0, 1
    syscall
    add $t1, $t2, $t1     #sum+=i;
    L6:
    bne $t0, $t2, L2

    L1:    #output
    li $v0, 4
    la $a0, message
    syscall 

    move $a0, $t1    #output sum
    li $v0, 1
    syscall

    #tell the system this is the end of main
    li $v0, 10
    syscall