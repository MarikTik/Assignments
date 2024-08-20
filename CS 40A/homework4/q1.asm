# R format
# opcode | rs     | rt     | rd     |shamt   | funct
# 6 bits | 5 bits | 5 bits | 5 bits | 5 bits | 6 bits

# I format
# opcode | rs     | rt     | immediate
# 6 bits | 5 bits | 5 bits | 16 bits

# $t0 = 8
# $t1 = 9
# $t2 = 10
# $a0 = 4
# $v0 = 2

.text
.globl main
main:
     ori $t0, $zero, 15  # 001101 01000 00000 0000000000001111
     ori $t1, $zero, 3   # 001101 01001 00000 0000000000000011
     add $t1, $zero, $t1 # 000000 00000 01001 01001 00000 100000 
     sub $t2, $t0, $t1   # 000000 01000 01001 01010 00000 100010
     sra $t2, $t2, 2     # 000000 00000 01010 01010 00010 000011
     mult $t0, $t1       # 000000 01000 01001 00000 00000 011000
     mflo $a0            # 000000 00000 00000 00100 00000 010010
     ori $v0, $zero, 1   # 001101 00000 00010 0000000000000001
     syscall             # 0x0000000C
     addi $v0, $zero, 10 # 001000 00000 00010 0000000000001010
     syscall             # 0x0000000C
.data
     result: .asciiz "15 * 3 is "


# so translating it to hex we get
# 0x3408000F
# 0x34090003
# 0x00094820
# 0x01095022
# 0x000A5083
# 0x01090018
# 0x00002012
# 0x34020001
# 0x0000000C
# 0x2002000A
# 0x0000000C