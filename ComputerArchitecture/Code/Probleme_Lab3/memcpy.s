# III.2) (puncte - vezi in text) (*)
# a) (1.5 puncte)
#   Functie MIPS ce implementeaza functia C "memcpy":
#
#      void *memcpy(void *dest, const void *src, size_t n);
#
#  care copiaza a "n" octeti de la adresa "src" la adresa "dest" si returneaza
#  "dest" (putem considera "src" si "dest" adrese obisnuite si "n" word).
#  Program ilustrativ care copiaza continutul unui vect. de word-uri in altul.
# b) (1 punct)
#   Acelasi lucru cu un macro.

.data
v: .word 7 8 9 10 11 12
s: .space 24
n: .word 24

.text

# $a0 -> dest, $a1 -> src, $a2 -> n
memcpy:
 addi $a2, $a2, -1

 add $t0, $a0, $a2               # $t0 -> adresa destinatie
 add $t1, $a1, $a2               # $t1 -> adresa sursa

 copiere:
  blt $t0, $a0, sf
  lb $t7, 0($t1)
  sb $t7, 0($t0)
  addi $t0, $t0, -1
  addi $t1, $t1, -1
  j copiere
 sf:

 jr $ra

main:
 la $a0, s
 la $a1, v
 lw $a2, n
 jal memcpy

 li $v0, 10
 syscall
