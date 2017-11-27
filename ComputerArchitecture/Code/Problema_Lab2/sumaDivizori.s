#II.3) (3 puncte)   (*)
# Program care calculeaza suma divizorilor unui numar natural. Numarul este
#  dat intr-o variabila n de tip word declarata cu initializare in program;
#  suma va fi stocata in final intr-o variabila s de tip word.

.data
n: .space 12
s: .space 4

.text

main:

lw $t0, n
li $t1, 2
li $t7, 0

cat_timp:
 li $t3, 2
 div $t0, $t3
 mflo $t3
 bgt $t1, $t3, exit
 div $t0, $t1
 mfhi $t3
 bne $t3, $zero, rep
  add $t7, $t7, $t1
 rep:
  addi $t1, $t1, 1
  j cat_timp

exit:
 sw $t7, s
 li $v0, 10
 syscall
