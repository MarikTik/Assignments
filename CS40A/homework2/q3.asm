# Program file: q3.asm
# Author: Mark Tikhonov
# Program to print out a random number from 1...100

.data
     random_max: .word 100
     generator: .word 5122 # chosen randomly by myself

.text
main: 
     # generate a random number and store it in $a0
     li $v0, 42
     lw $a0, generator
     lw $a1, random_max
     syscall

     # pring integer stored in $a0
     li $v0, 1 
     syscall

     # exit
     li $v0, 10
     syscall