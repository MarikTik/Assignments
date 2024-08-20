# Program File: q1.asm
# Author: Mark Tikhonov
# program to do a bitwise complement (NOT) of an integer number entered by the user. 

.data
     input_prompt: .asciiz "Please enter an ineger:\n"
     output_prompt: .asciiz "The complement of this integer is: "
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

     # compute the complement and store it in $a0
     xori $a0, $t0, 0xffffffff
     # print the complement
     li $v0, 1
     syscall 
     
     # exit
     li $v0, 10
     syscall


 # 10110011
 # 11111111
 # --------
 # 01001100 -> xor 0xffffffff to get the complement for 32-bit integer
