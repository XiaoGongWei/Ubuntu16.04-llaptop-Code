#! /usr/bin/python3
import tensorflow as tf
import tensorflow.tensorboard as tfboard

node1 = tf.constant(3.0,dtype=tf.float32)
node2 = tf.constant(4.0,dtype=tf.float32)
print(node1,node2)

sess = tf.Session()
print(sess.run([node1,node2]))

node3 = tf.add(node1,node2)
print(sess.run(node3))

a = tf.placeholder(tf.float32)
b = tf.placeholder(tf.float32)
addr_node = a + b
print(sess.run(addr_node,{a:3, b:4.5}))
print(sess.run(addr_node,{a:[1, 3], b:[2, 4]}))

addr_and_tripe = addr_node * 3
print(sess.run(addr_and_tripe,{a:[1,2],b:[1,2]}))

W = tf.Variable([.3], dtype=tf.float32)
b = tf.Variable([-.3],dtype=tf.float32)
x = tf.placeholder(tf.float32)
liner_model = W * x + b

init = tf.global_variables_initializer()
sess.run(init)

print(sess.run(liner_model, {x:[1,2,3,4]}))

y = tf.placeholder(tf.float32)
squared_delats = tf.square(liner_model - y)
lossfun = tf.reduce_sum(squared_delats)
print("loss function:",sess.run(lossfun,{x:[1,2,3,4],y:[0,-1,-2,-3]}))

fixW = tf.assign(W,[-1.])
fixb = tf.assign(b,[1.])
sess.run([fixW, fixb])
print("loss function:",sess.run(lossfun,{x:[1,2,3,4],y:[0,-1,-2,-3]}))

optimizer = tf.train.GradientDescentOptimizer(0.01)
train = optimizer.minimize(lossfun)

sess.run(init)
for i in range(1000):
    sess.run(train, {x:[1,2,3,4], y:[0,-1,-2,-3]})

print(sess.run([W,b]))

curr_W, curr_b, curr_loss = sess.run([W,b,lossfun],{x:[1,2,3,4],y:[0,-1,-2,-3]})
print("W:%s, b:%s, loss:%s" % (curr_W, curr_b, curr_loss))


