bill = float(input("Enter bill amount: "))
size = float(input("Enter size of party: "))
print(f"The bill is ${bill if size < 8 else bill * 1.18 :.2f}")
