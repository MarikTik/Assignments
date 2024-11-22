class Triangle:
     def __init__(self, base: float, height: float):
         self.__base = base
         self.__height = height
     
     @property
     def base(self):
         return self.__base
     
     @base.setter
     def base(self, base):
          if base > 0:
             self.__base = base
          else:
             raise ValueError('Base must be greater than 0')
          
     @property
     def height(self):
         return self.__height
     
     @height.setter
     def height(self, height):
         if height > 0:
             self.__height = height
         else:
             raise ValueError('Height must be greater than 0')
     
     def area(self):
         return self.base * self.height / 2


triangle = Triangle(100, 2)
print(f"base = {triangle.base}, height = {triangle.height}")
triangle.base = 5
triangle.height = 10
print(f"new area = {triangle.area()}")