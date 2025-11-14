import numpy as np
import pandas as pd
from sklearn.preprocessing import StandardScaler, MinMaxScaler
from sklearn.metrics import accuracy_score, precision_score, recall_score, confusion_matrix
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
import seaborn as sns

# ============================================
#               PREPROCESSING
# ============================================

def load_csv(path, target_col, dropna=True):
    df = pd.read_csv(path)
    if dropna:
        df = df.dropna()
    if target_col not in df.columns:
        raise ValueError(f"Target '{target_col}' not in CSV.")
    return df


def preprocess_features(df, target_col, scaler_type="standard"):
    df = df.copy()
    y = df[target_col].values
    X = df.drop(columns=[target_col]).values.astype(float)

    # Scaling
    if scaler_type == "standard":
        scaler = StandardScaler()
        X = scaler.fit_transform(X)
    elif scaler_type == "minmax":
        scaler = MinMaxScaler()
        X = scaler.fit_transform(X)
    else:
        raise ValueError("Scaler must be 'standard' or 'minmax'")

    return X, y, scaler


def add_intercept(X):
    return np.hstack([np.ones((X.shape[0], 1)), X])


# ============================================
#         SIGMOID NEURON (Logistic)
# ============================================

def sigmoid(z):
    return 1 / (1 + np.exp(-z))


def train_sigmoid_neuron(X, y, lr=0.1, epochs=500):
    w = np.zeros(X.shape[1])

    for _ in range(epochs):
        z = np.dot(X, w)
        y_hat = sigmoid(z)

        gradient = np.dot((y_hat - y), X) / len(y)
        w -= lr * gradient

    return w


def predict_sigmoid(X, w, threshold=0.5):
    return (sigmoid(np.dot(X, w)) >= threshold).astype(int)


# ============================================
#         ONE VS ALL FRAMEWORK
# ============================================

def train_one_vs_all(X, y, lr, epochs):
    classes = np.unique(y)
    weights = {}

    for c in classes:
        y_binary = (y == c).astype(int)
        w = train_sigmoid_neuron(X, y_binary, lr=lr, epochs=epochs)
        weights[c] = w

    return weights


def predict_one_vs_all(X, weights):
    scores = {c: sigmoid(np.dot(X, w)) for c, w in weights.items()}
    score_matrix = np.column_stack(list(scores.values()))
    class_labels = list(weights.keys())
    return np.array(class_labels)[np.argmax(score_matrix, axis=1)]


# ============================================
#         HYPERPARAMETER TUNING
# ============================================

def hyperparameter_tuning(X_train, y_train, X_val, y_val):
    lr_list = [0.001, 0.01, 0.1, 0.5]
    epoch_list = [300, 500, 800]

    best_acc = 0
    best_params = None
    best_weights = None

    for lr in lr_list:
        for ep in epoch_list:
            weights = train_one_vs_all(X_train, y_train, lr, ep)
            preds = predict_one_vs_all(X_val, weights)
            acc = accuracy_score(y_val, preds)

            print(f"LR={lr}, Epochs={ep}, Val Accuracy={acc:.4f}")

            if acc > best_acc:
                best_acc = acc
                best_params = (lr, ep)
                best_weights = weights

    print("\nBest Hyperparameters:")
    print("Learning rate:", best_params[0])
    print("Epochs:", best_params[1])
    print("Best Validation Accuracy:", best_acc)

    return best_weights, best_params


# ============================================
#      CLASS-WISE METRIC REPORTING
# ============================================

def report_metrics(y_true, y_pred, label="Dataset"):
    print(f"\n=== {label} METRICS ===")
    classes = np.unique(y_true)

    print("Accuracy:", accuracy_score(y_true, y_pred))

    print("Precision (per class):", precision_score(y_true, y_pred, average=None))
    print("Recall (per class):", recall_score(y_true, y_pred, average=None))

    cm = confusion_matrix(y_true, y_pred)
    print("\nConfusion Matrix:\n", cm)

    plt.figure(figsize=(6, 4))
    sns.heatmap(cm, annot=True, cmap="Blues", fmt="d")
    plt.title(f"Confusion Matrix - {label}")
    plt.xlabel("Predicted")
    plt.ylabel("Actual")
    plt.show()


# ============================================
#                 MAIN PROGRAM
# ============================================

# Load Iris dataset directly
from sklearn.datasets import load_iris
iris = load_iris()
df = pd.DataFrame(iris.data, columns=iris.feature_names)
df["target"] = iris.target

# Preprocess
X, y, scaler = preprocess_features(df, target_col="target")
X = add_intercept(X)

# Train/Val/Test Split: 70/10/20
X_train, X_temp, y_train, y_temp = train_test_split(
    X, y, test_size=0.30, random_state=42, stratify=y
)

X_val, X_test, y_val, y_test = train_test_split(
    X_temp, y_temp, test_size=2/3, random_state=42, stratify=y_temp
)

# Hyperparameter Tuning
best_weights, best_params = hyperparameter_tuning(X_train, y_train, X_val, y_val)

# Final Evaluation
train_preds = predict_one_vs_all(X_train, best_weights)
test_preds = predict_one_vs_all(X_test, best_weights)

# Metrics
report_metrics(y_train, train_preds, label="Training")
report_metrics(y_test, test_preds, label="Testing")
