from typing import Callable

function = Callable[[float], float] # type alias for mathematical function signature

def left_hand_approximation(f: function, a: float, b: float, n: int) -> float:
    delta_x = (b - a) / n
    return sum(f(a + k * delta_x) for k in range(1, n + 1)) * delta_x