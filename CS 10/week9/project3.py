import re

def luhn(ccn: str) -> bool:
     digits = list(map(int, ccn))
     odd_sum = sum(digits[-1::-2])
     even_sum = sum([sum(divmod(2 * digit, 10)) for digit in digits[-2::-2]])
     return (odd_sum + even_sum) % 10 == 0 

def rn_algorithm(rn: str) -> bool:
     r = list(map(int, rn))
     return (sum([sum(r[-1::-3]), 7 * sum(r[-2::-3]), 3 * sum(r[-3::-3])]) % 10 == 0)

def is_valid_CC(ccn: str) -> bool:
     return 13 <= len(ccn) <= 16 and re.match(r'^[4, 5, 6, 37].[0-9]*$', ccn) and luhn(ccn)

def is_valid_RN(rn: str) -> bool:
     return len(rn) == 9 and re.match(r'^[0-9]*$', rn) and rn_algorithm(rn)

sep = "-" * 80
print(f"Credit Card Entry\n{sep}")

while (ccn := input("Enter credit card number: ")) != "q":
     print(f"{ccn} is {'valid' if is_valid_CC(ccn) else 'invalid'}")

print(f"\nRouting Number Entry\n{sep}")
while (rn := input("Enter registration number: ")) != "q":
     print(f"{rn} is {'valid' if is_valid_RN(rn) else 'invalid'}")
