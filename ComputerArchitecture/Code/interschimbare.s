# interschimbarea a doua numere
.data
  x:.byte 17
  y:.byte 93
.text
main:
  lb $t0,x
  lb $t1,y
  sb $t0,y
  sb $t1,x
li $v0,10
syscall
