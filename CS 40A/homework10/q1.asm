.text
.globl main
main:
	la $a0, array_base
	lw $a1, array_size
	jal print_int_array_reversed
	jal exit

.data
	array_size: .word 5
	array_base:
		.word 12
		.word 7
		.word 3
		.word 5
		.word 11

# Subprogram: print_int_array_reversed
# Author: Mark Tikhonov
# Purpose: print an integer array in reverse order to the console
# Input: $a0 - base address of the array, $a1 - number of elements
# Output: prints the array nicely
# Side effects: none.
.text
print_int_array_reversed:
     start:
          addi $sp, $sp, -12 # Stack record
          sw $ra, 0($sp)
          sw $s0, 4($sp)
          sw $s1, 8($sp)
          # using $s2 is pretty much unnecessary for this subprogram

          # put $s0 to point to the end address of the array
          move $s0, $a1
          sll $s0, $s0, 2
          add $s0, $s0, $a0

          # store the start address of the array in $s1
          move $s1, $a0
          li $s2, 0 # initialize counter
          la $a0, open_bracket
          jal print_string

          # print last element so that the comma separation will be correct.
          addi $s0, $s0, -4 # substruct first to get on the integer address start
          lw $a0, 0($s0)
          jal print_integer
     loop:
          # print comma
          la $a0, comma
          jal print_string


          # print the nth integer of the array
          addi $s0, $s0, -4 
          lw $a0, 0($s0)
          jal print_integer 

          blt $s1, $s0, loop
           
	end_loop:
     	la $a0, close_bracket
     	jal print_string
	
     	lw $ra, 0($sp)
     	lw $s0, 4($sp)
     	lw $s1, 8($sp)
     	addi $sp, $sp, 12
     	jr $ra


.include "utils.asm"