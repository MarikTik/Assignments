from matplotlib import pyplot as plt
import numpy as np
from math import exp
from functools import partial
from typing import Callable

class DataSet:
    def __init__(self) -> None:
        self.years = []
        self.populations = []

    @staticmethod
    def from_census(path: str) -> 'DataSet':
        data_set = DataSet()
        with open(path, "r") as file:
            for line in file.readlines():
                year, population = line.split()
                data_set.years.append(int(year))
                data_set.populations.append(float(population))

        return data_set

class Parameters:
    def __init__(self, a: float, b: float, t0: int, tf: int, p0: float) -> None:
        self.a = a
        self.b = b
        self.t0 = t0
        self.tf = tf
        self.p0 = p0


data_set = DataSet.from_census("hw5/us_population_cenesus_data.txt")    
parameters = Parameters(1, 1, data_set.years[0], data_set.years[-1], data_set.populations[0])

def p_model1(t: float, a: float, b: float, p0):
    return a * p0 / (b * p0 + (a - b * p0) * exp(-a * t))

def p_model_gen() -> Callable[[float], float]:
    def p_model(t, a, b, p0):
        return a * p0 / (b * p0 + (a - b * p0) * exp(-a * t))
    return partial(p_model, a=parameters.a, b=parameters.b, p0=parameters.p0)


def main():
    plt.yscale('log')
    plt.scatter(data_set.years, data_set.populations)
    model = np.vectorize(p_model_gen())
    t = np.linspace(parameters.t0, parameters.tf, 100000)
    # print(t)
    p = model(t)
    plt.plot(t, p, color='red')
    plt.show()

if __name__ == '__main__':
    main()