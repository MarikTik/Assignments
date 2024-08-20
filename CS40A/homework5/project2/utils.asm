# File:	utils.asm
# Purpose:	To define utilities which will be used in MIPS programs.
# Author:	Charles Kann & Mark Tikhonov
# 
# Title to and ownership of all intellectual property rights 
# in this file are the exclusive property of Charles W. Kann.
#
# Subprograms Index:
#   Exit 		Call syscall with a server 10 to exit the program
#   PrintNewLine	Print a new line character (\n) to the console
#   PrintInt	Print a string with an integer to the console
#   PrintString	Print a string to the console
#   PromptInt	Prompt for an int & return it to the calling program.
#
# Modification History
#     12/27/2014 - Initial release

# Subprogram:	Exit
# Author:  		Charles Kann
# Purpose:		to use syscall service 10 to exit a program
# Input/Output:	None
# Side effects:	The program is exited

.text
Exit:
    li $v0, 10
    syscall

# Subprogram:	PrintNewLine
# Author:  		Charles Kann
# Purpose:		to output a new line to the user console
# Input/Output:	None
# Side effects:	A new line character is printed to the user's console

.text
PrintNewLine:
    li $v0, 4
    la $a0, __PNL_newline
    syscall 
    jr $ra

.data
   __PNL_newline:   .asciiz "\n"


# Subprogram: 	PrintInt
# Author:		Charles W. Kann
# Purpose:		To print a string to the console
# Input:		$a0 - The address of the string to print.
#			$a1 - The value of the int to print
# Output:		None
# Side effects:	The String is printed followed by the integer value.

.text
PrintInt: 
    # Print string.  The string address is already in $a0
    li $v0, 4
    syscall
    
    # Print integer.   The integer value is in $a1, and must
    # be first moved to $a0.
    move $a0, $a1
    li $v0, 1
    syscall
    
    #Return
    jr $ra

# Subprogram: 	PrintString
# Author:		Charles W. Kann
# Purpose:		To print a string to the console
# Input:		$a0 - The address of the string to print.
# Output:		None
# Side effects:	The String is printed to the console.

.text
PrintString: 
    addi $v0, $zero, 4
    syscall
    jr $ra

# Subprogram: 	PromptInt
# Author:		Charles W. Kann
# Purpose:		To prompt the user for an integer input, and
#               	to return that input value to the caller.
# Input:		$a0 - The address of the string to print.
# Output:		$v0 - The value the user entered
# Side effects:	The String is printed followed by the integer value.

.text
PromptInt: 
    # Print the prompt, which is already in $a0
    li $v0, 4
    syscall
    
    # Read the integer.  Note: at the end of the syscall the value is
    # already in $v0, so there is no need to move it anywhere.
    li $v0, 5
    syscall
    
    #Return
    jr $ra


#    ###########################

#    NOR - take two input parameters and return the NOR operation on those two parameters
#    NAND - take two input parameters and return the NAND operation on those two parameters
#    Mult4 - take an input parameter and return that parameter multiplied by 4 using only the shift operation.
#    Swap - take two input parameters and swap them using only the XOR and MOVE operations. 

#    Notes:  assume your subprograms already have arguments in the 'a' register(s) ($a0...$a3) and should store output(s) in the 'v' register(s) ($v0, $v1).



# Subprogram: 	 NOR
# Author:		 Mark Tikhonov
# Purpose:      to compute the nor value of 2 numbers and return it
# Input:		 ($a0, $a1) - The addresses of the arguments
# Output:		 $v0 - address that stores the operation result
# Side effects: none
.text 
NOR:
     nor $v0, $a0, $a1
     jr $ra

# Subprogram: 	 NAND
# Author:		 Mark Tikhonov
# Purpose:      to compute the NAND value of 2 numbers and return it
# Input:		 ($a0, $a1) - The addresses of the arguments
# Output:		 $v0 - address that stores the operation result
# Side effects: none
.text 
NAND:
     and $v0, $a0, $a1
     nor $v0, $v0, $v0
     jr $ra

# Subprogram: 	 MULT4
# Author:		 Mark Tikhonov
# Purpose:      to multiply a number by 4 by bit shifting
# Input:		 ($a0) - The address of the argument
# Output:		 $v0 - address that stores the operation result
# Side effects: none
.text
MULT4:
     sll $v0, $a0, 2
     jr $ra


# Subprogram: 	 Swap
# Author:		 Mark Tikhonov
# Purpose:      to swap two numbers 
# Input:		 ($a0, $a1) - The addresses of the arguments
# Output:		 $v0, $v1 - addresses that store the operation result
# Side effects: none
.text
Swap:
     # the algorithm is easy to see using a truth table
     # | p | q | p xor q | q xor (p xor q) => q| p xor (q xor (p xor q)) => p|
     # | 0 | 0 |    0    |          0          |               0             |
     # | 0 | 1 |    1    |          0          |               1             |
     # | 1 | 0 |    1    |          1          |               0             |
     # | 1 | 1 |    0    |          1          |               1             |
     # which guarantees that it will swap the values for any two variables p and q (in this case $a0 and $a1)
     
     xor $a0, $a0, $a1 # $a0 stores the intermediate value
     xor $a1, $a0, $a1 # $a1 stores the initial value of $a0
     xor $a0, $a1, $a0 # a0 stores the initial value of $a1

     move $v0, $a0
     move $v1, $a1
     jr $ra
  