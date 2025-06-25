import numpy as np

A = np.array([[-4, -3, -7], [2, 3, 2], [4, 2, 7]])

print("原矩阵A：")
print(A)

#用Householder进行正交三角化
def householder_reflection(A):
    n = A.shape[0]
    Q = np.eye(n)
    R = A.copy()

    for k in range(1):
        x = R[k:, k]
        e = np.zeros_like(x)
        e[0] = np.linalg.norm(x)
        u = x + x[0]/abs(x[0]) * e
        v = u / np.linalg.norm(u)
        print(v)
        H = np.eye(n - k) - 2 * np.outer(v, v)
        print(H)
        R = H @ R
    return R

R = householder_reflection(A)
print(R)
R1 = householder_reflection(R[1:, 1:])
print(R1)