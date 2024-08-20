.text
main:
     # prompt for a number
     la $a0, prompt_request
     jal read_integer

     # save n to $a0 and $s0
     move $a0, $v0
     move $s0, $v0

     # call the procedure to sum up all the numbers in range [1, $a0] 
     # li $a1, 0
     li $v0, 0
     jal sum_first_n

     # save the sum in $v0 to $s1
     move $s1, $v0 

     # begin response prompt
     la $a0, prompt_response_section1
     jal print_string

     # add range end (n) to response prompt
     move $a0, $s0
     jal print_integer
     la $a0, prompt_response_section2
     jal print_string

     # show the result
     move $a0, $s1
     jal print_integer

     # exit 
     jal exit

# Subprogram: sum_first_n
# Author: Mark Tikhonov
# Purpose: sums all numbers in range [1,n] where n is a positive integer stored in $a0
# Input: $a0 - The value of n, $v0 SHOULD BE SET TO 0
# Output: stores the result in $v0
# Side effects: changes the value in $a0 to 0.
.text
sum_first_n:
     addi $sp, $sp, -4         # adjust stack pointer to allocate space
     sw $ra, 0($sp)            

     add $v0, $v0, $a0          
     addi $a0, $a0, -1         
     beqz $a0, finish          # if $a0 is zero, finish
     jal sum_first_n

     finish:
          lw $ra, 0($sp)            # restore return address
          addi $sp, $sp, 4          # adjust stack pointer
          jr $ra                    

.data 
prompt_request: .asciiz "Enter a number: "
prompt_response_section1: .asciiz "\nThe sum of the numbers from 1 to "
prompt_response_section2: .asciiz " is "


.include "utils.asm"