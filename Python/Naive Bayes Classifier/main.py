import numpy as np
from sklearn.preprocessing import KBinsDiscretizer
from sklearn.model_selection import train_test_split
from sklearn.base import BaseEstimator
from sklearn.base import ClassifierMixin


class NBC(BaseEstimator, ClassifierMixin):
    def __init__(self, X, y, laplace_correction=False):
        self._class_probs = {}  # P(Y = y)
        self._feature_probs = {}  # P(X = x | Y = y)
        self._X = X
        self._y = y
        self._laplace_correction = laplace_correction

    def fit(self):
        unique_classes, class_counts = np.unique(self._y, return_counts=True)
        total_samples = len(self._y)

        number_of_features = self._X.shape[1]
        for class_label, class_count in zip(unique_classes, class_counts):

            # P(Y = y)
            self._class_probs[class_label] = class_count / total_samples

            # P(X = x | Y = y)
            class_indexes = np.where(self._y == class_label)[0]
            class_data = self._X[class_indexes, :]

            for feature_index in range(number_of_features):
                unique_feature_values, feature_value_counts = np.unique(class_data[:, feature_index], return_counts=True)
                for value, count in zip(unique_feature_values, feature_value_counts):
                    if self._laplace_correction:
                        self._feature_probs[(feature_index, value, class_label)] = (count + 1) / (class_count + len(unique_feature_values))
                    else:
                        self._feature_probs[(feature_index, value, class_label)] = count / class_count

    def predict(self, X, log=False):
        predicted_classes = []

        if log:
            for sample in X:
                candidate_class = {'class_label': None, 'value': float('-inf')}

                for class_label, class_prob in self._class_probs.items():
                    y_star = np.log(class_prob)

                    for feature_index, feature_value in enumerate(sample):
                        y_star += np.log(self._feature_probs.get((feature_index, feature_value, class_label), 1e-10))

                    if y_star > candidate_class['value']:
                        candidate_class['class_label'] = class_label
                        candidate_class['value'] = y_star

                predicted_classes.append(candidate_class['class_label'])
        else:
            for sample in X:
                candidate_class = {'class_label': None, 'value': -1}

                for class_label, class_prob in self._class_probs.items():
                    y_star = class_prob

                    for feature_index, feature_value in enumerate(sample):
                        y_star *= self._feature_probs.get((feature_index, feature_value, class_label), 1e-10)

                    if y_star > candidate_class['value']:
                        candidate_class['class_label'] = class_label
                        candidate_class['value'] = y_star

                predicted_classes.append(candidate_class['class_label'])

        return np.array(predicted_classes)

    def predict_proba(self, X, log=False):
        predicted_classes_probs = []
        belonging_to_classes_probs = {}

        if log:
            for sample in X:
                likelihoods = {}
                sum_of_likelihoods = 0

                for class_label, class_prob in self._class_probs.items():
                    likelihood = np.log(class_prob)

                    for feature_index, feature_value in enumerate(sample):
                        likelihood += np.log(self._feature_probs.get((feature_index, feature_value, class_label), 1e-10))

                    sum_of_likelihoods += likelihood
                    likelihoods[class_label] = likelihood

                for class_label, likelihood in likelihoods.items():
                    prop = likelihood / sum_of_likelihoods
                    belonging_to_classes_probs[class_label] = prop

                predicted_classes_probs.append(belonging_to_classes_probs)
        else:
            for sample in X:
                likelihoods = {}
                sum_of_likelihoods = 0

                for class_label, class_prob in self._class_probs.items():
                    likelihood = class_prob

                    for feature_index, feature_value in enumerate(sample):
                        likelihood *= self._feature_probs.get((feature_index, feature_value, class_label), 1e-10)

                    sum_of_likelihoods += likelihood
                    likelihoods[class_label] = likelihood

                for class_label, likelihood in likelihoods.items():
                    prop = likelihood / sum_of_likelihoods
                    belonging_to_classes_probs[class_label] = prop

                predicted_classes_probs.append(belonging_to_classes_probs)

        return np.array(predicted_classes_probs)


def classification_accuracy(predicted_classes, true_classes):
    NP = np.count_nonzero(predicted_classes == true_classes)
    LZ = len(true_classes)
    accuracy = (NP / LZ) * 100
    accuracy = round(accuracy, 2)
    return str(accuracy) + ' %'



# Przeprowadzenie eksperymentów podstawowych:
print('EKSPERYMENTY PODSTAWOWE')

