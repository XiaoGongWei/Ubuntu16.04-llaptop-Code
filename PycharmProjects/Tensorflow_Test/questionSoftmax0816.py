import tensorflow.examples.tutorials.mnist.input_data as input_data
mnist = input_data.read_data_sets("MNIST_data/", one_hot=True)
import tensorflow as tf
# Parameters
learning_rate = 0.001
training_iters = 20000
batch_size = 100
display_step = 10

# Network Parameters
n_input = 784 # MNIST data input (img shape: 28*28)
n_classes = 10 # MNIST total classes (0-9 digits)
dropout = 0.75 # Dropout, probability to keep units

W_conv1 = tf.Variable(tf.random_normal(shape=[5,5,1,32]))
b_conv1 = tf.Variable(tf.random_normal(shape=[1,32]))
W_conv2 = tf.Variable(tf.random_normal(shape=[5,5,32,64]))
b_conv2 = tf.Variable(tf.random_normal( shape=[1,64]))
W_full = tf.Variable(tf.random_normal(shape=[7 * 7 * 64, 1024]))
b_full = tf.Variable(tf.random_normal(shape=[1, 1024]))
W_softmax = tf.Variable(tf.truncated_normal(shape=[1024, 10]))
b_softmax = tf.Variable(tf.truncated_normal(shape=[1,10]))


# tf Graph input
x = tf.placeholder(tf.float32, [None, n_input])
y = tf.placeholder(tf.float32, [None, n_classes])
keep_prob = tf.placeholder(tf.float32, shape=()) #dropout (keep probability)
# Create some wrappers for simplicity
def conv2d(x, W, b, strides=1):
    # Conv2D wrapper, with bias and relu activation
    x = tf.nn.conv2d(x, W, strides=[1, strides, strides, 1], padding='SAME')
    x = tf.nn.bias_add(x, b)
    return tf.nn.relu(x)


def maxpool2d(x, k=2):
    # MaxPool2D wrapper
    return tf.nn.max_pool(x, ksize=[1, k, k, 1], strides=[1, k, k, 1],
                          padding='SAME')


# Create model
def conv_net(x,dropout):
    # Reshape input picture
    x = tf.reshape(x, shape=[-1, 28, 28, 1])

    # Convolution Layer
#     conv1 = conv2d(x, weights['wc1'], biases['bc1'])

    # Max Pooling (down-sampling)
    convOne = tf.nn.conv2d(x, W_conv1, strides=[1,1,1,1], padding="SAME")
    reluOne = tf.nn.relu(convOne + b_conv1)
    conv1 = tf.nn.max_pool(reluOne, ksize=[1,2,2,1],strides=[1,2,2,1],padding="SAME")

    # Convolution Layer

    convTwo = tf.nn.conv2d(conv1, W_conv2, strides=[1,1,1,1], padding="SAME")
    reluTwo = tf.nn.relu(convTwo + b_conv2)
    conv2 = tf.nn.max_pool(reluTwo, ksize=[1,2,2,1], strides=[1,2,2,1],padding="SAME")

    # Fully connected layer
    input_flat=tf.reshape(conv2, shape=[-1, 7 * 7 * 64])
    fc1 = tf.nn.relu(tf.matmul(input_flat, W_full) + b_full)

    # Apply Dropout
    drop_out = tf.nn.dropout(fc1,keep_prob)

    # Output, class prediction
    y_predict = tf.matmul(drop_out, W_softmax) + b_softmax

    return y_predict

# Construct model
pred = conv_net(x, keep_prob)

# Define loss and optimizer
# cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(pred, y))  #(method (3)

softmax = tf.nn.softmax(pred)              #method (1)
# cross_entropy_cnn = - y * tf.log(softmax + 1e-10) #method (1)
# cost = tf.reduce_mean(-tf.reduce_sum(y * tf.log(softmax)))
cross_entropy_cnn = -y * tf.nn.log_softmax(pred)  #method (2)
cost = tf.reduce_mean(tf.reduce_sum(cross_entropy_cnn))

optimizer = tf.train.AdamOptimizer(learning_rate=learning_rate).minimize(cost)

# Evaluate model
correct_pred = tf.equal(tf.argmax(pred, 1), tf.argmax(y, 1))
accuracy = tf.reduce_mean(tf.cast(correct_pred, tf.float32))

# Initializing the variables
init = tf.initialize_all_variables()

sess = tf.Session()
sess.run(tf.initialize_all_variables())
for i in range(2000):
    batch = mnist.train.next_batch(50)

    if 1:#i% 100 == 0:
        train_accuracy = accuracy.eval(feed_dict={x:batch[0], y:batch[1], keep_prob:1.0},session=sess)
        print ("step "+ str(i) +", training accuracy :"+ str(train_accuracy))
        cross_entropy_val = cross_entropy_cnn.eval(feed_dict={x:batch[0], y:batch[1], keep_prob:1.0},session=sess)

    sess.run(optimizer, feed_dict={x:batch[0], y:batch[1], keep_prob:0.75})

test_batch = mnist.test.next_batch(2000)
print("test accuracy :" + str(accuracy.eval(feed_dict={x: test_batch[0], y: test_batch[1], keep_prob:1.0},session=sess)))
