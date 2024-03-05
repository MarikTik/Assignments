import matplotlib.pyplot as plt

# Sample data: approximation methods and their results
approximations = ["Left hand", "Mid point", "Right hand"]
results = [1.234, 5.678, 9.012]

# Create a figure and an axis
fig, ax = plt.subplots()
# Hide the axes
ax.axis('tight')
ax.axis('off')

# Prepare the data for the table: zip together the approximation methods and their results
table_data = list(zip(approximations, results))

# Creating the table
table = ax.table(cellText=table_data,
                 colLabels=["Approximation", "Result"],
                 cellLoc='center',
                 loc='center')

plt.show()