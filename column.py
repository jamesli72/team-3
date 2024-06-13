import matplotlib.pyplot as plt

# Sample data
categories = ['A', 'B', 'C', 'D']
values = [30, 40, 20, 50]

# Create bar chart
plt.bar(categories, values, color='skyblue')

# Add title and labels
plt.title('Bar Chart Example')
plt.xlabel('Categories')
plt.ylabel('Values')

# Display the plot
plt.show()
