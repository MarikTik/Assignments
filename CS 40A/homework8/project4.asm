# Filename: project4.asm
# Author: Mark Tikhonov
# Date: 6/21/2024
# Purpose: print every other charracter in the sequence [A, B, C, ..., Y, Z] starting at A.

.text
     # load the ascii values of (A, Z) to registers $a0, $t0
     lb $a0, range_start
     lb $t0, range_end

     # print character located in $a0. Add +2 to its ascii value. Repeat while the character is less then 'Z'
loop:
     jal print_character
     addi $a0, $a0, 2
     ble $a0, $t0, loop
     
     
     # exit the program
     jal exit

     
.data
     range_start: .ascii "A" 
     range_end:   .ascii "Z"

.include "utils.asm"