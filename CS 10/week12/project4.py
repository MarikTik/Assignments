class Employee:
     def __init__(self, name: str="", hours: float=0, rate: float=0):
         self.__name = name
         self.__hours = hours
         self.__rate = rate
     
     @property
     def name(self):
         return self.__name
     
     @property
     def hours(self):
         return self.__hours
     
     @property

     def rate(self):
          return self.__rate
     
     @name.setter
     def name(self, name):
         self.__name = name
     
     @hours.setter
     def hours(self, hours):
         self.__hours = hours if hours >= 0 else self.__hours
     
     @rate.setter
     def rate(self, rate):
         self.__rate = rate if rate >= 0 else self.__rate

     def get_input(self) -> None:
          self.name = input("\nEnter a name: ")
          self.hours = float(input("Enter hours worked: "))
          self.rate = float(input("Enter hourly rate: "))

     @staticmethod
     def from_stdin() -> 'Employee': # a bit more idiomatic in my opinion
         employee = Employee()
         employee.get_input()
         return employee
     
     def calc_pay(self) -> float:
         h, r = self.hours, self.rate
         return h * r if h < 40 else 40 * r + (h - 40) * r * 1.5

     def __repr__(self):
         dollar = "$"
         return f"Name:{self.name:>33}\nHours Worked:{self.hours:>25}\nHourly Rate:{dollar+str(self.rate):>26}"
     
     def __str__(self):
         return self.__repr__()
     
     
class Menu:
     def __init__(self):
          self.__employees: list[Employee] = []
          self.__prompts = {
              "1: Enter an employee" : lambda: True,
              "2: Display all employees" : lambda: len(self.__employees) > 0,
              "q: Quit the application" : lambda: True
          }

          self.__actions = {
              "1": lambda: self.__employees.append(Employee.from_stdin()),
              "2": lambda: print(*self.__employees, sep="\n\n"),
              "q": lambda: exit("No employees entered") if not self.__employees else exit(self)
          }
     
     def __str__(self):           
          total = sum(employee.calc_pay() for employee in self.__employees)
          avg = total / len(self.__employees)
          return f"The total amount to be paid is ${total :,.2f}\nThe average employee is paid ${avg:,.2f}"

     def __prompt(self):
          prompt = "\n".join(filter(lambda k: self.__prompts[k](), self.__prompts))
          self.__actions.get(input(f"{prompt}\n\n"))()
          print("")
          
     @staticmethod
     def run():
          sep = "-" * 80
          topic = "Employee Data Entry Application "
          print(f"{sep}\n{topic:^80}\n{sep}\n")
          menu = Menu()
          
          while True:
               menu.__prompt()

if __name__ == '__main__':
     Menu.run()
