# sortare prin selectie cu doi registrii
# compara/interschimba (x,y), (x,z), (y,z)
.data
 x: .word 3
 y: .word 1
 z: .word 2
.text
main:
 lw $t0,x
 lw $t1,y
 ble $t0,$t1,comp2
 sw $t1,x
 sw $t0,y
comp2:
 lw $t0,x
 lw $t1,z
 ble $t0,$t1,comp3
 sw $t0,z
 sw $t1,x
comp3:
 lw $t0,y
 lw $t1,z
 ble $t0,$t1,sf
 sw $t0,z
 sw $t1,y
sf:
 li $v0,10
 syscall