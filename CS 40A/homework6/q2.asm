# File: q2.asm
# Author: Mark Tikhonov
# Program fix to question 2 from homework on Chapter 6

.text
     lui $t0, 0x1001 # <- fix needed here. 1001 != 0x1001 which is the intended start adress of .data frame
     lw $a0, 0($t0)
     li $v0, 1
     syscall
     li $v0, 10
     syscall
.data
     .word 8

# the exception is created because the adress 1001 is an invalid adress to access (hence out of range error).
# The correct adress should be 0x1001 which is the start adress of the .data frame. 