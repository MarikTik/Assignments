from globals import *
q = 1.75e-6
Ncu=46 * (1/63.546) * 6.02 * 10**23
Np = Ncu * 29
print("Np", Np)
dNe = q / e
print(f"fraction {dNe/Np:e}")
# nn = 34

# m = 0.046 
# q = 1.75e-6

# mh = mp + 34/29 * mn

# b = (m - q * mh) / (e * (mh + me))
# print("b", b)