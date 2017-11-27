#program care calculeaza suma elementelor unui vector
.data
 v: .word 1, 2, 3, 4, 5
 n: .word 5
 suma: .space 4

.text
main:
 li $t0,0
 lw $t7,n
 li $t5,0
 #sll $t7, $t7, 2

inceput:
 bge $t0, $t7, sfarsit
 li $t1, 4
 mult $t0, $t1
 mflo $t1
 lw $t6, v($t1)
 add $t5, $t5, $t6
 addi $t0, 1
 j inceput

sfarsit:
 sw $t5,suma
 li $v0,10
 syscall
