def fee(hours: float) -> int:
    if hours <= 3:
        return 20
    elif hours <= 9:
        return 5 + fee(hours - 1)
    return 50