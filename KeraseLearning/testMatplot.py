import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as gImage
from PIL import Image
# create data
x1 = np.linspace(0.0, 5.0)
x2 = np.linspace(0.0, 2.0)
y1 = np.sin(x1)
y2 = np.exp(x2)
#subplot
plt.subplot(2,1,1)
plt.plot(x1,y1,'k-o')
plt.title('y = f(x)')
plt.ylabel('y=sin(x)')
plt.show()
#subplots
fig, axs = plt.subplots(2,2, figsize=(5,5))
axs[0,0].plot(x1,y1)
axs[0,1].plot(x1,y1+1)
axs[1,0].plot(x1,y1+1)
axs[1,1].scatter(x1, y1, alpha=0.6,c = y1, s = 10 * x1)
axs[1,1].grid(True)
plt.show()
#read image
image1 = gImage.imread('D:\\1.bmp')
print(image1.shape)
plt.axis('off')
plt.imshow(image1)
plt.show()

#PIL
image2 = Image.open('D:\\1.bmp')
image2_resize = image2.resize((64,64))
image2_array = np.array(image2)
image2.show()
