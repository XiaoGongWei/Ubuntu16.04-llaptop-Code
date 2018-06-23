# import pickle
# import cPickle as pickle
import pickle

#load data
with open("iris_data.pickle", "rb") as f:
    X_data = pickle.load(f)
    Y_data = pickle.load(f)
# load model
with open("model.pickle", "rb") as f:
    model_bak = pickle.load(f)

print("mode_bak: ", model_bak)
# print "mode predict: ", model_bak.predict(X_data)
# print "mode True: ", Y_data
print("pridict score: ", model_bak.score(X_data, Y_data))

