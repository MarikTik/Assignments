"""This module calculates the pay of an employee given the hours worked and the hourly rate"""


if __name__ == '__main__':
     name = input("Enter a name: ")
     hours = float(input("Enter hours worked: "))
     rate = float(input("Enter hourly rate: "))
     print(f"{name} should be paid ${hours * rate if hours < 40 else 40 * rate + (hours - 40) * rate * 1.5 :,.2f}")

 