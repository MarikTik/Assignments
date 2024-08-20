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

# Subprogram: endl
# Author: Mark Tikhonov
# Purpose: output a new line to console
# Input/Output: None
# Side effects: none


# Subprogram: read_integer
# Author: Mark Tikhonov
# Purpose: prompt the user for an integer (verbose prompt is an option), and
# to return that input value to the caller.
# Input: $a0 - The address of the prompt string to print or no prompt at all.
# Output: $v0 - The value the user entered
# Side effects: The String is printed followed by the integer value.
.text
read_integer:
     addi $sp, $sp, -4
     sw $ra, 0($sp)
     # fix on the textbook implementation of read_integer which assumes that the value in $a0 is a prompt address which might not be the case
     
     lw $t0, data_segment_address_start
     lw $t1, data_segment_address_end
     addi $t1, $t1, -4
     
     sge $t2, $a0, $t0
     sle $t3, $a0, $t1
     and $t4, $t2, $t3

     beqz $t4, finally
     if_prompt: # print prompt if $a0 value is an address on .data segment frame
          jal print_string

     finally: # read int to $v0
          li $v0, 5
          syscall
     
     lw $ra, 0($sp)
     addi $sp, $sp, 4
     jr $ra


.data:
     data_segment_address_start: .word 0x10010000
     data_segment_address_end: .word 0x10040000
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
