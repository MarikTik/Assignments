from matplotlib import pyplot as plt
import numpy as np
import scipy.optimize as opt

from data_set import DataSet

data_set = DataSet.from_file("hw5/us_population_cenesus_data.txt")    
t0 = data_set.years[0]
tf = data_set.years[-1]
p0 = data_set.populations[0]
 

def p_exponential_model(t: float, a: float, b: float, p0: float) -> float:
    return a * p0 / (b * p0 + (a - b * p0) * np.exp(-a * (t - t0)))

def p_logistic_model(t: float, a: float, b: float, c: float, p0: float) -> float:
    D = (c - p0) / (b* p0 -a)
    return (c + a * D * np.exp((a - b * c) * (t - t0))) / (1 + b * D * np.exp((a - b * c) * (t - t0)))
  

def fit_exponential_model():
    t_data = np.array(data_set.years)
    p_data = np.array(data_set.populations)

    guess = [2.8248e-2, 1e-27] # educated guess

    popt, _ = opt.curve_fit(
        lambda t, a, b: p_exponential_model(t, a, b, p0),
        t_data,
        p_data,
        p0=guess,
        bounds=(0, 1),
        max_nfev=10000
    )
    a_fit, b_fit = popt
    print(f"Fitted parameters using curve_fit on exponential model:\na = {a_fit:.50f}\nb = {b_fit:.50f}\n")
    # sse_curve_fit = np.sum((p_exponential_model(t_data, a_fit, b_fit, p0) - p_data) ** 2)
    # print(f"SSE (curve_fit) = {sse_curve_fit}")
    return a_fit, b_fit

def fit_logistic_model():
    t_data = np.array(data_set.years)
    p_data = np.array(data_set.populations)

    a, b = fit_exponential_model()
    guess = [a, b, 1e-15]

    popt, _ = opt.curve_fit(
        lambda t, a, b, c: p_logistic_model(t, a, b, c, p0),
        t_data,
        p_data,
        p0=guess,
        bounds=(0, 1),
        max_nfev=5000
    )
    a_fit, b_fit, c_fit = popt
    print(f"Fitted parameter:\na = {a_fit:.50f}\nb = {b_fit:.50f}\nc = {c_fit:.50f}\n")
    # sse_curve_fit = np.sum((p_logistic_model(t_data, a_fit, b_fit, c_fit, p0) - p_data) ** 2)
    # print(f"SSE (curve_fit) = {sse_curve_fit}")
    return a_fit, b_fit, c_fit

def plot_exponential_model():
    a, b = fit_exponential_model()
    plt.scatter(data_set.years, data_set.populations)
    t_array = np.linspace(t0, tf, 100000)
    p_array = p_exponential_model(t_array, a, b, p0)
    plt.title("US Population Census Data Exponential Model")
    plt.plot(t_array, p_array, color='red')
    plt.show()

def plot_logistic_model():
    a, b, c = fit_logistic_model()
    plt.scatter(data_set.years, data_set.populations)
    t_array = np.linspace(t0, tf, 100000)
    p_array = p_logistic_model(t_array, a, b, c, p0)
    plt.title("US Population Census Data Logistic Model")
    plt.plot(t_array, p_array, color='green')
    plt.show()

def print_data():
    for year, population in zip(data_set.years, data_set.populations):
        print(f"({year}, {population})", end=',')

def main():
    plot_exponential_model()
    plot_logistic_model()
 
    #print_data()

if __name__ == '__main__':
    main()