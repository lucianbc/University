.data
x: .word 1
y: .word 2
.text

main:
z: .word 3
t: .word 4

lw $t0, z
lw $t1, t

li $v0, 10
syscall
