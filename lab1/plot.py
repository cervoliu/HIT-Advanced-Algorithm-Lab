# Import matplotlib and numpy libraries
import matplotlib.pyplot as plt
import numpy as np

# Open the input file and read the data as a numpy array
input_file = "data/AOL/AOL_info.txt"
data = np.loadtxt(input_file)

# Plot a histogram of the data with 10 bins
plt.hist(data, bins=500)

# plt.boxplot(data)

plt.yscale("log")


# Add a title and labels to the plot
plt.title("Histogram of AOL.txt")
plt.xlabel("Set size")
plt.ylabel("Frequency")

# Show the plot on the screen
plt.show()
