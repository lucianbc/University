.data
v: .word 2, 3, 2, 4
n: .word 4
msg: .asciiz "ok"

.text

extinde:
# salvez adresa de retur
# addi $sp, $sp, -4
# sw $ra, 0($sp)

# incarc argumentele
lw $t0, 0($fp)     # t0 = n
lw $t1, 4($fp)     # t1 = v

li $t2, 4
mult $t0, $t2
mflo $t0           # t0 = offset pentru v
add $t0, $t1, $t0  # t0 = adresa ultimului element

lw $t2, 0($t1)     # t2 = valoarea primului element
addi $t1, $t1, 4

bucla:
 bge $t1, $t0, end
 sw $t2, 0($t1)
 addi $t1, $t1, 4
 j bucla
end:

# restaurez adresa de retur
# lw $ra, 0($sp)
# addi $sp, $sp, 4

jr $ra

main:

# citire argumente din memorie
la $t0, v
lw $t1, n

# li $fp, 1

# incarcare argumente pe stiva
addi $sp, $sp, -12     # fac spatiu pentru 3 word-uri
sw $fp, 8($sp)         # salvez pe stiva valoarea lui fp
sw $t0, 4($sp)         # salvez pe stiva valoarea lui v = 4(fp)
sw $t1, 0($sp)         # salvez pe stiva valoarea lui n = 0(fp)
addi $fp, $sp, 0       # salvez in fp valoarea lui sp

jal extinde

lw $fp, 8($sp)
addi $sp, $sp, 12

# afisare
li $v0, 4
la $a0, msg
syscall

li $v0, 10
syscall
