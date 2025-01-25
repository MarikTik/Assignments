from globals import *
delta = 4.5e-6
a = 0.35
Ex = -k * delta / a
print(f"Ex {Ex / 1e3}")

print("Ey", -Ex / 1e3)