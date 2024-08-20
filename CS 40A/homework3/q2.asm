# Program File: q1.asm
# Author: Mark Tikhonov
# Program that calculates the 2's complement of a number entered by the user

.data
     input_prompt: .asciiz "Please enter an ineger:\n"
     output_prompt: .asciiz "The 2's complement of this integer is: "
.text
main:
     # show input prompt
     li $v0, 4
     la $a0, input_prompt
     syscall

     # read an integer and store it in $t0
     li $v0, 5
     syscall
     move $t0, $v0

     # show output prompt
     li $v0, 4
     la $a0, output_prompt
     syscall

     # compute 2's the complement and store it in $a0
     xori $a0, $t0, 0xffffffff
     addi $a0, $a0, 1

     # print the 2's complement
     li $v0, 1
     syscall 
     
     # exit
     li $v0, 10
     syscall


 