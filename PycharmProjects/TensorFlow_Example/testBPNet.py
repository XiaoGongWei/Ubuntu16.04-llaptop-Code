import tensorflow as tf

# 声明变量。
w1 = tf.Variable(tf.random_normal([2, 3], stddev=0.1, seed=1))
b1 = tf.Variable(tf.constant(0.0, shape=[3]))
w2 = tf.Variable(tf.random_normal([3, 1], stddev=0.11, seed=1))
b2 = tf.Variable(tf.constant(0.0, shape=[1]))

# 暂时将输入的特征向量定义为一个常量。注意这里x是一个1*2的矩阵。
x = tf.constant([[0.7, 0.9],[1, 1]])  

# 实现神经网络的前向传播过程，并计算神经网络的输出。
a = tf.nn.relu(tf.matmul(x, w1)+b1)
y = tf.nn.relu(tf.matmul(a, w2)+b2)

sess = tf.Session()
# 运行变量初始化过程。
init_op = tf.global_variables_initializer()
sess.run(init_op)
# 输出[[3.95757794]]
print(sess.run(y))  
sess.close()
