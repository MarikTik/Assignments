from sympy import symbols, sin, exp, integrate, series

# Define the variable
x, t = symbols('x t')

# Step 1: Expand sin(t) * exp(t^3) as a series around t = 0
f = sin(t) * exp(t**3)
f_series = series(f, t, 0, 5)  # Expand up to t^4
print("Series expansion of sin(t) * exp(t^3):")
print(f_series)

# Step 2: Integrate term-by-term from 0 to x
integral_series = integrate(f_series, (t, 0, x))
print("\nSeries of the integral of sin(t) * exp(t^3) from 0 to x:")
print(integral_series)

# Step 3: Expand exp(x^3) in the denominator
denominator = exp(x**3)
denominator_series = series(denominator, x, 0, 5)  # Expand up to x^4
print("\nSeries expansion of exp(x^3):")
print(denominator_series)

# Step 4: Perform the division to get the series expansion of y(x)
numerator = 1 + integral_series
y_series = series(numerator / denominator_series, x, 0, 5)
print("\nSeries expansion of y(x):")
print(y_series)
