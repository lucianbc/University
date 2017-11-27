# II.15) (2.5 puncte) (*)
#  Program care calculeaza suma bitilor (numarul bitilor egali cu 1) din
#   reprezentarea interna a unui numar natural. Numarul este dat intr-o
#   variabila n de tip word declarata cu initializare in program; suma va fi
#   stocata in final intr-o variabila s de tip word. Se vor folosi op. de
#   shiftare si op. logice pentru a muta/selecta bitii.
#  Ex: nr. 11001000 00001111 00000011 00001101 --> suma bitilor = 12

.data
n: .word 3356427021
s: .space 4

.text

main:

li $t0, 0                   # in t0 se calculeaza suma
lw $t1, n                   # t1 contine numarul curent

cat_timp:
 beq $t1, $zero, sfarsit    # daca n = 0, sfarsit
 li $t5, 1                  # t5 = 1
 and $t6, $t5, $t1          # t6 = n & 1
 add $t0, $t0, $t6          # t0 = t0 + t6
 srl $t1, $t1, 1            # n = n >> 1
 j cat_timp

sfarsit:
 sw $t0, s
 li $v0, 10
 syscall
