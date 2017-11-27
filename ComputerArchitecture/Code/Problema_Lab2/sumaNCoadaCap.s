# II.10) (2.5 puncte)(*)
#  Program care calculeaza 1+2+...+n, unde n este o variabila word declarata
#   cu initializare (numar natural) in program. Suma va fi stocata in final
#   intr-o variabila s de tip word.

.data
x: .word 0
n: .word 5
.text
main:

cat_timp:
 lw $t0, n
 ble $t0, $zero, end
 lw $t1, x
 add $t1, $t1, $t0
 sw $t1, x
 addi $t0, $t0, -1
 sw $t0, n
 j cat_timp

end:
 li $v0, 10
 syscall
