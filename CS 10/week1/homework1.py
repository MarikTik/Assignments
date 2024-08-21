from datetime import datetime

name = "Mark Tikhonov"
classes_taken = [
     "CS36 - C Programming",
     "CS37 - C++ Programming",
     "CS 10 - Python Programming",
]
month, day, year = datetime.today().strftime("%m/%d/%Y").split("/")

template = f"""My name is {name}
I have taken {", ".join(classes_taken)}
Today's date is {month}/{day}/{year}"""

print(template)

 

