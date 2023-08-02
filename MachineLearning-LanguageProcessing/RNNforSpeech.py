import numpy as np
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers
import os

model = keras.Sequential()
# Add an Embedding layer expecting input vocab of size 1000, and
# output embedding dimension of size 64.
model.add(layers.Embedding(input_dim=1000, output_dim=64))

# Add a LSTM layer with 128 internal units.
model.add(layers.LSTM(128))

# Add a Dense layer with 10 units.
model.add(layers.Dense(10))

model.summary()

x_train = list()
y_train = list()
x_test = list()
y_test = list()
i = 0
parsed = False
for file in os.listdir('D:\\voices\\data'):
    if len(x_test) < 10:
        if i == 0:
            buffer = []
            f = open('D:\\voices\\data\\'+file)
            buffer.append(f.read())
            f.close()
        elif i == 1:
            f = open('D:\\voices\\data\\'+file)
            buffer.append(f.read())
            f.close()
            x_test.append(buffer)
        elif i == 2:
            f = open('D:\\voices\\data\\'+file)
            y_test.append(f.read())
            f.close()
    else:
        if i == 0:
            buffer = []
            f = open('D:\\voices\\data\\'+file)
            buffer.append(f.read())
            f.close()
        elif i == 1:
            f = open('D:\\voices\\data\\'+file)
            buffer.append(f.read())
            f.close()
            x_train.append(buffer)
        elif i == 2:
            f = open('D:\\voices\\data\\'+file)
            y_train.append(f.read())
            f.close()
    if i < 2:
        i += 1
    else:
        i = 0