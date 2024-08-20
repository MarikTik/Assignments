.text
largest_and_average:
     # allocate 20 bytes on the stack
     addi $sp, $sp, -20
     
     # store $ra and arguments in $a0-$a3 on the stack
     sw $ra, 0($sp)
     sw $a0, 4($sp)
     sw $a1, 8($sp)
     sw $a2, 12($sp)
     sw $a3, 16($sp)

     # find the largest integer among $a0-$a3 and save it in $v0
     jal get_larger
     move $a0, $v0
     move $a1, $a2
     jal get_larger
     move $a0, $v0
     move $a1, $a3
     jal get_larger # $v0 stores the maximum. I genuinly think that the use of $s0 regiter in the code example is redundant so I avoid it.

     # restore the original values of $a0-$a3 (now there is real use to the stack and the question got it wrong)
     lw $a0, 4($sp)
     lw $a1, 8($sp)
     lw $a2, 12($sp)
     lw $a3, 16($sp)

     # find the average among $a0-$a3 and store it in $v1
     jal average

     # load the return address from the stack and return
     lw $ra, 0($sp)
     jr $ra

# Subprogram: get_larger:
# Author: Mark Tikhonov
# Purpose: returns the largest values between ($a0, $a1).  
# Input/Output: input is the registers ($a0, $a1) and the output is stored in $v0
# Side effects: none
.text
get_larger:
     move $v0, $a0
     bge $a1, $a0, if_bigger
     b end
     if_bigger:
          move $v0, $a1
     end:
          jr $ra


# Subprogram: average:
# Author: Mark Tikhonov
# Purpose: returns the average of the values stored in the registers $a0, $a1, $a2, $a3.  
# Input/Output: input is the registers ($a0, $a1, $a2, $a3) the average is stored in $v1
# Side effects: none
.text
average:
     li $v1, 0
     add $v1, $v1, $a0
     add $v1, $v1, $a1
     add $v1, $v1, $a2
     add $v1, $v1, $a3
     srl $v1, $v1, 2
     jr $ra



# Subprogram: print_charactter
# Author: Mark Tikhonov
# Purpose: output an integer to the console
# Input/Output: expects $a0 to be the ascii value of a character
# Side effects: invalidates the value of $v0 register
.text
print_integer:
     li $v0, 1
     syscall 
     jr $ra


# Subprogram: print_string
# Author: Mark Tikhonov
# Purpose: print a string to the console
# Input: $a0 - The address of the string to print.
# Output: None
# Side effects: The String is printed to the console.
.text
     print_string:
     addi $v0, $zero, 4
     syscall
     jr $ra

# Subprogram: largest_and_average
# Author: Mark Tikhonov
# Purpose: returns the largest of value stored in registers $a(n) for 0 <= n <= 3 and their average.  
# Output: the largest number is in $v0, while the average is in $v1
# Side effects: none

# Subprogram: endl
# Author: Mark Tikhonov
# Purpose: output a new line to console
# Input/Output: None
# Side effects: none
.text
     endl:
     li $v0, 4
     la $a0, new_line
     syscall
     jr $ra

.data
     new_line: .asciiz "\n"


# Subprogram: exit
# Author: Mark Tikhonov
# Purpose: to exit the program
# Input/Output: None
# Side effects: exits the program
.text
exit:
     li $v0, 10,
     syscall
