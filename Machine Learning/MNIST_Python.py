
# coding: utf-8

# In[1]:


import tensorflow as tf
import random
import matplotlib.pyplot as plt
tf.set_random_seed(777)
from tensorflow.examples.tutorials.mnist import input_data


# In[2]:


mnist = input_data.read_data_sets("MNIST_data/", one_hot = True)
#MNIST_data/train-images를 다운받습니다.(tensorflow에서 MNIST data-set을 받는 코드에 해당합니다)
nb_classes = 10
#결과값의 출력이 0 ~ 9 값으로 출력됩니다.


# In[3]:


X = tf.placeholder(tf.float32, [None, 784])
# 28 X 28 에 해당하는 X값입니다.
Y = tf.placeholder(tf.float32, [None, nb_classes])
# 0 ~ 9 값을 출력하는 Y값입니다.
W = tf.Variable(tf.random_normal([784, nb_classes]))
b = tf.Variable(tf.random_normal([nb_classes]))
hypothesis = tf.nn.softmax(tf.matmul(X, W) + b)

# Y = X*W + b


# In[4]:


cost = tf.reduce_mean(-tf.reduce_sum(Y * tf.log(hypothesis), axis = 1))
# cost값을 구하는 공식을 tensorflow를 활용하여 구현
optimizer = tf.train.GradientDescentOptimizer(learning_rate = 0.1).minimize(cost)
# cost값을 최소화 하는 공식을 tensorflow 내장함수를 활용하여 구현
is_correct = tf.equal(tf.arg_max(hypothesis, 1), tf.arg_max(Y, 1))
accuracy = tf.reduce_mean(tf.cast(is_correct, tf.float32))
# 특정 X값에 대해 설계한 모델이 나타낸 결과값과 정답이 맞는지
# 알아내기위해 accuracy 측정을 위한 내장함수 활용


# In[5]:


training_epochs = 15
batch_size = 100
# 한번에 100개의 data를 가져와서 
# 총 15번 학습을 반복합니다.


# In[6]:


with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    # 한번 학습을 실시할 때마다 얼만 큼 정확성이 상승하는지
    # 알기위해 cost를 출력합니다.
    for epoch in range(training_epochs):
        # 반복적인 학습을 위한 for문에 해당합니다.
        avg_cost = 0
        total_batch = int(mnist.train.num_examples / batch_size)
        for i in range(total_batch):
            # 가져온 데이터에대한 구체적인 학습을 시작합니다.
            batch_xs, batch_ys = mnist.train.next_batch(batch_size)
            c, _ = sess.run([cost, optimizer], feed_dict={X: batch_xs, Y: batch_ys})
            avg_cost += c / total_batch
            # 위에 설정한 hypothesis에 대한 구체적인 학습을 시작하기 위해서 X값과 Y값을 넣어줍니다.
            
        print('Epoch:', '%04d' % (epoch + 1), 'cost =', '{:.9f}'.format(avg_cost))
        # 반복시마다 정확성 상승 측정
    print("Learning finished")
    # 학습을 완료했을 경우 정확성을 출력합니다. 
    print("Accuracy: ", accuracy.eval(session=sess, feed_dict={ X: mnist.test.images, Y: mnist.test.labels}))
    
    r = random.randint(0, mnist.test.num_examples - 1)
    # 받아온 data 중 random한수를 저장해서 변수 r의 값으로 저장합니다. 
    
    print("Label: ", sess.run(tf.argmax(mnist.test.labels[r:r + 1], 1)))
    # r의 값이 몇인지 를 출력합니다
    
    print("Prediction: ", sess.run( tf.argmax(hypothesis, 1), feed_dict={X: mnist.test.images[r:r + 1]}))
    # 학습한 모델이 예측한 예측값을 출력합니다.
    plt.imshow( mnist.test.images[r:r + 1].reshape(28, 28), cmap='Greys', interpolation='nearest')
    # 해당 데이터의 값을 사람이 볼수 있는 글씨의 형태로 출력합니다.
    
    plt.show()


# In[ ]:





# In[ ]:





# In[ ]:




