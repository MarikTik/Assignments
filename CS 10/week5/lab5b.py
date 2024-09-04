prompt = lambda: input("Enter an integer (q to quit):  ")

response = prompt()
sum = 0
while response != "q":
    integer = int(response)
    sum += 0 if integer % 2 else integer
    response = prompt()

print(f"The sum of the even integers entered is {sum}")