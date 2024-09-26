from matplotlib import pyplot as plt
import numpy as np
from scipy.optimize import curve_fit, minimize
from functools import partial
from typing import Callable
from data_set import DataSet
from parameters import Parameters


data_set = DataSet.from_file("hw5/us_population_cenesus_data.txt")    
parameters = Parameters(.1, .1, data_set.years[0], data_set.years[-1], data_set.populations[0])

def p_exponential_model(t: float, a: float, b: float, p0: float) -> float:
    return a * p0 / (b * p0 + (a - b * p0) * np.exp(-a * (t - parameters.t0)))

def p_logistic_model(t: float, a: float, b: float, c: float, p0: float) -> float:
    D = (c - p0) / (b* p0 -a)
    return (c + a * D * np.exp((a - b * c) * t)) / (1 + b * D * np.exp((a - b * c) * t))
  

def fit_exponential_model():
    t_data = np.array(data_set.years)
    p_data = np.array(data_set.populations)

    guess = [
        2.8248e-2,
        1e-27
        ]
    popt, _ = curve_fit(
        lambda t, a, b: p_exponential_model(t, a, b, parameters.p0),
        t_data,
        p_data,
        p0=guess,
        bounds=(0, 1)
    )
    a_fit, b_fit = popt
    # sse_curve_fit = np.sum((p_exponential_model(t_data, a_fit, b_fit, parameters.p0) - p_data) ** 2)
    # print(f"Fitted parameters using curve_fit:\na = {a_fit:.50f}\nb = {b_fit:.50f}\n")
    # print(f"SSE (curve_fit) = {sse_curve_fit}")
    return a_fit, b_fit

def fit_logistic_model():
    t_data = np.array(data_set.years)
    p_data = np.array(data_set.populations)

    guess = [
        0.09,
        0.000000001,
        parameters.p0 - 2
    ]
    lower_bounds = [1e-15, 1e-15, 1e-15]  # strictly positive bounds for a, b, c
    upper_bounds = [0.3, 1e1, parameters.p0 - 1]

    popt, _ = curve_fit(
        lambda t, a, b, c: p_logistic_model(t, a, b, c, parameters.p0),
        t_data,
        p_data,
        p0=guess,
        bounds=(lower_bounds, upper_bounds),
        max_nfev=5000
    )
    a_fit, b_fit, c_fit = popt
    # def loss(params):
    #     a, b, c = params
    #     return np.sum((p_logistic_model(t_data, a, b, c, parameters.p0) - p_data) ** 2)
    
    # result = minimize(loss, guess, method='BFGS')

    # a_fit, b_fit, c_fit = result.x
    sse_minimize = np.sum((p_logistic_model(t_data, a_fit, b_fit, c_fit, parameters.p0) - p_data) ** 2)

    print(f"Fitted parameter:\na = {a_fit:.50f}\nb = {b_fit:.50f}\nc = {c_fit:.50f}\n")
    print(f"SSE (minimize) = {sse_minimize:50f}")
    return a_fit, b_fit, c_fit

def plot_exponential_model():
    a, b = fit_exponential_model()
    plt.scatter(data_set.years, data_set.populations)
    t_array = np.linspace(parameters.t0, parameters.tf, 100000)
    p_array = p_exponential_model(t_array, a, b, parameters.p0)
    plt.title("US Population Census Data Exponential Model")
    plt.plot(t_array, p_array, color='red')
    plt.show()

def plot_logistic_model():
    a, b, c = fit_logistic_model()
    plt.scatter(data_set.years, data_set.populations)
    t_array = np.linspace(parameters.t0, parameters.tf, 100000)
    p_array = p_logistic_model(t_array, a, b, c, parameters.p0)
    plt.title("US Population Census Data Logistic Model")
    plt.plot(t_array, p_array, color='red')
    plt.show()

def print_data():
    for year, population in zip(data_set.years, data_set.populations):
        print(f"({year}, {population})", end=',')

def main():
    # plot_exponential_model()
    plot_logistic_model()
    fit_logistic_model()
    #print_data()
    

if __name__ == '__main__':
    main()