from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import os
from urllib import request
import numpy as np
import tensorflow as tf



# tf.logging.set_verbosity(tf.logging.INFO)

# Data sets
IRIS_TRAINING = "iris_training.csv"
IRIS_TRAINING_URL = "http://download.tensorflow.org/data/iris_training.csv"

IRIS_TEST = "iris_test.csv"
IRIS_TEST_URL = "http://download.tensorflow.org/data/iris_test.csv"

def main():
    #if the training and test sets aren't stored locally,downliad them
    if not os.path.exists(IRIS_TRAINING):
        raw = request.urlopen(IRIS_TRAINING_URL).read()
        with open(IRIS_TRAINING,"w") as f:
            f.write(str(raw))
    if not os.path.exists(IRIS_TEST):
        raw = request.urlopen(IRIS_TEST_URL).read()
        with open(IRIS_TEST,"w") as f:
            f.write(str(raw))
    # load datasets
    training_set = tf.contrib.learn.datasets.base.load_csv_with_header(
        filename = IRIS_TRAINING,
        target_dtype = np.int,
        features_dtype = np.float32
    )
    test_set = tf.contrib.learn.datasets.base.load_csv_with_header(
        filename=IRIS_TEST,
        target_dtype=np.int,
        features_dtype=np.float32
    )
    #use ValidtionMonitor
    valid_monitor = tf.contrib.learn.monitors.ValidationMonitor(
        test_set.data,
        test_set.target,
        every_n_steps=100
    )

    # Specify that all features have real-value data
    feature_columns = [tf.feature_column.numeric_column("",shape=[4])]
    #Build 3 layer DNN with 10,20,10 units respectively.
    classfier = tf.contrib.learn.DNNClassifier(
        feature_columns = feature_columns,
        hidden_units = [10,20,10],
        n_classes = 3,
        model_dir="/home/david/PycharmProjects/tf_Estimator_temp",
        config=tf.contrib.learn.RunConfig(save_checkpoints_secs=1)
    )
    # debug

    '''
    # Define the training inputs
    training_input_fn = tf.estimator.inputs.numpy_input_fn(
        x = {"x":np.array(training_set.data)},
        y = np.array(training_set.target),
        num_epochs = None,
        shuffle= True
    )
    '''
    # Train model
    #classfier.train(input_fn = training_input_fn,steps=20)
    classfier.fit(x=training_set.data,
                  y=training_set.target,
                  steps=2000,
                  monitors=[valid_monitor])
    # Define the test inputs
    '''
    test_input_fn = tf.estimator.inputs.numpy_input_fn(
        x = {"x":np.array(test_set.data)},
        y = np.array(test_set.target),
        num_epochs = 1,
        shuffle = False
    )
    '''
    # Evaluate accuracy
    #accracy_score = classfier.evaluate(input_fn = test_input_fn)["accuracy"]
    accracy_score = classfier.evaluate(
        x=test_set.data,
        y=test_set.target,
    )["accuracy"]
    print("\nTest Accuracy:{0:f}\n".format(accracy_score))









if __name__ == "__main__":
    main()
