from random import randint

random_number = randint(1, 10)
user1_guess = int(input("User 1, enter a number between 1 and 10: "))
user2_guess = int(input("User 2, enter a number between 1 and 10: "))

diff1 = abs(random_number - user1_guess)
diff2 = abs(random_number - user2_guess)

print("Magic Number:", random_number)
out_string = "User {0} guessed {1} which is closer to {2} than {3}"

if diff1 < diff2:
     winning_user = 1
     winning_guess = user1_guess
     losing_guess = user2_guess

elif diff2 < diff1:
     winning_user = 2
     winning_guess = user2_guess
     losing_guess = user1_guess 
# assuming users don't input the same number, ignoring else case:

print(out_string.format(winning_user, winning_guess, random_number, losing_guess))