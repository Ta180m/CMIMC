import numpy as np
import matplotlib.pyplot as plt

lines = open("in").readlines()

x = []
y = []
for line in lines:
    x = line.split()[0]
    y = line.split()[1]

plt.scatter(x, y)
