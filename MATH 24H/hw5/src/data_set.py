class DataSet:
    def __init__(self) -> None:
        self.years = []
        self.populations = []

    @staticmethod
    def from_file(path: str) -> 'DataSet':
          data_set = DataSet()
          with open(path, "r") as file:
              for line in file.readlines():
                  year, population = line.split()
                  data_set.years.append(int(year))
                  data_set.populations.append(float(population) * 1e6)
     
          return data_set
