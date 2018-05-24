import numpy as np


rand_mat1 = np.mat(np.random.rand(3, 3))
rand_mat2 = np.mat(np.random.rand(3, 2))
mult_mat = rand_mat1*rand_mat2

arry1 = np.array([1, 2, 3])
mat_diag = np.mat( np.diag(arry1) )

rand_mat1_inv = np.linalg.inv(rand_mat1)
q, r = np.linalg.qr(rand_mat1)

print(np.allclose(rand_mat1, q*r))

print(mat_diag)
print(mult_mat)