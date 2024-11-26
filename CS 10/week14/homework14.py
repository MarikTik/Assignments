class Money:
    def __init__(self, amount: float):
        self.amount = amount

    def __str__(self):
        return f"${self.amount:,.2f}"
    
    def __add__(self, other: 'Money'):
        return Money(self.amount + other.amount)
    
    def __sub__(self, other: 'Money'):
        return Money(self.amount - other.amount)

money1, money2 = Money(10), Money(120.5)
print(f"""money1 = {money1}
money2 = {money2}
sum = {money1 + money2}
diff = {money1 - money2}""")
