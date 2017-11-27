.data
n: .word 7
z: .space 4

.text
main:

li $t0, 1
addi $sp, $sp, -4
sw $t0, 0($sp)

addi $sp, $sp, -4
sw $t0, 0($sp)

li $t0, 2
lw $t1, n
cat_timp:
bge $t0, $t1, def


def:
#salvez varful stivei in n
