import numpy as np

A = np.array([[4, 3, 0], [3, 4, -1], [0, -1, 4]])
b = np.array([[24], [30], [-24]])
x = np.array([[0], [0], [0]])

r = b - np.dot(A, x)
d = r

for i in range(3):
    print(f"d{i}=", d)
    alpha = np.dot(r.T, d) / np.dot(np.dot(d.T, A), d)
    print(f"alpha{i}=", alpha)
    x = x + alpha * d
    print(f"x{i+1}=", x)
    r = b - np.dot(A, x)
    print(f"r{i+1}=", r)
    beta  = np.dot(np.dot(r.T, A), d) / np.dot(np.dot(d.T, A), d)
    print(f"beta{i}=", beta)
    d = r - beta * d