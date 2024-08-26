from random import randint


def different_digits(integer: int) -> set[int]:
     if integer < 0 or integer > 99:
          raise RuntimeError("integer out of lottery range")
     
     return {integer // 10, integer % 10}

lottery_number = randint(0, 99)
guess = int(input("Enter an integer from 0-99: "))
profit = 0
guess_digits = different_digits(guess)
lottery_digits = different_digits(lottery_number)

if lottery_number == guess:
     profit = 10_000

elif guess_digits == lottery_digits:
     profit = 3000

elif len(guess_digits.intersection(lottery_digits)) == 1:
     profit = 1000

print(f"You won ${profit} dollars.")


