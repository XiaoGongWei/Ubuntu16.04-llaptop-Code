#

import tensorflow as tf
# set GPU
config = tf.ConfigProto(log_device_placement=True)
config.gpu_options.allow_growth = True
sess = tf.Session(config=config)

# run in GPU
mat1 = tf.Variable([3], dtype=tf.float32)
b1 = tf.constant([-0.3],dtype=tf.float32)
x = tf.placeholder(dtype=tf.float32)
proMat = x*mat1 + b1
init = tf.global_variables_initializer()
sess.run(init)

print(sess.run(proMat,{x: [1, 2, 3, 4]}))
print('use GPU test:')
with tf.device('/gpu:0'):
    for _ in range(10):
        print(sess.run(proMat, {x: [_, _ + 1, 1, 2]}))




