if __name__ == '__main__':
    f_input = lambda message: float(input(message))
    prompt_gallons = lambda: f_input("Enter gallons used (-1 to quit): ")
    prompt_miles = lambda: f_input("Enter miles driven: ")
    
    gallons = prompt_gallons()
    total_gallons, total_miles = 0, 0

    while gallons != -1:
        miles = prompt_miles()
        print(f"MPG: {miles / gallons :.2f}\n")
        total_gallons, total_miles = total_gallons + gallons, total_miles + miles
        gallons = prompt_gallons()

    print(f"Total MPG: {total_miles / total_gallons :.2f}")



 