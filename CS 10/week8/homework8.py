# this I unfortunatelly won't be able to truncate to lambda without imported methods

def measuresOfCenter(lst: list[float]) -> tuple[float, float]:
    if len(lst) == 0:
        return None, None
    sorted_list = sorted(lst) # not changing the original list
    sum = 0
    for i in lst:
        sum += i
    
    if len(sorted_list) % 2 != 0:
        median = sorted_list[len(sorted_list) // 2]
    else:
        index = len(sorted_list) // 2
        i1 = sorted_list[index]
        i2 = sorted_list[index - 1]
        median = (i1 + i2) / 2
    
    return sum / len(lst), median


print(measuresOfCenter([])) # (None, None)
print(measuresOfCenter([1])) # (1.0, 1)
print(measuresOfCenter([1, 2])) # (1.5, 1.5)
print(measuresOfCenter([1, 5, 2])) # (2.6666666666666665, 2)
print(measuresOfCenter([1, 32, 5, 2])) # (10.0, 3.5)
print(measuresOfCenter([11.9, 32.2, 25, 62, 18.6, 45.1])) # (32.46666666666667, 28.6)