#!/usr/bin/python3
import tensorflow as tf
hello = tf.constant('hello TensorFlow!');
sess = tf.Session();
print(sess.run(hello));
a = tf.constant(10);
b = tf.constant(11);
print(sess.run(a+b));
print("hello XiaoGongWei");
