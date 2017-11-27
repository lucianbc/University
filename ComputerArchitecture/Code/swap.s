#swap
.data
 x:.word 1
 y:.word 2
.text
main:
 lw $t0,x
 lw $t1,y
 sw $t0,y
 sw $t1,x
li $v0,10
syscall