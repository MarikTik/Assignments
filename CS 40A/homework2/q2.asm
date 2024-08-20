# Program File: q2.asm
# Author: Mark Tikhonov
# Program to play a middle "C" for 1 second as a reed instrument using the Musical Instrument Digital Interface (MIDI) services

.data
     middle_c: .word 60
     duration: .word 1000 # 1000 milliseconds = 1 second
     instrument: .word 65 # reed instrument
     volume: .word 50
.text
main: 
     # call MIDI service with the given parameters
     li $v0, 31 
     lw $a0, middle_c 
     lw $a1, duration 
     lw $a2, instrument 
     lw $a3, volume 
     syscall

     li $v0, 10
     syscall

# The difference between service 31 and 33 is that service 33 halts the thread while the audio machine reproduces the sound.
# Service 31 on the other hand is not blocking.