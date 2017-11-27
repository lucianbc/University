# II.10) (2.5 puncte)(*)
#  Program care calculeaza 1+2+...+n, unde n este o variabila word declarata
#   cu initializare (numar natural) in program. Suma va fi stocata in final
#   intr-o variabila s de tip word.

.data
n: .word 5
x: .space 4
i: .space 4
.text
main:
#initializare
li $t0, 5
sw $t0, n
li $t0, 0
sw $t0, x
#sfarsit initializare

li $t0, 1
cat_timp:
 lw $t1, n
 bgt $t0, $t1, end
 lw $t1, x
 add $t1, $t1, $t0
 sw $t1, x
 addi $t0, $t0, 1
 j cat_timp

end:
 li $v0, 10
 syscall
