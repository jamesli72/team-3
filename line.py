import matplotlib.pyplot as plt

# Sample data
x = [1, 2, 3, 4, 5]
y = [10, 20, 25, 30, 35]

# Create line chart
plt.plot(x, y, marker='o', linestyle='-', color='b', label='Line 1')

# Add title and labels
plt.title('Line Chart Example')
plt.xlabel('X-axis')
plt.ylabel('Y-axis')

# Display the plot
plt.legend()
plt.show()
