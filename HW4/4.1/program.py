import numpy as np

A = np.array([[1, 2, 3], [2, 3, 4], [3, 4, 5]])
lamda = 9.6
x = np.array([1, 1, 1])  # 初始向量

A_i = A - lamda * np.eye(3)  # 减去特征值的单位矩阵

# 反幂法计算特征值和特征向量
for _ in range(1):  # 迭代次数
	a = np.max(abs(x))
	x = x / a  # 归一化
	x = np.linalg.solve(A_i, x)  # 解线性方程 A_i * y = x

# 计算对应的特征值
# eigenvalue = np.dot(x.T, np.dot(A, x))
eigenvalue = 1 / np.max(abs(x)) + lamda  # 计算特征值
print("特征值：", eigenvalue)
print("特征向量：", x)  # 特征向量
print("特征向量：", x / np.linalg.norm(x))  # 归一化特征向量

eigenvalues, eigenvectors = np.linalg.eigh(A)
print("特征值：")
print(eigenvalues)
print("特征向量：")
print(eigenvectors)