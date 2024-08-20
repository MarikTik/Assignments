# File: utils.asm
# Purpose: To define utilities which will be used in MIPS programs.
# Author: Charles Kann
#
# Title to and ownership of all intellectual property rights
# in this file are the exclusive property of Charles W. Kann.
#
# Subprograms Index:
# Exit Call syscall with a server 10 to exit the program
# PrintNewLine Print a new line character (\n) to the console
# PrintInt Print a string with an integer to the console
# PrintString Print a string to the console
# PromptInt Prompt for an int & return it to the calling program.
#
# Modification History
# 12/27/2014 - Initial release
# Subprogram: Exit
# Author: Charles Kann
# Purpose: to use syscall service 10 to exit a program
# Input/Output: None
# Side effects: The program is exited

.text
Exit:
     li $v0, 10
     syscall

# Subprogram: PrintNewLine
# Author: Charles Kann
# Purpose: to output a new line to the user console
# Input/Output: None
# Side effects: A new line character is printed to the user's console
.text
     PrintNewLine:
     li $v0, 4
     la $a0, __PNL_newline
     syscall
     jr $ra


# Subprogram: PrintInt
# Author: Charles W. Kann
# Purpose: To print a string to the console
# Input: $a0 - The address of the string to print.
# $a1 - The value of the int to print
# Output: None
# Side effects: The String is printed followed by the integer value.
# .text
#      PrintInt:
#      # Print string. The string address is already in $a0
#      li $v0, 4
#      syscall
#      # Print integer. The integer value is in $a1, and must
#      # be first moved to $a0.
#      move $a0, $a1
#      li $v0, 1
#      syscall
#      # Return
#      jr $ra


# Subprogram: PrintString
# Author: Charles W. Kann
# Purpose: To print a string to the console
# Input: $a0 - The address of the string to print.
# Output: None
# Side effects: The String is printed to the console.
.text
     PrintString:
     addi $v0, $zero, 4
     syscall
     jr $ra

# Subprogram: PromptInt
# Author: Charles W. Kann
# Purpose: To prompt the user for an integer, and
# to return that input value to the caller.
# Input: $a0 - The address of the string to print.
# Output: $v0 - The value the user entered
# Side effects: The String is printed followed by the integer value.
.text
     PromptInt:
     # Print the prompt, which is already in $a0
     li $v0, 4
     syscall
     # Read the integer. Note: at the end of the syscall the value is
     # already in $v0, so there is no need to move it anywhere.
     move $a0, $a1
     li $v0, 5
     syscall
     #Return
     jr $ra


.data
     __PNL_newline: .asciiz "\n"