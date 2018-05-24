from sklearn.decomposition import PCA
from sklearn import datasets
from sklearn import preprocessing
from sklearn.svm import SVC
from sklearn.model_selection import train_test_split
from sklearn.neural_network import MLPClassifier
from sklearn.datasets.samples_generator import make_classification
import pickle
import tensorflow as tf
import numpy as np

# load data
iris_data = datasets.load_iris()
iris_data_X = iris_data.data
iris_data_Y = iris_data.target


# generate data
X_Gen, Y_Gen = make_classification(n_samples=1000, n_features=5, n_classes=2)
for _x, _y in zip(X_Gen, Y_Gen):
    pass
    # print "label: " + str(_y), "properity: " + str(_x)

# input X and Output Y
X_data = X_Gen
Y_data = Y_Gen

# process data
proceeHandle = preprocessing.StandardScaler().fit(X_data)
X_data_process = proceeHandle.transform(X_data)


# normalization
X_data_norm = preprocessing.normalize(X_data, norm='l2')

# one-hot
oneHot_data_ = [[0, 0, 3], [1, 1, 0], [0, 2, 1], [1, 0, 2]]
oneHotHandle = preprocessing.OneHotEncoder().fit(oneHot_data_)
oneHot_data = oneHotHandle.transform(oneHot_data_).toarray()

# use PCA
mypca = PCA(n_components=0.95, whiten=False)
mypca.fit(X_data)
X_data_pca = mypca.transform(X_data)
print(mypca.explained_variance_ratio_)
print(mypca.explained_variance_)

# split data
train_X, test_X, train_Y, test_Y = train_test_split(X_data_pca, \
                                                    Y_data,\
                                                    test_size=0.3,\
                                                    random_state = 25)

# use svm
model = SVC(C=1.0, kernel='rbf', degree=3, max_iter=1500)
model.fit(train_X, train_Y)
print("SVM score: ", model.score(test_X, test_Y))
print("SVM params: ", model.get_params())

# use MLPClassifier
model1 = MLPClassifier(hidden_layer_sizes=(16, 32, 8),\
                      activation='relu',\
                      solver='adam', max_iter=1500)
model1.fit(train_X, train_Y)
print("MLPClassifier score: ", model1.score(test_X, test_Y))
print("MLPClassifier params: ", model1.get_params())


# save model
with open("model.pickle", "wb") as f:
    pickle.dump(model, f, 2)

# save some data
with open("iris_data.pickle", "wb") as f:
    pickle.dump(test_X, f)
    pickle.dump(test_Y, f)
