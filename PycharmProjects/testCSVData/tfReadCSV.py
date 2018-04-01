# /usr/bin/python3

import tensorflow as tf
import numpy as np
csvfileName = "test.csv"
csvfileOld = "iris_training.csv"
train_set = tf.contrib.learn.datasets.base.load_csv_with_header(
    filename=csvfileOld,
    target_dtype=np.int,
    features_dtype=np.float32
)
print(train_set.data)
print(train_set.target)

x = np.array([1,2,3,4])
y = np.array([0,1,0,1])

train_input_fn1 = tf.estimator.inputs.numpy_input_fn(
    {"x":x},
    y=y,
    num_epochs=None,
    shuffle=True
)

dict = {"x":np.array(train_set.data)}
print(dict)

train_input_fn = tf.estimator.inputs.numpy_input_fn(
    x={"x":np.array(train_set.data)},
    y=np.array(train_set.target),
    num_epochs=None,
    shuffle=True
)

tensorSparse = tf.SparseTensor(indices=[[0,1],[2,3]],
                values=[6,0.5],
                dense_shape=[3,5]
                )

