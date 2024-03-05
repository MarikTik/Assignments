from typing import Callable

function = Callable[[float], float] # type alias for mathematical function signature

def trapezoidal_approximation(f: function, a: float, b: float, n: int) -> float:
    delta_x = (b - a) / n
    return delta_x * (
                (f(a) + f(b)) / 2 +
                sum(f(a + i * delta_x) for i in range(1, n))
    )