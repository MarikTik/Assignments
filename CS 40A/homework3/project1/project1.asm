# Program file: project1.asm
# Author: Mark Tikhonov 
# Project 1, accepts 3 inetgers (n, T, P) and ouputs V according to the ideal gas low formula V = n * R * T / P (integer only calculation)

# Note: I believe that this program is intended to work only with 32-bit integers throught it's lifetime, 
#       that is because dividing a 64 bit integer stored as [lo, hi] isn't something I can implement with the current tools
#       (in my opinion at least).

.data
     R: .word 8
     prompt: .asciiz "You are required to input 3 values to calculate V with the ideal gas law formula\n\n"
     request_n_prompt: .asciiz "Enter the value for n:\t"
     request_T_prompt: .asciiz "Enter the value for T:\t"
     request_P_prompt: .asciiz "Enter the value for P:\t"
     response_prompt: .asciiz "V = "

.text 
main:
     # output general prompt
     li $v0, 4
     la $a0, prompt
     syscall

     # request n
     la $a0, request_n_prompt
     syscall

     # store n in $t0
     li $v0, 5
     syscall
     move $t0, $v0

     # request T
     li $v0, 4
     la $a0, request_T_prompt
     syscall

     # store T in $t1
     li $v0, 5
     syscall
     move $t1, $v0

     # request P
     li $v0, 4
     la $a0, request_P_prompt
     syscall

     # store P in $t2
     li $v0, 5
     syscall
     move $t2, $v0

     # output response prompt
     li $v0, 4
     la $a0, response_prompt
     syscall

     # calculate V and store it in $a0
     lw $a0, R
     mulo $a0, $a0, $t0 # exception upon overflow
     mulo $a0, $a0, $t1 # exception upon overflow
     div $a0, $a0, $t2

     # print V
     li $v0, 1
     syscall

     # exit
     li $v0, 10
     syscall