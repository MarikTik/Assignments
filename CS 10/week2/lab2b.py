def to_cm(inches: float):
     return 2.54 * inches


inches = float(input("Enter a measurement in inches:\t"))
print(f"{inches} inches is equal to {to_cm(inches)} centimeters")
 