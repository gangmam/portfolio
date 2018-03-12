#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jan  9 14:06:16 2018

@author: dsl
"""

'''
This script shows how to predict stock prices using a basic RNN
'''
import tensorflow as tf
import numpy as np
import matplotlib
import os
import talib
"""
from keras.layers.core import Dense, Activation, Dropout
from keras.layers.recurrent import LSTM
from keras.layers import Bidirectional
import time
from keras.models import Sequential
import keras
from IPython import get_ipython
"""
tf.set_random_seed(777)  # reproducibility

if "DISPLAY" not in os.environ:
    # remove Travis CI Error
    matplotlib.use('Agg')

import matplotlib.pyplot as plt


def MinMaxScaler(data):
    numerator = data - np.min(data, 0)
    denominator = np.max(data, 0) - np.min(data, 0)
    # noise term prevents the zero division
    return numerator / (denominator + 1e-7)


def del_null_line(data):
    output=[]
    date=[]
    for i in data:
        i=i.split(",")
        try:
            date.append(i[0])
            output.append(list(map(float,i[1:])))
        except ValueError as e:
            print(e)
    #print(date)    
    return date,output

def read_file(filename):
    f = open(filename, 'r').read()
    data = f.split('\n')[:-2]
    raw_data=[]
    
    info=data[0].split(",")
    date,raw_data=del_null_line(data)
    
    return info, raw_data

##############################################
a, raw_data = read_file('lg.csv')
xy = np.array(raw_data)

# train Parameters
seq_length = 10
data_dim = 6
hidden_dim = 10
output_dim = 5
learning_rate = 0.01
iterations = 2000

# Open, High, Low, Volume, Close
#xy = np.loadtxt('lg_nullx.csv', delimiter=',')
#xy = xy[::-1]  # reverse order use only daliy-02-stock.csv

xy = MinMaxScaler(xy)
x = xy
y = xy[:, -3]  # Close as label
#print(x)

"""
####################################
np_data=np.array(xy)
#print(np_data)

inputs={
        'info': 'null',
        'date': 'date' ,
        'open':np.array(np_data[:,0],dtype='f8'),
        'high':np.array(np_data[:,1],dtype='f8'),
        'low':np.array(np_data[:,2],dtype='f8'),
        'close':np.array(np_data[:,3],dtype='f8'),
        'volume':np.array(np_data[:,5],dtype='f8')
        }


##open high low close adj.close volume BBands(h m l),stochastic, (moving average20 60 120) 15 feature

upper, middle, lower = talib.abstract.BBANDS(inputs, 20, 2, 2)

slowk,slowd=talib.abstract.STOCH(inputs)

dema=talib.abstract.DEMA(inputs)

ma_5=talib.abstract.MA(inputs,timeperiod=5)

ma_200=talib.abstract.MA(inputs,timeperiod=200)
ma_60=talib.abstract.MA(inputs,timeperiod=60)
ma_120=talib.abstract.MA(inputs,timeperiod=120)

macda,macdb,macdc=talib.abstract.MACD(inputs)# time period 26
adx = talib.abstract.ADX(inputs)
trix=talib.abstract.TRIX(inputs)

obv=talib.abstract.OBV(inputs)
ad=talib.abstract.AD(inputs)

sar=talib.abstract.SAR(inputs)

midpoint=talib.abstract.MIDPOINT(inputs)

##################################################
sma = talib.abstract.SMA(inputs) #SMA start 29
wma = talib.abstract.WMA(inputs)  #WMA start 29
              
#momentum
stocK, stocD = talib.abstract.STOCH(inputs) # stochastic K% start 8
# stochastic D% start 8
rsi = talib.abstract.RSI(inputs, timperiod = 14)# RSI start 14
macd, macdsignal, macdhist =talib.abstract. MACD(inputs) # MACD start 33
willr = talib.abstract.WILLR(inputs) # LWR(larry willilams R%) start 13
adosc = talib.abstract.ADOSC(inputs) # A/D oscillator start 9
cci = talib.abstract.CCI(inputs, timeperiod=14)# CCI   start 13  

###################################################


#x = xy
#y = xy[:, [-3]]  # Close as label
#np_data.append([11])
Xt = []

