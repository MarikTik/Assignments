from approximation_methods import *
import math

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
          f"L_({n})": left_hand_approximation(f, a, b, n),
          f"M_({n})": mid_point_approximation(f, a, b, n),
          f"R_({n})": right_hand_approximation(f, a, b, n),
          f"T_({n})": trapezoidal_approximation(f, a, b, n),  
          f"S_({n})": simpsons_approximation(f, a, b, n)
     }

     def print_row(description: str, result: float, error: float, relative_error: float):
          print(f"{description:<21} | {result:<20} | {error:<20} | {relative_error}")

     def print_separator(length: int):
          print("-" * length)

     table_header = "Approximation Method: | Approximation result | Error                | Relative error"

     def print_table():
          print_separator(len(table_header))
          print(table_header)
          print_separator(len(table_header))
          for description, result in approximations.items():
               print_row(description, result, error(result, actual), relative_error(result, actual))
          print_separator(len(table_header))
     
     print_table()

def question5():

     pass

def question18():
     def normal_distribution(x: float) -> float:
          return 1 / math.sqrt(2 * math.pi) * math.exp(-x ** 2 / 2)
     
     print(f"S_4 = {simpsons_approximation(normal_distribution, -1,1, 4)}")

     f = lambda x: normal_distribution(x)

     print(f"S_4* = {1/6 * (f(-1) + 2*(f(0)) + 4 * (f(-1/2) + f(1/2)) + f(1))}")
     

if __name__ == "__main__":
     print ("Homework 5 By Mark Tikhonov\n\n\n")
     print("4.\n\n")
     question_4()
     print("\n\n5.\n\n")
     question5()
     print("\n\n18.\n\n")
     question18()
 
,,,,,,,,,,,,        nk k kk         k  . ,. 