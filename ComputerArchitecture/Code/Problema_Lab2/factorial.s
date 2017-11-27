# II.9) (2.5 puncte) (*)
#  Program care calculeaza factorialul unui numar natural. Numarul este
#   dat intr-o variabila n de tip word declarata cu initializare in program;
#   factorialul va fi stocata in final intr-o variabila s de tip word.

.data
n: .word 5
x: .word 1

.text
main:

li $t0, 1
lw $t1, n

cat_timp:
 bgt $t0, $t1, end
 lw $t2, x
 mult $t0, $t2
 mflo $t2
 sw $t2, x
 addi $t0, $t0, 1
 j cat_timp

end:
 li $v0, 10
 syscall
