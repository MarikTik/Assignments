# Program File: q1.asm
# Author: Mark Tikhonov
# Outputs prompt, reads user response, combines the response with predetermined strings and outputs it to the console.

.data
     prompt: .asciiz "Enter your favorite type of pie:\n"
     output_fragment_1: .asciiz "So you like "
     output_fragment_2: .asciiz "pie" 
     input: .space 41
     input_size: .word 40
.text
main:
     # output prompt
     li $v0, 4
     la $a0, prompt
     syscall

     # read user response
     li $v0, 8
     la $a0, input
     lw $a1, input_size
     syscall

     # output program response
     li $v0, 4
     la $a0, output_fragment_1
     syscall
     la $a0, input
     syscall
     la $a0, output_fragment_2
     syscall

     # Exit the program
     li $v0, 10
     syscall

# The "annoying feature" is that the 'read user response' block stiks a newline character at the end of the user input.




 