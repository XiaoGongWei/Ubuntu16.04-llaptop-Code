#! /usr/bin/python3

import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data
import os
from tensorflow.python import debug as tf_debug


print(os.getcwd())

mnist = input_data.read_data_sets("MNIST_data/",one_hot=True)
sess = tf.InteractiveSession()

x = tf.placeholder(tf.float32,[None, 784])
y_ = tf.placeholder(tf.float32,[None, 10])

W = tf.Variable(tf.zeros([784,10]))
b = tf.Variable(tf.zeros([10]))

tf.global_variables_initializer().run()

y = tf.nn.softmax(tf.matmul(x,W) + b)

cross_entropy_loss = tf.reduce_mean(-tf.reduce_sum(y_ * tf.log(y),
                             reduction_indices=[1])) # methond(1)

y1 = tf.matmul(x,W) + b
cross_entropy_loss1 = tf.reduce_mean(
    tf.nn.softmax_cross_entropy_with_logits(labels=y_,logits=y1)
    )# methond(2)

train_step = tf.train.GradientDescentOptimizer(0.01).minimize(cross_entropy_loss1)
# debug
#sess = tf_debug.LocalCLIDebugWrapperSession(sess)
#sess.add_tensor_filter('has_inf_or_nan', tf_debug.has_inf_or_nan)

for i in range(20000):
    if i%100 == 0:
        print('traing...',i)
    batch_x, batch_y = mnist.train.next_batch(50)
    sess.run(train_step, feed_dict={x:batch_x, y_:batch_y})
    #train_step.run(feed_dict={x:batch_x, y_:batch_y})

correct_prediction = tf.equal(tf.argmax(y,1),tf.argmax(y_,1))
print("correct_prediction:",correct_prediction)
accuracy = tf.reduce_mean(tf.cast(correct_prediction,tf.float32))
print(sess.run(accuracy,feed_dict={x:mnist.test.images,y_:mnist.test.labels}))
"""
list_W = sess.run([W])
list_b = sess.run([b])
list_temp = ['xiao','gong','wei']
print(type(list_W))
print(list_W.__len__())

print(list_temp)
print(list_temp.__len__())
"""

sess.close()

