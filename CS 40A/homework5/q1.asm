# File: q1.asm
# Author: Mark Tikhonv
# Purpose: Illustrates a fix for the bug in the PromptInt subprogram



.text
main:
     # Read an input value from the user
     la $a0, prompt
     jal PromptInt
     move $s0, $v0
     # Print the value back to the user
     jal PrintNewLine
     la $a0, result
     move $a1, $s0
     jal PrintInt
     # Call the Exit subprogram to exit
     jal Exit

.data
     prompt: .asciiz "Please enter an integer: "
     result: .asciiz "You entered: "

# Subprogram implementation that leads to an infinite loop when called
.text
PrintIntBad:
     # Print string. The string address is already in $a0
     li $v0, 4
     syscall
     # Print integer. The integer value is in $a1, and must
     # be first moved to $a0.
     move $a0, $a1
     li $v0, 1
     syscall
     # Print a new line character
     jal PrintNewLine
     # Return
     jr $ra

# it is easy to see that the problem is that the problem is that after calling PrintNewLine
# the initial address location of $ra is lost. To fix it I will just save that initial address in another register and use it as 
# an indicator for the program to jump to

# Subprogram custom fix implementation that avoids the infinite loop
.text
PrintInt:
     # Print string. The string address is already in $a0
     li $v0, 4
     syscall
     # Print integer. The integer value is in $a1, and must
     # be first moved to $a0.
     move $a0, $a1
     li $v0, 1
     syscall
     # save the initial value of $ra to $t0
     move $t0, $ra
     # Print a new line character
     jal PrintNewLine
     # return the initial value of $ra back to the register
     # Return
     jr $t0

.include "utils.asm"