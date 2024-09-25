"""This module calculates employee pay at the desired amount"""

def get_input() -> tuple[str, float, float]: 
    """returns a tuple [name, hours, rate] inputed by the user"""
    return (input("\nEnter a name: "), float(input("Enter hours worked: ")), float(input("Enter hourly rate: ")))

def calc_pay(hours: float, rate: float) -> float:
    """returns the pay for a worker that worked for {hours} hours with a pay rate {rate}"""
    return hours * rate if hours < 40 else 40 * rate + (hours - 40) * rate * 1.5

if __name__ == '__main__':
    total = 0
    n = int(input("How many employees do you want to enter? "))
    for i in range(n):
        name, hours, rate = get_input()
        pay = calc_pay(hours, rate)
        total += pay
        print(f"{name} should be paid ${pay:,.2f}")
    print(f"The total amount to be paid is ${total :,.2f}")
    print(f"The average employee is paid ${total / n:,.2f}")