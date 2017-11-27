# Program care cauta un numar x intr-un vector de numere si pune in y
# valoarea 1/0 dupa cum x apare/nu apare in vector.
.data
v: .word 1, 2, 3, 4, 5, 6
n: .word 6
x: .space 4
y: .byte -1
.text
main:
# initializare
 li $t0, 3
 sw $t0, x
# sfarsit initializare

 li $t0, 0
 lw $t7, n
 lw $t6, x
cat_timp:
 bge $t0,$t7,end

 #t1 -> offset pentru vector
 li $t1,4
 mult $t1,$t0
 mflo $t1

 addi $t0,$t0,1

 lw $t2,v($t1)
 bne $t2,$t6,cat_timp
 li $t3,1
 sb $t3,y
 j exit
end:
 li $t3,0
 sb $t3,y
exit:
 li $v0,10
 syscall
