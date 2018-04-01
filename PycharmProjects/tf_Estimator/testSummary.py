# /usr/bin/python3
import tensorflow as tf
import os
import time
sess = tf.Session()

with tf.name_scope("XiaoGongWei"):
    a = tf.placeholder(dtype=tf.float32,name="a")
    b = tf.Variable([1.0],dtype=tf.float32,name="b")
    W = tf.Variable([[-2,-1,0,1,2],[1,2,3,4,100]],
                    dtype=tf.float32,
                    name="W")
    addAB = W * a + b
    tf.summary.scalar("wight_max",tf.reduce_mean(W))
    tf.summary.scalar("b_value",tf.reduce_mean(b))
    tf.summary.scalar("a_value",tf.reduce_mean(a))
    tf.summary.histogram("WightMatrix",W)
    merged = tf.summary.merge_all()
    train_summary = tf.summary.FileWriter('/home/david/PycharmProjects/TensorBoard/TestSum',
                                          sess.graph)
    sess.run(tf.global_variables_initializer())
    for i in range(100):
        run_options = tf.RunOptions(trace_level=tf.RunOptions.FULL_TRACE)
        run_metadata = tf.RunMetadata()
        tfmensumm, myadd = sess.run([merged, addAB], feed_dict={a: i})
        train_summary.add_run_metadata(run_metadata,"step:%d" % i)
        print(myadd)
        train_summary.add_summary(tfmensumm,i)
    train_summary.close()

# test Variable
with tf.name_scope("test"):
    state = tf.Variable(0,dtype=tf.float32)
    oneConst = tf.constant(1,dtype=tf.float32)
    new_state = tf.add(state * 2,oneConst)
    updataOp = tf.assign(state,new_state)
    sess.run(tf.global_variables_initializer())
    for i in range(3):
        sess.run(updataOp)
        print(sess.run(state))
        varVal = tf.Variable(i, dtype=tf.float32)
        op_var = tf.assign(varVal, i)
        #sess.run(tf.global_variables_initializer())
        print(sess.run(op_var))


#os.system("tensorboard --logdir=/tmp/XIAO")

#time.sleep(120)
#print("AAA")
#os.system("rmdir --ignore-fail-on-non-empty /tmp/XIAO")
