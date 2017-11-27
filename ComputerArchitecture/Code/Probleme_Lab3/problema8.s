#III.8) (3 puncte) (*)
# Translatati in MIPS urmatorul program C:
#
#  int aplica(int (*f)(int), int x){
#    return (*f)(x);
#  }
#
#  int f1(int y){return y+y;}
#  int f2(int y){return y*y;}
#  int f3(int y){return -y;}
#
#  int (*vf[])={f1, f2, f3}, v[3];
#
#  void main(){
#    register int i;
#    for(i=0;i<3;++i) v[i]=aplica(vf[i],1+i);
#  }
#
#  /* in final v[0]=2, v[1]=4, v[2]=-3 */

.data
v: .space 12
vf: .space 12

.text

f1:
 # a0 - y, parametrul functiei
 add $v0, $a0, $a0
 jr $ra

f2:
 # a0 - y, parametrul functiei
 mult $a0, $a0
 mflo $v0
 jr $ra

f3:
 # a0 - y, parametrul functiei
 addi $t7, -1
 mult $a0, $t7
 mflo $v0
 jr $ra

aplica:
 # a1 -> adresa functiei la care se sare
 # a0 -> x, parametru numeric

 # salvez adresa de retur pe stiva
 addi $sp, $sp, -4
 sw $ra, 0($sp)

 jalr $ra, $a1
 #returneaza valoarea functiei in $r0

 # scot adresa de retur din stiva
 lw $ra, 0($sp)
 addi $sp, $sp, 4

 jr $ra


main:
 # initializare vector de functii
 la $t0, vf
 la $t1, f1
 sw $t1, 0($t0)
 la $t1, f2
 sw $t1, 4($t0)
 la $t1, f3
 sw $t1, 8($t0)
 # sfarsit initializare vector de functii

 li $s0, 0
 li $s1, 3

 for:
  bge $s0, $s1, end
  li $t0, 4
  mult $t0, $s0
  mflo $t0 # t0 -> offsetul pentru vectori
  la $t1, vf
  add $t1, $t1, $t0 # t1 = vf + i
  lw $t1, 0($t1)
  addi $a1, $t1, 0 # a1 = vf[i]
  addi $a0, $s0, 1
  jal aplica
  la $t1, v
  add $t1, $t1, $t0
  sw $v0, 0($t1)
  addi $s0, $s0, 1
  j for
 end:

 li $v0, 10
 syscall
