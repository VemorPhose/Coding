import numpy as np
import pandas as pd
from sklearn.datasets import load_iris
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import KFold
from sklearn.metrics import accuracy_score, precision_score, recall_score, confusion_matrix

# ---------------------------------------
#           Utility functions
# ---------------------------------------

def sigmoid(z):
    return 1 / (1 + np.exp(-z))


def soft_one_hot(y, num_classes):
    """Convert labels to one-hot."""
    onehot = np.zeros((len(y), num_classes))
    for i, v in enumerate(y):
        onehot[i, v] = 1
    return onehot


# ---------------------------------------
#  Single-Layer Perceptron (Sigmoid neurons)
# ---------------------------------------

def train_slp(X, y_onehot, lr=0.1, epochs=500):
    n_samples, n_features = X.shape
    n_classes = y_onehot.shape[1]

    # Weight matrix: (features × classes)
    W = np.zeros((n_features, n_classes))

    for _ in range(epochs):
        z = np.dot(X, W)                 # (n_samples × n_classes)
        y_hat = sigmoid(z)               # sigmoid activation

        # Gradient for multi-output layer:
        grad = np.dot(X.T, (y_hat - y_onehot)) / n_samples

        W -= lr * grad

    return W


def predict_slp(X, W):
    probs = sigmoid(np.dot(X, W))
    return np.argmax(probs, axis=1)


# ---------------------------------------
#      Evaluation Utilities
# ---------------------------------------

def compute_class_metrics(y_true, y_pred, label="Fold"):
    print(f"\n=== {label} Metrics ===")
    print("Accuracy:", accuracy_score(y_true, y_pred))
    print("Precision (per class):", precision_score(y_true, y_pred, average=None, zero_division=0))
    print("Recall (per class):", recall_score(y_true, y_pred, average=None, zero_division=0))
    print("Confusion Matrix:\n", confusion_matrix(y_true, y_pred))


# ---------------------------------------
#                MAIN
# ---------------------------------------

# Load Iris dataset
iris = load_iris()
X = iris.data
y = iris.target
num_classes = len(np.unique(y))

# Scale features
scaler = StandardScaler()
X = scaler.fit_transform(X)

# Add intercept
X = np.hstack([np.ones((X.shape[0], 1)), X])

# 5-fold cross validation
kf = KFold(n_splits=5, shuffle=True, random_state=42)

all_acc = []
all_prec = []
all_rec = []

fold = 1

for train_idx, test_idx in kf.split(X):
    print(f"\n==================== Fold {fold} ====================")

    X_train, X_test = X[train_idx], X[test_idx]
    y_train, y_test = y[train_idx], y[test_idx]

    # One-hot encoding for SLP
    y_train_onehot = soft_one_hot(y_train, num_classes)

    # Train Single-Layer Perceptron
    W = train_slp(X_train, y_train_onehot, lr=0.1, epochs=700)

    # Predict
    y_pred = predict_slp(X_test, W)

    # Metrics
    acc = accuracy_score(y_test, y_pred)
    prec = precision_score(y_test, y_pred, average=None, zero_division=0)
    rec = recall_score(y_test, y_pred, average=None, zero_division=0)

    all_acc.append(acc)
    all_prec.append(prec)
    all_rec.append(rec)

    compute_class_metrics(y_test, y_pred, label=f"Fold {fold}")

    fold += 1

# ---------------------------------------
#          OVERALL METRICS
# ---------------------------------------

print("\n\n========== OVERALL 5-FOLD RESULTS ==========")
print("Overall Accuracy:", np.mean(all_acc))
print("Class-wise Precision:\n", np.mean(np.vstack(all_prec), axis=0))
print("Class-wise Recall:\n", np.mean(np.vstack(all_rec), axis=0))
