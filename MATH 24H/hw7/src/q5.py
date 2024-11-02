import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp

# Define the system of equations
def system(t, state):
    x, y = state  # state = [x(t), y(t) = dx/dt]
    dxdt = y
    dydt = (5/3) * np.exp(-t) - (32/3) * np.exp(-4*t)
    return [dxdt, dydt]

# Time range for simulation
t_span = (0, 5)
t_eval = np.linspace(0, 5, 500)

# Initial conditions (x(0) = 0, y(0) = dx/dt(0) = some initial value)
initial_state = [0, 0]  # You can vary this for different trajectories

# Solve the system of equations
solution = solve_ivp(system, t_span, initial_state, t_eval=t_eval)

# Extract the solution
x = solution.y[0]
y = solution.y[1]

# Plot the phase diagram
plt.figure(figsize=(8, 6))
plt.plot(x, y, label='Phase Trajectory')
plt.xlabel('x(t)')
plt.ylabel('dx/dt (t)')
plt.title('Phase Diagram')
plt.grid()
plt.legend()
plt.show()
