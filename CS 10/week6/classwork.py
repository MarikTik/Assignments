from random import uniform

n = 0
for i in range(int(1e6)):
    x = uniform(0, 1)
    y = uniform(0, 1)
    if y > x:
        n += 1

print(n)