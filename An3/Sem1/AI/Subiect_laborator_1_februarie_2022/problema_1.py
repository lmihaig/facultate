import numpy as np
from sklearn.metrics import confusion_matrix
from sklearn.svm import LinearSVC
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.metrics import accuracy_score, f1_score


dataPath = "data\\"

cifre_exemple = [np.loadtxt(dataPath + f"{i}.txt", "uint8", converters=float) for i in range(0, 10)]


train_data = [i for exemplu in cifre_exemple for i in exemplu[:75]]
train_labels = [i for i in range(0, 10) for _ in range(75)]

test_data = [i for exemplu in cifre_exemple for i in exemplu[75:]]
test_labels = [i for i in range(0, 10) for _ in range(25)]


model = LinearSVC(max_iter=5000)
model.fit(train_data, train_labels)
y_pred = model.predict(test_data)


label_vals = [i for i in range(10)]
conf_mat = confusion_matrix(test_labels, y_pred)
sns.heatmap(conf_mat, annot=True, fmt="d", xticklabels=label_vals, yticklabels=label_vals)
plt.ylabel("Actual")
plt.xlabel("Predicted")
plt.show()


y_pred = [x % 2 for x in y_pred]
test_labels = [x % 2 for x in test_labels]

label_vals = ["Par", "Impar"]
conf_mat = confusion_matrix(test_labels, y_pred)
sns.heatmap(conf_mat, annot=True, fmt="d", xticklabels=label_vals, yticklabels=label_vals)
plt.ylabel("Actual")
plt.xlabel("Predicted")
plt.show()

acc = accuracy_score(y_pred, test_labels)
f1 = f1_score(y_pred, test_labels)
print("Accuracy:", acc)
print("F1:", f1)


train_data = [i for exemplu in cifre_exemple for i in exemplu[:75]]
train_labels = [i % 2 for i in range(0, 10) for _ in range(75)]

test_data = [i for exemplu in cifre_exemple for i in exemplu[75:]]
test_labels = [i % 2 for i in range(0, 10) for _ in range(25)]


model = LinearSVC(max_iter=5000)
model.fit(train_data, train_labels)
y_pred = model.predict(test_data)


label_vals = ["Par", "Impar"]
conf_mat = confusion_matrix(test_labels, y_pred)
sns.heatmap(conf_mat, annot=True, fmt="d", xticklabels=label_vals, yticklabels=label_vals)
plt.ylabel("Actual")
plt.xlabel("Predicted")
plt.show()

acc = accuracy_score(y_pred, test_labels)
f1 = f1_score(y_pred, test_labels)
print("Accuracy:", acc)
print("F1:", f1)
