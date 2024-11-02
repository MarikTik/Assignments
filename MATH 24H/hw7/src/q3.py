from math import pi, log

W = 3200
g = 32.2
m = W / g

def part_a():
     T = 3/4
     k = (2 * pi / T) ** 2 * m
     print("k = ", k)


def part_b():
     w_n = 8/3 * pi
     w_d = 39/15 * pi
     b = 2 * m * (w_n ** 2 - w_d ** 2) ** 0.5
     delta = b/(2 * m)
     t = log(100) / delta 
     print ("t = ", t)

part_b()

 