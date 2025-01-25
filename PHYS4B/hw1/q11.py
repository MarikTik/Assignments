from globals import *
r = 1.25e-6
p = 925
v = (4/3) * pi * r**3
w = v * p * g
print("w", w)

delta_E = (w) / qe
print(f"delta_E {delta_E:e}")
