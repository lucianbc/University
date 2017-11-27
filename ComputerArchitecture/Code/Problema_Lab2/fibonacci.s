#Program pentru calcularea celui de-al n-lea termen al sirului lui Fibonacci
#  (t1:=1, t2:=1, tn:=t(n-1)+t(n-2), pt. orice n>=3). Numarul n este dat
#  printr-o variabila declarata cu initializare in program. In plus, pentru
#  calcularea termenilor se vor folosi maxim trei alte variabile x,y,z
#  declarate in program si nu se va folosi stiva. In final valoarea ceruta
#  va fi stocata in z. Variabilele vor fi de tip word.

.data
n: .word 6
z: .space 4

.text
main:

li $t1, 1
li $t2, 1
li $t3, 1

lw $t0, n

ble $t0, 2, sf

li $t4, 2
comp:
addi $t4, $t4, 1
bgt $t4, $t0, sf
add $t3, $t2, $t1
add $t1, $t2, $zero
add $t2, $t3, $zero
j comp

sf:
sw $t3, z
li $v0, 10
syscall
