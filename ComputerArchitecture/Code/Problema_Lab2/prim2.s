# II.4) (3 puncte)
# Program care verifica daca un numar natural este prim. Numarul este dat
#  intr-o variabila n de tip word declarata cu initializare in program;
#  raspunsul va fi stocat intr-o variabila x de tip byte sub forma 0=neprim,
#  1=prim.

.data
t: .word 11
x: .byte 0
u: .word 11
n: .word 5

.text

main:

li $t7, 0
lw $t1, n
li $t0, 1

cat_timp:
 bgt $t0, $t1, final
 div $t1, $t0
 mfhi $t2
 bne $t2, $zero, cont
  addi $t7, $t7, 1
 cont:
  addi $t0, $t0, 1
  j cat_timp

# $7 retine numarul divizorilor lui n; verific daca numarul divizorilor este diferit de 2
final:
 li $t2, 2
 seq $t1, $t2, $t7
 sb $t1, x

li $v0, 10
syscall
