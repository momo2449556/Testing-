import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# Load data: t, x1, y1, x2, y2
data = np.loadtxt("CP.DAT")

t  = data[:, 0]
x1 = data[:, 1]
y1 = data[:, 2]
x2 = data[:, 3]
y2 = data[:, 4]

# Pendulum length (for axis limits)
L = max(np.max(np.sqrt(x2**2 + y2**2)), 1.0)

# Create figure
fig, ax = plt.subplots()
ax.set_aspect('equal')
ax.set_xlim(-L, L)
ax.set_ylim(-L, L)
ax.set_title("Double Pendulum")

# Draw elements
line, = ax.plot([], [], 'o-', lw=2)
trace, = ax.plot([], [], '-', lw=1, alpha=0.6)

trace_x, trace_y = [], []

def init():
    line.set_data([], [])
    trace.set_data([], [])
    return line, trace

def update(i):
    j = i * skip
    line.set_data([0, x1[j], x2[j]], [0, y1[j], y2[j]])
    
    # Append current position of the second mass to trace lists
    trace_x.append(x2[j])
    trace_y.append(y2[j])
    trace.set_data(trace_x, trace_y)
    
    return line, trace




h = 0.001
skip = 10

ani = FuncAnimation(
    fig,
    update,
    frames=len(t) // skip,
    init_func=init,
    interval=1,
    blit=True
)

plt.show()
