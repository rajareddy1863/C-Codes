from scipy.io import wavfile
import numpy as np
from sklearn import preprocessing
import os, struct, keras
from keras.utils import np_utils
from keras.models import Sequential
from keras.layers.core import Dense, Dropout, Activation
from keras.optimizers import SGD
import matplotlib.pyplot as plt

def extractFeatures(ind):
    global featSeq
    global labelSeq
    global position
    Fs, data = wavfile.read('DataSet/timitData/' + featSeq[ind] + '.wav')
    data_len = len(data)

    trainFeature = data[0:nStack * nS]

    minLen = 0
    maxLen = nS
    featMat = np.array(list(data[minLen:maxLen]))
    labelMat = np.array([-1])
    minLen = minLen + nO
    maxLen = maxLen + nO
    while maxLen < len(data):
        featMat = np.concatenate((featMat,list(data[minLen:maxLen])))
        minLen = minLen + nO
        maxLen = maxLen + nO
    featMat_len = featMat.size / nS
    begin = featMat[0:nS]
    end = featMat[-nS:]
    for i in range((nStack-1)/2):
        featMat = np.concatenate((begin,featMat))
        featMat = np.concatenate((featMat,end))
    for i in range(featMat_len):
        trainFeature = np.concatenate((trainFeature, list(featMat[(i)*nS:(i + nStack)*nS])))
        labelMat = np.concatenate((labelMat, [int(labelSeq[position + i][2])]))
    trainFeature = trainFeature[nStack * nS:]
    labelMat = labelMat[1:]
    position += featMat_len

    return trainFeature, labelMat

#Reading feature sequence
with open("DataSet/featSequence","r") as myFile:
    featSeq = myFile.readlines()

#Reading label squence
with open("DataSet/label.txt","r") as myFile:
    labelSeq = myFile.readlines()

labelSeq = labelSeq[1:]
labelSeq = [x.strip() for x in labelSeq]
labelSeq = [ v for v in labelSeq if not v.startswith('Proc') ]
labelSeq = [x.split(' ') for x in labelSeq]
print len(labelSeq)
featSeq = [x.strip() for x in featSeq]

#25ms data with 10ms overlap
Fs = 16000
nS = int(25*1e-3*Fs)
nO = int(10*1e-3*Fs)
nStack = 7

trainSet = np.empty([1,nS*nStack])
labelSet = np.empty([1,1])
position = 0
for i in range(175):
    print 'Extracting feature ' + str(i)
    trainMat, labelMat = extractFeatures(i)
    trainMat = np.array(trainMat, dtype = 'float')
    nRows = trainMat.size / (nS * nStack)
    trainMat = np.reshape(trainMat, (nRows,nS*nStack))
    labelMat = np.reshape(labelMat, (nRows,1))
    trainSet = np.vstack([trainSet, trainMat])
    labelSet = np.vstack([labelSet, labelMat])

trainSet = trainSet[1:,:]
labelSet = labelSet[1:]
labelSet = np_utils.to_categorical(labelSet)

trainSet = preprocessing.scale(trainSet)
n_output = 183

model = Sequential()
model.add(Dense(25, input_dim = nS * nStack, init = 'uniform'))
model.add(Activation('relu'))
model.add(Dropout(0.5))
model.add(Dense(25, init = 'uniform'))
model.add(Activation('relu'))
model.add(Dropout(0.5))
model.add(Dense(25, init = 'uniform'))
model.add(Activation('relu'))
model.add(Dropout(0.5))
model.add(Dense(n_output, init = 'uniform'))
model.add(Activation('relu'))

sgd = SGD(lr = 0.1, decay = 1e-6, momemtum = 0.9, nesterov = True)
model.compile(loss='categorical_crossentropy', optimizer=sgd)

model.fit(trainSet, labelSet, nb_epoch = 5, batch_size = 64, validation_split = 0.1)

##for layer in model.layers:
##    weights = layer.get_weights() # list of numpy arrays
##    print layer
weight = model.layers[0].get_weights()
weight_1 = weight[0][:,0]
f = open('myfile0.txt','w')
[f.write(str(w) + '\n') for w in weight_1]

weight_2 = weight[0][:,1]
f = open('myfile1.txt','w')
[f.write(str(w) + '\n') for w in weight_2]

weight_3 = weight[0][:,2]
f = open('myfile2.txt','w')
[f.write(str(w) + '\n') for w in weight_3]

weight_4 = weight[0][:,3]
f = open('myfile3.txt','w')
[f.write(str(w) + '\n') for w in weight_4]
