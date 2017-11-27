# III.20) (8 puncte)
#  Program pentru sortarea unui vector de word (declarat cu initializare in
# program) prin metoda Qsort, folosind o procedura recursiva; interactiunea
# dintre procedura si program se va face doar prin parametri/valoare returnata
# (nu prin variabile globale).

.data
v: .word 9, 8, 7, 6, 5, 4, 3, 2, 1
n: .word 9

.text

# a0 -> adresa spre vector
# a1 -> limita din stanga
# a2 -> limita din dreapta
part:
 # salvez argumentele pe stiva
 addi $sp, $sp, -4
 sw $a0, 0($sp)
 addi $sp, $sp, -4
 sw $a1, 0($sp)
 addi $sp, $sp, -4
 sw $a2, 0($sp)

 addi $sp, $sp, -4   # aloc memorie in stiva pentru pivot

 sub $t0, $a2, $a1   # $t0 = $a2 - $a1 = r - l

 li $t1, 2
 div $t0, $t1        # $t0 = $t0 / 2 = (r - l) / 2
 mflo $t0

 add $t0, $t0, $a1   # $t0 = $t0 + $a1 = (r - l) / 2 + l

 li $t1, 4
 mult $t1, $t0
 mflo $t0            # ofsetez indicele
 add $t1, $a0, $t0   # $t1 = v + p

 lw $t0, 0($t1)
 sw $t0, 0($sp)      # salvez valoarea pivotului in stiva

 cautare:
  bgt $a1, $a2, ret
  avansare_stanga:
   li $t0, 4
   mult $a1, $t0
   mflo $t0
   add $t0, $t0, $a0
   lw $t0, 0($t0)         # t0 = a[l]
   lw $t1, 0($sp)         # t1 = piv
   bge $t0, $t1, term_stanga
   addi $a1, $a1, 1
   j avansare_stanga
  term_stanga:
  avansare_dreapta:
   li $t0, 4
   mult $a2, $t0
   mflo $t0
   add $t0, $t0, $a0
   lw $t0, 0($t0)        # t0 = a[r]
   lw $t1, 0($sp)        # t1 = piv
   ble $t0, $t1, term_dreapta
   addi $a2, $a2, -1
   j avansare_dreapta
  term_dreapta:
   bgt $a1, $a2, not_int
   # interschimb valorile de la a1 si a2
   li $t0, 4
   mult $a1, $t0
   mflo $t0
   add $t0, $a0, $t0      # $t0 = v + a1
   li $t1, 4
   mult $a2, $t1
   mflo $t1
   add $t1, $a0, $t1      # $t1 = v + a2
   lw $t5, 0($t0)         # $t5 = v[a1]
   lw $t6, 0($t1)         # $t6 = v[a2]
   sw $t5, 0($t1)         # v[a1] = $t6
   sw $t6, 0($t0)         # v[a2] = $t5
   addi $a1, $a1, 1       # l++
   addi $a2, $a2, -1      # r--
  not_int:
   j cautare
 ret:
  addi $sp, $sp, 4
  addi $v0, $a1, 0   # returnez pozitia pivotului
  # scot argumentele din stiva
  lw $a2, 0($sp)
  addi $sp, $sp, 4
  lw $a1, 0($sp)
  addi $sp, $sp, 4
  lw $a0, 0($sp)
  addi $sp, $sp, 4
  jr $ra

# a0 -> adresa spre vector
# a1 -> limita din stanga
# a2 -> limita din dreapta
sort:
 # salvez argumentele pe stiva
 addi $sp, $sp, -4
 sw $a0, 0($sp)
 addi $sp, $sp, -4
 sw $a1, 0($sp)
 addi $sp, $sp, -4
 sw $a2, 0($sp)
 addi $sp, $sp, -4
 sw $ra, 0($sp)
 addi $sp, $sp, -4
 sw $s0, 0($sp)

 jal part
 addi $s0, $v0, 0    # $s0 = piv

 bge $s0, $a2, not_sort_2
  addi $a1, $s0, 0
  jal sort
 not_sort_2:

 addi $s0, $s0, -1
 bge $a0, $s0, not_sort_1
  addi $a2, $s0, 0
  jal sort
 not_sort_1:

 # scot argumentele din stiva
 lw $s0, 0($sp)
 addi $sp, $sp, 4
 lw $ra, 0($sp)
 addi $sp, $sp, 4
 lw $a2, 0($sp)
 addi $sp, $sp, 4
 lw $a1, 0($sp)
 addi $sp, $sp, 4
 lw $a0, 0($sp)
 addi $sp, $sp, 4

 jr $ra

main:
 la $a0, v
 li $a1, 0
 lw $a2, n
 addi $a2, $a2, -1

 jal sort

 li $v0, 10
 syscall
