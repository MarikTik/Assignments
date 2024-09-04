n = int(input("Enter a positive integer:  "))
sum = 0

for i in range(1, n + 1):
    sum += i
    print(i, end=" ")

print(f"\nThe sum is {sum}.")