import matplotlib.pyplot as ply
import numpy as np

# plot function
data = np.random.randn(2,10000)

fig, axs = ply.subplots(2,2,figsize=[10,10])
axs[0, 0].hist(data[0], bins=5)
axs[0, 1].plot(data[0], data[1])
axs[1, 0].scatter(data[0], data[1])
axs[1, 1].hist2d(data[0], data[1])
axs[1, 1].set_xlabel('smash')
ply.show()
ply.close()
# plot param
import math
xi = np.linspace(0, 2 * math.pi, 100)
yi = np.sin(xi)
aa = ply.plot(xi, yi, 'ro--')
print(aa)
ply.grid(True)
#ply.axis([-5, 5, -5, 5])
ply.show()

"""
Xiao Gongwei
Cao Huijuan
"""
# plt title

ply.hist(yi, bins=50, alpha = 0.5)
ply.show()
