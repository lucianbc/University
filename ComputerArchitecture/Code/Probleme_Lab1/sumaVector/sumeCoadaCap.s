#program care calculeaza suma elementelor unui vector
.data
 suma: .space 4
 v: .word 1, 2, 3, 4, 5
 n: .word 5


.text
main:
 lw $t7,n
 li $t5,0
 sll $t7, $t7, 2

 addi $t7, -4

inceput:
 blt $t7, $zero, sfarsit
 lw $t6, v($t7)
 add $t5, $t5, $t6
 addi $t7, -4
 j inceput

sfarsit:
 sw $t5,suma
 li $v0,10
 syscall
