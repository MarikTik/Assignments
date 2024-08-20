# Program file: q5.asm
# Author: Mark Tikhonov
# program that opens an input dialog box and read a string value than write the string back to
# the user using a message box.

.data 
     message: .asciiz "Please enter a string value"
     response: .space 100
     response_size: .word 101

.text
main:
     # prompt user with textbox
     li $v0, 54
     la $a0, message
     la $a1, response
     lw $a2, response_size
     syscall

     # output entered string
     li $v0, 4
     la $a0, response
     syscall

     # exit
     li $v0, 10
     syscall



