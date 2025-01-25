from globals import *
m=0.00428
L=1.09
theta = 6.12 * pi / 180

q = 2 * L * sin(theta) * sqrt(m * g * tan(theta) / k)
print("q (Mi C)", q * 1e6)