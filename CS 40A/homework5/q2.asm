# Subprogram: PrintNewLine
# Author: Charles Kann
# Purpose: to output a new line to the user console
# Input/Output: None
# Side effects: A new line char is printed to the console
.text
PrintNewLine:
     li $v0, 4
     la $a0, __PNL_newline
     syscall
     jr $ra
.data
     __PNL_newline: .asciiz "\n"

.text # <- not inserted in the example which is a mistake, otherwise it is unclear to which memory segment does the subprogram belong
PrintTab:
li $v0, 4
la $a0, tab
syscall
jr $ra

.data
     tab: .asciiz "\t"

# it is very hard to understand what went wrong in a program that is intentionally incorrect, if the intention was to leave
# the subprogram PrintTab accessible but at the same time to have it automatically inserted in every call to PrintNewLine
# than that call should have referenced PrintTab as follows:

.text
PrintNewLine:
     li $v0, 4
     la $a0, __PNL_newline
     syscall
     move $t0, $ra
     jal PrintTab
     jr $t0

# 