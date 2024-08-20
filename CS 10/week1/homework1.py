from datetime import datetime

name = "Mark Tikhonov"
classes_taken = [
     "CS36 - C Programming",
     "CS37 - C++ Programming",
     "CS 10 - Python Programming",
]
date = datetime.today().strftime('%m/%d/%Y')

template = f"""My name is {name}
I have taken {", ".join(classes_taken)}
Today's date is {date}"""

print(template)

# if I were to use three variables, it would look like this:
# day = 19
# month = 8
# year = 2024
# and the date output would look like 
# print(f"{month}/{day}/{year}")

# but I think the method above is more proper in python


