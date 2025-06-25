import numpy as np

n = 100
A = np.random.randint(1, 10, (n, n))
AS = A @ A.T
A = AS + np.eye(n)
eigenvalues, eigenvectors = np.linalg.eig(A)
print(max(abs(eigenvalues)))
print(eigenvalues)
with open("output.dat", "w") as f:
    f.write(str(n)+"\n")
    for i in range(n):
        for j in range(n):
            f.write(str(A[i][j])+" ")
        f.write("\n")
    f.write(str(max(abs(eigenvalues))))