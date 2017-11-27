# Program care sorteaza un vector de numere.
.data
 v: .word 2, 9, 7
 n: .word 3
.text

main:
 li $t0, 0
 lw $t7, n
 sll $t7, $t7, 2

parcurgere:
 bge $t0,$t7,fin
 move $t2,$t0
 addi $t1,$t0,4

scanare:
 bge $t1,$t7,interschimbare
 lw $t4,v($t2)
 lw $t5,v($t1)
 bge $t5,$t4,sariPoz
 move $t2,$t1

sariPoz:
 addi $t1,$t1,4
 j scanare

interschimbare:
 lw $t4, v($t0)
 lw $t5, v($t2)
 sw $t4, v($t2)
 sw $t5, v($t0)
 addi $t0,$t0,4
 j parcurgere

fin:
 li $v0, 10
 syscall
