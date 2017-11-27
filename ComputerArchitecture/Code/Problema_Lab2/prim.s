# II.4) (3 puncte)
# Program care verifica daca un numar natural este prim. Numarul este dat
#  intr-o variabila n de tip word declarata cu initializare in program;
#  raspunsul va fi stocat intr-o variabila x de tip byte sub forma 0=neprim,
#  1=prim.

.data
x: .byte 0
n: .word 1

.text
main:
lw $t7, n
li $t1, 2
div $t7, $t1
mflo $t6

cat_timp:
 bgt $t1, $t6, final
 div $t7, $t1
 mfhi $t4
 bne $t4, $zero, cont
  j final
 cont:
 addi $t1, $t1, 1
 j cat_timp

final:
 addi $t6, $t6, 1
 bne $t6, $t1, end
  li $t0, 1
  sb $t0, x
end:
 li $v0, 10
 syscall
