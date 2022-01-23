
import numpy as np
import tensorflow as tf

model = tf.keras.Sequential([
    tf.keras.layers.Dense(5, input_dim=2, activation="sigmoid")
    ])

# model.compile()

# model.fit()

# model.evaluate()

# model.predict()