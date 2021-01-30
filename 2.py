import numpy as np
import matplotlib.pyplot as plt

lines = open("in2").readlines()

x = []
y = []
for line in lines:
    x.append(int(line.split()[0]))
    y.append(int(line.split()[1]))

R = open("r").readlines()
ans = open("out").readlines()

for i in range(0, 15):
    c = plt.Circle((float(ans[i].split()[0]), float(ans[i].split()[1])), radius=int(R[i]), color=(0, 1, 0))
    plt.gca().add_artist(c)

plt.scatter(x, y)
plt.show()

