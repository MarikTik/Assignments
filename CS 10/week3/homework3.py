class Coordinate:
     def __init__(self, x: float, y: float):
          self.x = x
          self.y = y

class Rectangle:
     def __init__(self, bottom_left_corner: Coordinate, right_top_corner: Coordinate):
          self._blc = bottom_left_corner
          self._rtc = right_top_corner

     def __contains__(self, point: Coordinate) -> bool:
         return self._blc.x <= point.x <= self._rtc.x and self._blc.y <= point.y <= self._rtc.y


if __name__ == '__main__':
     x1 = float(input("Enter x1: "))
     y1 = float(input("Enter y1: "))
     x2 = float(input("Enter x2: "))
     y2 = float(input("Enter y2: "))
     blc = Coordinate(x1, y1)
     rtc = Coordinate(x2, y2)
     rect = Rectangle(blc, rtc)
     x = float(input("Enter x: "))
     y = float(input("Enter y: "))
     point = Coordinate(x, y)
     print(point in rect)
 