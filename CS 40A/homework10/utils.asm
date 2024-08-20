# .text
# print_int_array:
#      addi $sp, $sp, -16 # Stack record
#      sw $ra, 0($sp)
#      sw $s0, 4($sp)
#      sw $s1, 8($sp)
#      sw $s2, 12($sp)
#      move $s0, $a0 # save the base of the array to $s0
#      # Initialization for counter loop
#      # $s1 is the ending index of the loop
#      # $s2 is the loop counter
#      move $s1, $a1
#      move $s2, $zero
#      la $a0, open_bracket # print open bracket
#      jal print_string
#      lw $a0, 0($s0)
#      jal print_integer
#      addi $s2, $s2, 1
# 
#      loop:
#           # check ending condition
#           sge $t0, $s2, $s1
#           bnez $t0, end_loop
#           sll $t0, $s2, 2   
# 
#           # print comma
#           la $a0, comma
#           jal print_string # print the integer from array
# 
#           # print i-th element of the array
#           add $t0, $t0, $s0 # address of next array element
#           lw $a0, 0($t0) # Next array element
#           jal print_integer
# 
#           # increment array counter and repeat
#           addi $s2, $s2, 1
#           b loop
# end_loop:
#      li $v0, 4 # print close bracket
#      la $a0, close_bracket
#      syscall
# 
#      lw $ra, 0($sp)
#      lw $s0, 4($sp)
#      lw $s1, 8($sp)
#      lw $s2, 12($sp) # restore stack and return
#      addi $sp, $sp, 16
#      jr $ra
.data
     open_bracket: .asciiz "["
     close_bracket: .asciiz "]"
     comma: .asciiz ","


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
     li $v0, 4
     syscall
     jr $ra

 
.text 
read_integer:
     li $v0, 5
     syscall
     jr $ra

# Subprogram: print_charactter
# Author: Mark Tikhonov
# Purpose: output a character to the console
# Input/Output: expects $a0 to be the ascii value of a character
# Side effects: invalidates the value of $v0 register
.text
print_character:
     li $v0, 11
     syscall 
     jr $ra


# Subprogram: exit
# Author: Mark Tikhonov
# Purpose: to exit the program
# Input/Output: None
# Side effects: exits the program
.text
exit:
     li $v0, 10,
     syscall
