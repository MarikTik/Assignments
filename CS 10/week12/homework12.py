class NegativeIntegerError(ValueError):
    pass

try:
    integer = int(input("Enter a non-negative integer: "))
    if (integer < 0):
        raise NegativeIntegerError()
    
except NegativeIntegerError as ex:
    print("improper input of negative integer")
except ValueError as ex:
    print("This isn't even an integer...")




