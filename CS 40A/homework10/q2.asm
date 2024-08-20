.text:
main:
     la $a0, request_prompt
     jal print_string

     jal read_integer # digit in $v0
     move $t0, $v0 # save in $t0

     # print response string
     la $a0, response_prompt
     jal print_string

     # print the hex represenation of the value in $a0
     move $a0, $t0
     jal print_digit_to_hex

     jal exit

# Subprogram: print_int_array_reversed
# Author: Mark Tikhonov
# Purpose: print the the hex representation of a number
# Input: $a0 - digit to convert to hex. Range: [0, 15]
# Output: hex representation of the digit stored in $a0
# Side effects: doesn't terminate the string, that's up to the user)).
.text:
print_digit_to_hex:
     addi $sp, $sp, -4
     sw $ra, 0($sp)

     move $t0, $a0
     la $a0, hex_prefix
     jal print_string    

     la $t1, hex_digits
     add $t1, $t1, $t0

     lb $a0, 0($t1)
     jal print_character

     lw $ra, 0($sp)
     jr $ra

.data:
     request_prompt: .asciiz "Enter a number from 0 to 15: " 
     response_prompt: .asciiz "your number is "
     hex_prefix: .asciiz "0x"
     hex_digits: .ascii "0123456789abcdef"

.include "utils.asm"