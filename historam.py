import matplotlib.pyplot as plt

# Sample data
data1 = [1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5]

# Create the first histogram
plt.subplot(2, 1, 1)  # 2 rows, 1 column, position 2
plt.hist(data1, bins=5, edgecolor='black', color='skyblue')

# Add title and labels for the first histogram
plt.title('Histogram 1')
plt.xlabel('Value')
plt.ylabel('Frequency')

########################################

# Create the second histogram
plt.subplot(2, 1, 2)  # 2 rows, 2 columns, position 2

data2 = range(1, 10)

plt.hist(data2, bins=5, edgecolor='black', color='skyblue')
plt.title('Histogram 2')
plt.xlabel('Value')
plt.ylabel('Frequency')

# Adjust layout to prevent overlap
plt.tight_layout()

# Show the plot
plt.show()
