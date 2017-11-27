.data
 x: .word 3
 y: .word 1
 z: .word 5
 r: .space 4
.text
main:
 lw $t0,x
 lw $t1,y
 lw $t2,z
 blt $t0,$t1,compYZ
 blt $t0,$t2,afZ
 sw $t0,r
 j sfarsit
afZ:
 sw $t2,r
 j sfarsit
compYZ:
 blt $t1,$t2,afZ
sw $t1,r
sfarsit:
 li $v0,10
 syscall