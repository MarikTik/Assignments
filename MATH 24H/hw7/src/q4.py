from math import pi, atan

def part_a():
     for k in range(4):
          print((atan(2) + pi * k) / 10)

def part_b():
     c1 = 1
     c2 = -4 / (99 ** 0.5)
     for k in range(4):
          print((atan(-c1 / c2) + pi * k) / (99 ** 0.5))

def part_c():
     c1 = 1
     c2 = -4 / (99 ** 0.5)
     for k in range(4):
          print((atan(-c1 / c2) + pi * k) / (99 ** 0.5) - (atan(2) + pi * k) / 10)

part_a()
print("\n")
part_b()
print("\n")
part_c()

