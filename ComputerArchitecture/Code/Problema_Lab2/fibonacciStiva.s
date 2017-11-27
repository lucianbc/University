#Pentru calcularea termenilor fibonacci se va folosi stiva. In program vor fi declarate doar variabilele n (cu initializare) si z. Variabila n va fi folosita doar pentru a da si eventual numara iteratiile iar variabila z doar pentru a pune in ea la sfarsit termenul cerut (toti termenii intermediari vor fi stocati in stiva).

.data
n: .space 4
z: .space 4

.text

fib:
addi $sp, $sp, -4
sw $ra, 0($sp)
li $t0, 2
ble $a0, $t0, base
addi $sp, $sp, -4
sw $a0, 0($sp)
addi $a0, $a0, -1
jal fib
lw $a0, 0($sp)
addi $sp, $sp, -4
sw $v0, 0($sp)
addi $a0, $a0, -2
jal fib
lw $t0, 0($sp) #scot din stiva valoarea apelului anterior
addi $sp, $sp, 4
add $v0, $v0, $t0
addi $sp, $sp, 4
j ret
base:
li $v0, 1
ret:
lw $ra, 0($sp)
addi $sp, $sp, 4
jr $ra

main:
#initializare
li $t0, 7
sw $t0, n
#sfarsit initializare

lw $a0, n
jal fib

sw $v0, z

li $v0, 10
syscall
