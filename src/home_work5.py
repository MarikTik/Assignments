from approximation_methods import *
from decimal import Decimal, getcontext


def error(approx: float, actual: float) -> float:
     return abs(actual - approx)

def relative_error(approx: float, actual: float) -> float:
     return (error(actual, approx) / actual) * 100

def question_4() -> None:
     f = lambda x: x ** 0.5
     a, b = 0, 4
     n = 6
     actual = 5.33333333333333333333

     # Assuming f, a, b, and n are defined earlier in your code
     approximations = {
          "Left hand approximation": left_hand_approximation(f, a, b, n),
          "Mid point approximation": mid_point_approximation(f, a, b, n),
          "Right hand approximation": right_hand_approximation(f, a, b, n),
          "Simpson's rule approximation": simpsons_approximation(f, a, b, n)
     }

     def print_row(description: str, result: float, error: float, relative_error: float):
          print(f"{description:<30} | {result:<20} | {error:<20} | {relative_error}")

     def print_separator(length: int):
          print("-" * length)

     table_header = "Approximation Method:     | Approximation result | Error                | Relative error"

     def print_table():
          print_separator(len(table_header))
          print(table_header)
          print_separator(len(table_header))
          for description, result in approximations.items():
               print_row(description, result, error(result, actual), relative_error(result, actual))
          print_separator(len(table_header))
     
     print_table()
  

if __name__ == "__main__":
     getcontext().prec = 20
     question_4()
 
 

 
