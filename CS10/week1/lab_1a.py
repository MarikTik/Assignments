def h(t):
     return -16 * t**2 + 53 * t + 5
 
def show_height(t):
     print(f"The height of the ball after {t} seconds is {h(t)} ft.")

show_height(2)
