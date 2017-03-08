# Testing signals by plotting the values from a text file.
import numpy as np
import matplotlib.pyplot as plt

valfile = open('plot_values.txt', 'r')
values = valfile.read().split(",")
freqs = list(range(2**16))
for i in range(2**16):
    freqs[i] *= 44100 / (2**16)
plt.plot(freqs, values)
plt.show()

valfile.close()
