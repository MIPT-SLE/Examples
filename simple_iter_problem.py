import numpy as np
import matplotlib.pyplot as plt


def GD(A, b, x0, step, tol=1e-12, n_max=5000):
    iter = 0
    x = x0
    while (np.linalg.norm(A @ x - b) > tol and iter < n_max):
        x = x - step * (A @ x - b)
        iter = iter + 1
    return x, iter


A = np.array([
    [1, 0, 0],
    [0, 10, 0],
    [0, 0, 8]
])

b = np.array([1, 1, 1])

x0 = np.array([0, 0, 0])

iters = []
steps = []
for step_i in range(10, 300):
    step = float(step_i) / 1000.
    x, N = GD(A, b, x0, step)
    iters.append(N)
    steps.append(step)

plt.plot(steps, iters)
plt.xlabel('Шаг метода')
plt.ylabel('Число итераций')
plt.show()

# solution0, _ = GD(A, b, x0, 0.01)
# solution1, i = GD(A, b, x0, 0.8)
# print(solution0)
# print(solution1)
# print(i)


# print(A @ solution0 - b)
# print(np.linalg.norm(A @ solution1 - b))
# print(A @ solution1)