# (a)
data = np.genfromtxt('wine.data', delimiter=',')
X = data[:, 1:]
y = data[:, 0]
discretizer = KBinsDiscretizer(n_bins=4, encode='ordinal', strategy='uniform', subsample=None)
X_discrete = discretizer.fit_transform(X)
X_train, X_test, y_train, y_test = train_test_split(X_discrete, y)

# (b)
nbc = NBC(X_train, y_train, laplace_correction=False)
nbc.fit()

# (c)
predict = nbc.predict(X_test, log=False)

# (d)
print(f'Dokładność klasyfikatora bez poprawki LaPlace\'a wynosi: {classification_accuracy(predict, y_test)}')

# (e)
nbc = NBC(X_train, y_train, laplace_correction=True)
nbc.fit()
predict = nbc.predict(X_test, log=False)
print(f'Dokładność klasyfikatora z poprawką LaPlace\'a wynosi: {classification_accuracy(predict, y_test)}\n')

# (f)
for n in [4, 5, 7, 9, 11, 15, 20, 50, 100]:
    discretizer = KBinsDiscretizer(n_bins=n, encode='ordinal', strategy='uniform', subsample=None)
    X_discrete = discretizer.fit_transform(X)
    X_train, X_test, y_train, y_test = train_test_split(X_discrete, y, random_state=42)

    nbc = NBC(X_train, y_train, laplace_correction=True)
    nbc.fit()
    predict = nbc.predict(X_test, log=True)
    print(f'Dokładność klasyfikatora dla {n} przedziałów dyskretyzacji wynosi: {classification_accuracy(predict, y_test)}')

print('\n-------------------------------------------------------------------------------------------\n')

# Przeprowadzenie eksperymentów dodatkowych:
print('EKSPERYMENTY DODATKOWE')

# (a)
data = np.genfromtxt('iris.data', delimiter=',', dtype='str', encoding=None)
X = data[:, :-1].astype(float)
y = data[:, -1]

# (b)
discretizer = KBinsDiscretizer(n_bins=4, encode='ordinal', strategy='uniform', subsample=None)
X_discrete = discretizer.fit_transform(X)
X_train, X_test, y_train, y_test = train_test_split(X_discrete, y)

nbc = NBC(X_train, y_train, laplace_correction=False)
nbc.fit()

predict = nbc.predict(X_test, log=False)
print(f'Dokładność klasyfikatora bez poprawki LaPlace\'a wynosi: {classification_accuracy(predict, y_test)}')

nbc = NBC(X_train, y_train, laplace_correction=True)
nbc.fit()
predict = nbc.predict(X_test, log=False)
print(f'Dokładność klasyfikatora z poprawką LaPlace\'a wynosi: {classification_accuracy(predict, y_test)}\n')

for n in [4, 5, 7, 9, 11, 15, 20, 50, 100]:
    discretizer = KBinsDiscretizer(n_bins=n, encode='ordinal', strategy='uniform', subsample=None)
    X_discrete = discretizer.fit_transform(X)
    X_train, X_test, y_train, y_test = train_test_split(X_discrete, y, random_state=42)

    nbc = NBC(X_train, y_train, laplace_correction=True)
    nbc.fit()
    predict = nbc.predict(X_test, log=True)
    print(f'Dokładność klasyfikatora dla {n} przedziałów dyskretyzacji wynosi: {classification_accuracy(predict, y_test)}')

print()

# (c)
from sklearn.naive_bayes import CategoricalNB

for n in [4, 5, 7, 9, 11]:
    discretizer = KBinsDiscretizer(n_bins=n, encode='ordinal', strategy='uniform', subsample=None)
    X_discrete = discretizer.fit_transform(X)
    X_train, X_test, y_train, y_test = train_test_split(X_discrete, y, random_state=42)
    print('n = ', n)
    nbc = NBC(X_train, y_train, laplace_correction=True)
    nbc.fit()
    predict_nbc = nbc.predict(X_test, log=False)
    print(f'Dokładność własnego klasyfikatora wynosi: {classification_accuracy(predict, y_test)}')

    sklearn_nbc = CategoricalNB()
    sklearn_nbc.fit(X_train, y_train)
    predict_sklearn_nbc = sklearn_nbc.predict(X_test)
    print(f'Dokładność klasyfikatora z sklearn wynosi: {classification_accuracy(predict_sklearn_nbc, y_test)}')
