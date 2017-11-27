# II.16) (2.5 puncte)
#  Program care construieste imaginea in oglinda a configuratiei din locatia
#   unei variabile word declarata cu initializare in program; imaginea se va
#   construi in aceeasi locatie. Se vor folosi op. de shiftare, rotire,
#   logice.
#  Ex: nr. 11001000 00001111 00000000 00000001 -->
#          10000000 00000000 11110000 00010011

.data
n: .word 3356426241
x: .space 4

.text

main:
 li $t0, 0
 lw $t1, n

cat_timp:
 beq $t1, $zero, sfarsit
  li $t5, 1
  and $t6, $t5, $t1
  sll $t0, $t0, 1
  or $t0, $t0, $t6
  srl $t1, $t1, 1
  j cat_timp

sfarsit:
 sw $t0, n
 li $v0, 10
 syscall
