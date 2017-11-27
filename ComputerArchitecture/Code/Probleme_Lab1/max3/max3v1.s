.data
 x: .word 3
 y: .word 1
 z: .word 2
 max: .space 4
.text
comp1:
 blt $t1,$t0,change1
 j ret1
change1:
#interschimbare x($t0), y($t1)
 add $t0,$t0,$t1
 sub $t1,$t0,$t1
 sub $t0,$t0,$t1
 j ret1
comp2:
 blt $t1,$t0,change2
 j ret2
change2:
 add $t0,$t0,$t1
 sub $t1,$t0,$t1
 sub $t0,$t0,$t1
 j ret2
main:
 lw $t0,x
 lw $t1,y
 j comp1
ret1:
 lw $t0,z
 j comp2
ret2:
 sw $t1,max
 li $v0,10
 syscall