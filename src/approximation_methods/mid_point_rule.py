from typing import Callable

function = Callable[[float], float] # type alias for mathematical function signature

def mid_point_approximation(f: function, a: float, b: float, n: int) -> float:
    delta_x = (b - a) / n
    return sum(f(a + delta_x / 2 + k * delta_x) for k in range(0, n)) * delta_x