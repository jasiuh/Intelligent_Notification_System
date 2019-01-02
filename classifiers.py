import pandas as pd
import numpy as np

#Read the data with Pandas
data = pd.read_csv('DATA_TRAIN_TEST.csv')

#Store the data in a dataframe
df = pd.DataFrame(data)

#Print the first five rows of the data
df.head()

# Import resample for oversampling and undersampling.
from sklearn.utils import resample
# Separate majority and minority classes
zero = df[df.ALARM==0]
one = df[df.ALARM==1]

#Need to uncomment the one that will be used!
############UPSAMPLE ONES####################

# Upsample ones to match number of zeros
#one_upsampled = resample(one, replace=True,n_samples=9712,random_state=1)
# Combine majority class with upsampled minority class
#upsample = pd.concat([zero, one_upsampled])
# Display new class counts
#upsample.ALARM.value_counts()

############DOWNSAMPLE ZEROS#################
# Downsample zeros to match number of ones
zero_downsampled = resample(zero, replace=True,n_samples=669,random_state=1)
# Combine majority class with upsampled minority class
downsample = pd.concat([one, zero_downsampled])
# Display new class counts
downsample.ALARM.value_counts()
#df.ALARM.value_counts()


#Split dataset into training and testing sets.
from sklearn.model_selection import train_test_split

#Need to uncomment the one that will be used!
############UPSAMPLE ONES#####################################
#Y = upsample.ALARM
#X = upsample.drop('ALARM', axis=1)  
##############################################################
#############DOWNSAMPLE ZEROS#################################
Y = downsample.ALARM
X = downsample.drop('ALARM', axis=1)   
##############################################################

# Test size = 20% of dataset (other 80% is for training)
X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.2, random_state=5)

print "Training set samples: ", len(X_train)
print "Testing set samples:  ", len(X_test)


#Classification Algorithms
#Decision Tree
from sklearn import tree
tree = tree.DecisionTreeClassifier(criterion='entropy', splitter='best', random_state=5, class_weight='balanced')
tree.fit(X_train,Y_train)
Y_predict_tree = tree.predict(X_test)

#K-Nearest Neighbor
from sklearn.neighbors import KNeighborsClassifier
knn = KNeighborsClassifier(n_neighbors = 1, weights='distance')
knn.fit(X_train,Y_train)
Y_predict_knn = knn.predict(X_test)


#Confusion Matrix
from sklearn.metrics import confusion_matrix
confusion_tree = confusion_matrix(Y_test, Y_predict_tree)
print confusion_tree
print ""
confusion_knn = confusion_matrix(Y_test, Y_predict_knn)
print confusion_knn


#Cross Validation
from sklearn.model_selection import cross_val_score
score_tree = cross_val_score(tree, X_train, Y_train, cv=10)
print score_tree
print "Decision Tree Mean: ", score_tree.mean()
print''
score_knn = cross_val_score(knn, X_train, Y_train, cv=10)
print score_knn
print "KNN Mean: ", score_knn.mean()


#Validation dataset
#Read the data with Pandas
validation_data = pd.read_csv('DATA_VALIDATION.csv')
#Store the data in a dataframe
df_val = pd.DataFrame(validation_data)
y2 = ['ALARM']
x2 = ['BL1','BL2','BL3','SL1','SL2','SL3']
Y2 = df_val[y2]
X2 = df_val[x2]
df_val['ALARM'].value_counts()


#Call the two models to predict on the validation data using .predict()
tree_val_predictions = tree.predict(X2)
knn_val_predictions = knn.predict(X2)

score_tree_validation = cross_val_score(tree, X2, Y2, cv=10)
print "10-Fold Cross Validation Scores for Tree: ", score_tree_validation
print "Decision Tree Mean: ", score_tree_validation.mean()
print ""
score_knn_validation = cross_val_score(knn, X2, Y2, cv=10)
print "10-Fold Cross Validation Scores for KNN: ", score_knn_validation
print "KNN Mean: ", score_knn_validation.mean()
print ""

validation_confusion_tree = confusion_matrix(Y2, tree_val_predictions)
print "Confusion Matrix: Decision Tree"
print validation_confusion_tree
print ""
validation_confusion_knn = confusion_matrix(Y2, knn_val_predictions)
print "Confusion Matrix: KNN"
print validation_confusion_knn
print ""


#Here we can get a visual of the Decision Tree by copying the output and 
#pasting into https://dreampuf.github.io/GraphvizOnline/

from sklearn.externals.six import StringIO   
from sklearn.tree import export_graphviz
import pydot

plot = StringIO()
export_graphviz(tree, out_file=plot, filled=True, rounded=True, special_characters=True)

print plot.getvalue()


#Save the model using Pickle
import pickle
with open('knn_pickle', 'wb') as knn_model:
    pickle.dump(knn,knn_model)
