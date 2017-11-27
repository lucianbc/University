.data
x: .word 0x7053
.text

suma:
 addi $sp, $sp, -4
 sw $fp, 0($sp)
 add $fp, $sp, $zero
 lw $t0, 8($fp)

 li $t1, 0xf
 li $t2, 0

 bucla:
  ble $t0, $zero, end
  and $t3, $t0, $t1
  add $t2, $t2, $t3
  srl $t0, $t0, 4
  j bucla
 end:
  sw $t2, 4($fp)

 lw $fp, 0($sp)
 addi $sp, $sp, 4
 jr $ra

main:
 lw $t0, x
 addi $sp, $sp, -8
 sw $t0, 4($sp)
 jal suma
 lw $a0, 0($sp)
 addi $sp, $sp, 8

 li $v0, 1
 syscall

 li $v0, 10
 syscall
