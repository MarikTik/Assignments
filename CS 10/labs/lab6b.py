def print_it(string: str) -> None:
    for i, c in enumerate(string):
        print(f"{i}: {c}")

print_it(input("Enter string: "))