# import pickle
import cPickle as pickle

#load data
with open("iris_data.pickle", "rb") as f:
    iris_data_X = pickle.load(f)
    iris_data_Y = pickle.load(f)
# load model
with open("model.pickle", "rb") as f:
    model_bak = pickle.load(f)

print(model_bak)
print(model_bak.predict(iris_data_X))
print(model_bak.score(iris_data_X, iris_data_Y))
print(iris_data_Y)