for i,data in enumerate(x.tolist()):
    #data.append(upper[i],middle[i],lower[i],slowk[i],slowd[i],dema[i],ma_5[i],ma_200[i],ma_60[i],ma_120[i])
    #data.append([macda[i],macdb[i],macdc[i],adx[i],trix[i],obv[i],ad[i],sar[i],midpoint[i]])
    # data[-3] = close(current)
    #technical feature
    #print(stocK[i])
    #print(stocK[i-1])
    
    if data[-3] >= sma[i]:
        data.append(1)
    else:
        data.append(-1)
    #######################
    if data[-3] >= wma[i]:
        data.append(1)
    else:
        data.append(-1)
    #######################
    if stocK[i] > stocK[i-1]:
        data.append(1)
    else:
        data.append(-1)
    #######################
    if stocD[i] > stocD[i-1]:
        data.append(1)
    else:
        data.append(-1)
    #######################
    if rsi[i] > rsi[i-1]:
        data.append(1)
    else:
        data.append(-1)
    #######################
    if macd[i] > macd[i-1]:
        data.append(1)
    else:
        data.append(-1)
    ######################
    if willr[i] > willr[i-1]:
        data.append(1)
    else:
        data.append(-1)
    ######################
    if adosc[i] > adosc[i-1]:
        data.append(1)
    else:
        data.append(-1)
    ######################
    if cci[i] > 200 or ((cci[i] >= -200 and cci[i] <= 200) and cci[i] >= cci[i-1]):
        data.append(1)
    else:
        data.append(-1)
    
    Xt.append(data)

x = np.array(Xt)
####################################

"""
# build a dataset
dataX = []
dataY = []
for i in range(0, len(y) - seq_length):
    if i + seq_length + 4 < len(y):
        _x = x[i:i + seq_length]
        _y = y[i + seq_length : i + seq_length + 5]# 5days close price
    else:
        break
    #print(_x, "->", _y)
    dataX.append(_x)
    dataY.append(_y)

############## 18/01/18 clear untill this line &&& not a number -> (ex)112 line##############

# train/test split
train_size = int(len(dataY) * 0.7)
test_size = len(dataY) - train_size

trainX, testX = np.array(dataX[0:train_size]), np.array(
    dataX[train_size:len(dataX)])
trainY, testY = np.array(dataY[0:train_size]), np.array(
    dataY[train_size:len(dataY)])


# input place holders
X = tf.placeholder(tf.float32, [None, seq_length, data_dim])
Y = tf.placeholder(tf.float32, [None, output_dim])


# build a LSTM network
#########################
cell = tf.contrib.rnn.BasicLSTMCell(num_units=hidden_dim, state_is_tuple=True, activation=tf.tanh)
#########################
#cell = tf.contrib.rnn.DropoutWrapper(cell,input_keep_prob = 1 ,output_keep_prob = 1)
#cell = tf.contrib.rnn.MultiRNNCell([cell] * 2,  state_is_tuple=True)
outputs, _states = tf.nn.dynamic_rnn(cell, X, dtype=tf.float32)
#output and convey state


Y_pred = tf.contrib.layers.fully_connected(
    outputs[:, -1], output_dim , activation_fn= tf.nn.relu)  # We use the last cell's output

#Y_pred = tf.reshape(Y_pred, (None, 5, 1))
# cost/loss
loss = tf.reduce_sum(tf.square(Y_pred - Y))  # sum of the squares
# optimizer
optimizer = tf.train.AdamOptimizer(learning_rate)

train = optimizer.minimize(loss)


# RMSE
targets = tf.placeholder(tf.float32, [None, 5])
predictions = tf.placeholder(tf.float32, [None, 5])
rmse = tf.sqrt(tf.reduce_mean(tf.square(targets - predictions)))

with tf.Session() as sess:
    init = tf.global_variables_initializer()
    sess.run(init)

    # Training step
    for i in range(iterations):
        _, step_loss = sess.run([train, loss], feed_dict={
                                X: trainX, Y: trainY})
        print("[step: {}] loss: {}".format(i, step_loss))

    # Test step
    test_predict = sess.run(Y_pred, feed_dict={X: testX})
    rmse_val = sess.run(rmse, feed_dict={
                    targets: testY, predictions: test_predict})
    print("RMSE: {}".format(rmse_val))
    
    # Plot predictions
    plt.plot(testY)
    plt.plot(test_predict)
    plt.xlabel("Time Period")
    plt.ylabel("Stock Price")
    plt.show()


"""
    plt.plot(testY[2])
    plt.plot(test_predict[2])
    plt.xlabel("Time Period")
    plt.ylabel("Stock Price")
    plt.show()
    plt.plot(testY[3])
    plt.plot(test_predict[3])
    plt.xlabel("Time Period")
    plt.ylabel("Stock Price")
    plt.show()
"""
