sum_rec = lambda n: 1 if n == 1 else n + sum_rec(n - 1)
print(sum_rec(100))