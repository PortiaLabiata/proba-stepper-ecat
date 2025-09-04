import numpy as np
import matplotlib.pyplot as plt
import os

def draw_ladder(data: np.array):
    for t, dt, c, n in data:
        line_xs = np.array([t, t+dt])
        line_ys = np.array([c, c])
        plt.plot(line_xs, line_ys, c='b')

build_dir = os.environ['BUILD_DIR']
data = np.genfromtxt(f'./{build_dir}/trapez_data.csv', delimiter=',')
draw_ladder(data)
plt.show()