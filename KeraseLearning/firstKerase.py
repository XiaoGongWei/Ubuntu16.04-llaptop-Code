from keras.models import Sequential
from keras.layers import Dense, LSTM, Activation
from keras.optimizers import adam, rmsprop, adadelta
import numpy as np
import matplotlib.pyplot as plt

#construct model
models = Sequential()
models.add(Dense(100, init='uniform',activation='relu' ,input_dim=1))
models.add(Dense(50, activation='relu'))
models.add(Dense(1,activation='tanh'))
adamoptimizer = adam(lr=0.001, beta_1=0.9, beta_2=0.999, decay=0.00001)
models.compile(optimizer='rmsprop', loss='mse',metrics=["accuracy"] )

#train data
dataX = np.linspace(-2 * np.pi,2 * np.pi, 1000)
dataX = np.reshape(dataX, [dataX.__len__(), 1])
noise = np.random.rand(dataX.__len__(), 1) * 0.1
dataY = np.sin(dataX) + noise

models.fit(dataX, dataY, epochs=100, batch_size=10, shuffle=True, verbose = 1)
predictY = models.predict(dataX, batch_size=1)
score = models.evaluate(dataX, dataY, batch_size=10)

print(score)
#plot
fig, ax = plt.subplots()
ax.plot(dataX, dataY, 'b-')
ax.plot(dataX, predictY, 'r.')

ax.set(xlabel="x", ylabel="y=f(x)", title="y = sin(x),red:predict data,bule:true data")
ax.grid(True)

plt.show()