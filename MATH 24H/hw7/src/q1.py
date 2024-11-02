from math import pi, acos
g = 9.81
w = g ** 0.5

c1 = pi/6
c2 = -pi/(12 * 12)

A = (c1 + c2) ** 0.5
print(A)
fi = acos(c1 / A)
print (fi)

T = 2 * pi * (1/g) ** 0.5
print(T)