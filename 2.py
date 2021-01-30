import numpy as np
import matplotlib.pyplot as plt

lines = open("in").readlines()

x = []
y = []
for line in lines:
    x.append(int(line.split()[0]))
    y.append(int(line.split()[1]))

R = open("r").readlines()
ans = open("ans").readlines()

for i in range(0, 20):
    c = plt.Circle((int(ans[i].split()[0]), int(ans[i].split()[1])), radius=int(R[i]))
    plt.gca().add_artist(c)

plt.scatter(x, y)
plt.show()

