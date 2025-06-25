import numpy as np

# 将A矩阵的某两个对角元经相似变换变为0
def similarity_transformation(A, i, j):
    n = A.shape[0]
    P = np.eye(n)
    theta = np.arctan2(2 * A[i, j], A[i, i] - A[j, j]) / 2
    c = np.cos(theta)
    s = np.sin(theta)
    P[i, i] = c
    P[j, j] = c
    P[i, j] = -s
    P[j, i] = s
    return P, P.T @ A @ P, (2 * A[i, j])/(A[i, i] - A[j, j])

A = np.array([[4, 2, 2], [2, 5, 1], [2, 1, 6]])
print("原矩阵A：")
print(A)

P1, A_1, s_1 = similarity_transformation(A, 0, 1)
print("相似变换后的矩阵A_1：")
print(A_1)
print("对角元s_1：")
print(s_1)
print("相似变换矩阵P1：")
print(P1)

P2, A_2, s_2 = similarity_transformation(A_1, 0, 2)
print("相似变换后的矩阵A_2：")
print(A_2)
print("对角元s_2：")
print(s_2)
print("相似变换矩阵P2：")
print(P2)

eigenvalue = np.diag(A_2)
print("对角线上的特征值：")
print(eigenvalue)

eigenvalues, _ = np.linalg.eig(A)
print("特征值：")
print(eigenvalues)