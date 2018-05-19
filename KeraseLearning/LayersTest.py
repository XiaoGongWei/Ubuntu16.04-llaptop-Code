from keras.models import Sequential, Model
from keras.layers import Dense, LSTM, Activation, Input
from keras.optimizers import adam, rmsprop, adadelta
import numpy as np
import matplotlib.pyplot as plt

#construct model
data_input = Input((1,),dtype='float32',name='input_data')
x = Dense(100, activation = 'relu', name='layer1')(data_input)
x = Dense(32, activation = 'tanh', name='layer2')(x)
data_output = Dense(1, activation='tanh', name='output_data')(x)

model = Model(inputs=data_input, outputs=data_output)
model.compile(optimizer='rmsprop', loss='mse', metrics=['accuracy'])



#print model
print('models layers:',model.layers)
print('models config:',model.get_config())
print('models summary:',model.summary())

#get layers by name
layer1 = model.get_layer(name='layer1')
layer1_W_pro = layer1.get_weights()
layer2 = model.get_layer(name='layer2')
layer2_W_pro = layer2.get_weights()


#train data
dataX = np.linspace(-2 * np.pi,2 * np.pi, 1000)
dataX = np.reshape(dataX, [dataX.__len__(), 1])
noise = np.random.rand(dataX.__len__(), 1) * 0.1
dataY = np.sin(dataX) + noise

model.fit(dataX, dataY, epochs=10, batch_size=10, shuffle=True, verbose = 1)
predictY = model.predict(dataX, batch_size=1)
score = model.evaluate(dataX, dataY, batch_size=10)
print(score)
#get layers1 wights
layer1_W_end = layer1.get_weights()
#layer1_W_end - layer1_W_pro

layer2_W_end = layer2.get_weights()
#layer2_W_end - layer2_W_pro

#plot
fig, ax = plt.subplots()
ax.plot(dataX, dataY, 'b-')
ax.plot(dataX, predictY, 'r.')
ax.set(xlabel="x", ylabel="y=f(x)", title="y = sin(x),red:predict data,bule:true data")
ax.grid(True)
plt.savefig('d:\\test.eps', format='eps', dpi=1000)
plt.show()

#save weight
model.save_weights('d:\\test.hdf5')

#create new model
data_input1 = Input((1,),dtype='float32',name='input_data1')
x1 = Dense(100, activation = 'relu', name='layer11')(data_input1)
x1 = Dense(32, activation = 'tanh', name='layer21')(x1)
data_output1 = Dense(1, activation='tanh', name='output_data')(x1)

model1 = Model(inputs=data_input1, outputs=data_output1)
model1.load_weights('d:\\test.hdf5')