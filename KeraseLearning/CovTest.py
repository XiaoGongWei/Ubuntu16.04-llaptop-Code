from keras.layers import Conv1D, Conv2D, Input, Dense
from keras.models import Model
import numpy as np

#construct model

x_input = Input(shape=(None,10,32), dtype='float32', name='layers_input')

layer_1 = Conv1D(64, 3, activation='tanh')(x_input)
y_output = Dense(1, activation='sigmoid')(layer_1)

model = Model(inputs=x_input, outputs=y_output)
model.compile(optimizer='rmsprop', loss='mse', metrics=['accuracy'])


#construct data
dataMat_x = np.random.randint(0,256,size=(10,8))
dataMat_y = np.random.randint(0,2,size=(10,1))
model.fit(x=dataMat_x, y=dataMat_y, batch_size=1, epochs=3)






