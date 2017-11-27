# II.5) (1 punct daca a fost facuta problema II.4 sau 4 puncte altfel)  (*)
#  Program care verifica daca un numar natural este prim. Numarul este citit
#   interactiv de la consola sub forma:
#     Dati numarul: 5
#   iar rezultatul este afisat la consola sub forma:
#     Numarul 5 este prim.
#   La citire 5 este ce tastam noi; la afisare in loc de 5 se va afisa numarul
#   citit; daca nu e prim mesajul se va termina "... nu e prim".

.data
n: .space 4
i: .space 4
x: .space 1

msg: .asciiz "Dati numarul: "

.text
main:
#initializare
#li $t0, 13
#sw $t0, n
li $t0, 2
sw $t0, i
li $t0, 1
sb $t0, x
#sfarsit initializare

#citire n
li $v0, 4
la $a0, msg
syscall

li $v0, 5
syscall
sw $v0, n

cat_timp:
 lw $t0, n
 li $t1, 2
 div $t0, $t1
 mflo $t0
 lw $t1, i
 bgt $t1, $t0, end
  lw $t0, n
  div $t0, $t1
  mfhi $t0
  addi $t1, $t1, 1
  sw $t1, i
  bne $t0, $zero, cat_timp
  li $t0, 0
  sb $t0, x
end:
 li $t0, 0

 li $t1, 'N'
 sb $t1, msg($t0)
 addi $t0, $t0, 1

 li $t1, 'u'
 sb $t1, msg($t0)
 addi $t0, $t0, 1

 li $t1, 'm'
 sb $t1, msg($t0)
 addi $t0, $t0, 1

 li $t1, 'a'
 sb $t1, msg($t0)
 addi $t0, $t0, 1

 li $t1, 'r'
 sb $t1, msg($t0)
 addi $t0, $t0, 1

 li $t1, 'u'
 sb $t1, msg($t0)
 addi $t0, $t0, 1

 li $t1, 'l'
 sb $t1, msg($t0)
 addi $t0, $t0, 1

 li $t1, ' '
 sb $t1, msg($t0)
 addi $t0, $t0, 1

 li $t1, 0
 sb $t1, msg($t0)
 addi $t0, $t0, 1

 sb $t0, i

 li $v0, 4
 la $a0, msg
 syscall

 li $v0, 1
 lw $a0, n
 syscall

 li $t0, 0
 li $t1, ' '
 sb $t1, msg($t0)
 addi $t0, $t0, 1

 lb $t1, x
 bne $t1, $zero, cont
 li $t1, 'n'
 sb $t1, msg($t0)
 addi $t0, $t0, 1
 li $t1, 'u'
 sb $t1, msg($t0)
 addi $t0, $t0, 1
 li $t1, ' '
 sb $t1, msg($t0)
 addi $t0, $t0, 1

 cont:
 li $t1, 'e'
 sb $t1, msg($t0)
 addi $t0, $t0, 1

 li $t1, 's'
 sb $t1, msg($t0)
 addi $t0, $t0, 1

 li $t1, 't'
 sb $t1, msg($t0)
 addi $t0, $t0, 1

 li $t1, 'e'
 sb $t1, msg($t0)
 addi $t0, $t0, 1

 li $t1, ' '
 sb $t1, msg($t0)
 addi $t0, $t0, 1

 li $t1, 'p'
 sb $t1, msg($t0)
 addi $t0, $t0, 1

 li $t1, 'r'
 sb $t1, msg($t0)
 addi $t0, $t0, 1

 li $t1, 'i'
 sb $t1, msg($t0)
 addi $t0, $t0, 1

 li $t1, 'm'
 sb $t1, msg($t0)
 addi $t0, $t0, 1

 li $t1, '.'
 sb $t1, msg($t0)
 addi $t0, $t0, 1

 li $t1, 0
 sb $t1, msg($t0)
 addi $t0, $t0, 1

 li $v0, 4
 la $a0, msg
 syscall


 li $v0, 10
 syscall
