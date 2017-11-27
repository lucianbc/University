# II.16) (2.5 puncte)
#  Program care construieste imaginea in oglinda a configuratiei din locatia
#   unei variabile word declarata cu initializare in program; imaginea se va
#   construi in aceeasi locatie. Se vor folosi op. de shiftare, rotire,
#   logice.
#  Ex: nr. 11001000 00001111 00000000 00000001 -->
#          10000000 00000000 11110000 00010011

.data
x: .word 3356426241

.text
main:
 lw $t0, x

 # interschimba perechi de 1 bit
 # t0 = ((t0 >> 1) & 0x55555555) | ((t0 & 0x55555555) << 1)
 li $t1, 0x55555555
 srl $t2, $t0, 1
 and $t2, $t2, $t1
 and $t3, $t0, $t1
 sll $t3, $t3, 1
 or $t0, $t2, $t3

 # interschimba perechi de 2 biti
 # t0 = ((t0 >> 2) & 0x33333333) | ((t0 & 0x33333333) << 2)
 li $t1, 0x33333333
 srl $t2, $t0, 2
 and $t2, $t2, $t1
 and $t3, $t0, $t1
 sll $t3, $t3, 2
 or $t0, $t2, $t3

 # interschimba perechi de 4 biti
 # t0 = ((t0 >> 4) & 0x0f0f0f0f) | ((t0 & 0x0f0f0f0f) << 4)
 li $t1, 0x0f0f0f0f
 srl $t2, $t0, 4
 and $t2, $t2, $t1
 and $t3, $t0, $t1
 sll $t3, $t3, 4
 or $t0, $t2, $t3

 # interschimba perechi de 8 biti
 # t0 = ((t0 >> 8) & 0x00ff00ff) | ((t0 & 0x00ff00ff) << 8)
 li $t1, 0x00ff00ff
 srl $t2, $t0, 8
 and $t2, $t2, $t1
 and $t3, $t0, $t1
 sll $t3, $t3, 8
 or $t0, $t2, $t3

 # interschimba perechi de 16 biti
 # t0 = (t0 >> 16) | (t0 << 16)
 srl $t2, $t0, 16
 sll $t3, $t0, 16
 or $t0, $t2, $t3

 sw $t0, x

 li $v0, 10
 syscall
