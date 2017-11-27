.data
v: .word 2, 3, 2, 4
n: .word 4
msg: .asciiz "ok"

.text

extinde:
addi $sp, $sp, -4
sw $fp, 0($sp)

addi $fp, $sp, 0

lw $t0, 4($fp)
lw $t1, 8($fp)

li $t2, 4
mult $t0, $t2
mflo $t0

li $t3, 0

bucla:
 bge $t3, $t0, end
 add $t4, $t1, $t3
 lw $t5, 0($t1)
 sw $t5, 0($t4)
 addi $t3, $t3, 4
 j bucla
end:

lw $fp, 0($sp)
addi $sp, $sp, 4

jr $ra

main:
la $t0, v
lw $t1, n

addi $sp, $sp, -8
sw $t0, 4($sp)
sw $t1, 0($sp)

jal extinde

addi $sp, $sp, 8

li $v0, 4
la $a0, msg
syscall

li $v0, 10
syscall
