.text
main: 
     # print maximum string
     la $a0, maximum_string
     jal print_string

     # store required values in argument registers
     li $a0, 2
     li $a1, 5
     li $a2, 8
     li $a3, 11

     # print maximum
     jal largest_and_average
     move $a0, $v0
     jal print_integer
     

     # new line
     jal endl

     # print average string
     la $a0, average_string
     jal print_string

     # print average
     move $a0, $v1
     jal print_integer

     # exit
     jal exit
.data
     maximum_string: .asciiz "Maximum = "
     average_string: .asciiz "Average = "


.include "utils.asm"