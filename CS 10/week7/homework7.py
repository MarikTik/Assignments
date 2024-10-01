avg = lambda *args: sum(args) / len(args) if args else None
print(avg(1, 2, 3)) # 2.0
print(avg()) # None