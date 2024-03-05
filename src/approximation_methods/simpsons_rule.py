from typing import Callable

function = Callable[[float], float] # type alias for mathematical function signature

def simpsons_approximation(f: function, a: float, b: float, n: int) -> float:
    delta_x = (b - a) / n
    x = lambda i : a + i * delta_x 
    return delta_x / 3 * (
             f(a) + 
             2 * sum(f(x(2 * i)) for i in range(1, n // 2)) + 
             4 * sum(f(x(2 * i - 1)) for i in range(1, n // 2 + 1)) +
             f(b)
          )