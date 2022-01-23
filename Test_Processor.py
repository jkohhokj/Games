import tensorflow as tf
#make model
#   make cnn for matrix set
#   make rnn for phoenetic recognition 
#   ^ find out which layers to use
#   choose optimizer
#   compile model
#   make a loss function
#prepare dataset
#   change text to phonetics
#   change phnoetics to numbers
#   apply ctc beaming

#train model
#model.fit()
#   model.evaluate()
#make a prediction
f = open('D:\\voices\\data\\19-198-0002.MFCC.txt')
file = f.read()
print(len(file))
for vector in file:
    print(vector)
    print(len(vector))