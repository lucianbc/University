# II.15) (2.5 puncte) (*)
#  Program care calculeaza suma bitilor (numarul bitilor egali cu 1) din
#   reprezentarea interna a unui numar natural. Numarul este dat intr-o
#   variabila n de tip word declarata cu initializare in program; suma va fi
#   stocata in final intr-o variabila s de tip word. Se vor folosi op. de
#   shiftare si op. logice pentru a muta/selecta bitii.
#  Ex: nr. 11001000 00001111 00000011 00001101 --> suma bitilor = 12

.data
n: .word 12
#1678705421
s: .space 4
.text
main:

lw $t0, n
li $t2, 0

beq $t0, $zero, cat_timp
 addi $t2, $t2, 1

cat_timp:
 addi $t1, $t0, -1
 and $t0, $t0, $t1
 bne $t0, $zero, cont
  j end
 cont:
  addi $t2, $t2, 1
  j cat_timp

end:
 sw $t2, s
 li $v0, 10
 syscall
