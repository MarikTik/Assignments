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
