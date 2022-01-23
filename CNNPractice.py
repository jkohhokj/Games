import numpy as np
import tensorflow as tf
from sklearn.model_selection import train_test_split
from tensorflow import keras
from tensorflow.keras import layers
from random import random

# array([[0.1, 0.2], [0.2, 0.2]])
def generate_dataset(num_samples, test_size):
    x = np.array([[random()/2 for _ in range(2)] for _ in range(num_samples)])
    y = np.array([[i[0] + i[1]] for i in x])
    x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=test_size)
    return x_train, x_test, y_train, y_test

if __name__ == '__main__':
    x_train, x_test, y_train, y_test = generate_dataset(1000, 0.1)
    #print('x_test',x_test)
    #print('y_test',y_test)

    # 2 -> 5 -> 1
    model = tf.keras.Sequential([
        tf.keras.layers.Dense(5, input_dim=2, activation="sigmoid"),
        tf.keras.layers.Dense(1, activation="sigmoid")
    ]) # Sequential = forward propagation?
    optimizer = tf.keras.optimizers.SGD(learning_rate=0.3)
    model.compile(optimizer=optimizer, loss="MSE")

    # train model
    model.fit(x_train, y_train, epochs=200)

    # evaluate model
    print('\nModel Evaluation')

    model.evaluate(x_test, y_test, verbose=1)

    # make prediction
    data = np.array([[0.1, 0.2], [0.2, 0.2]])
    predictions = model.predict(data)

    print('\nSome predictions:')

    for d, p in zip(data, predictions):
        print(d[0], '+', d[1], '=', p)