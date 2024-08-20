# Program file: q3.asm
# Author: Mark Tikhonov
# Program that sleeps 4 seconds before exiting

.data
     sleep_time: .word 4000 # 4000 milliseconds = 4 seconds

.text
main:
     # sleep for the given amount of time
     li $v0, 32
     lw $a0, sleep_time
     syscall

     # exit
     li $v0, 10
     syscall

