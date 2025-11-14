import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.preprocessing import OneHotEncoder, StandardScaler, MinMaxScaler
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score


# =========================================================
# =============== COMMON PREPROCESSING CODE ===============
# =========================================================

def load_data(filepath, target_column):
    df = pd.read_csv(filepath)

    X = df.drop(columns=[target_column])
    y = df[target_column].values.reshape(-1, 1)

    return X, y


def preprocess_features(X):
    categorical_cols = X.select_dtypes(include=['object', 'category']).columns.tolist()
    numeric_cols = X.select_dtypes(include=[np.number]).columns.tolist()

    # ---- One Hot Encoding ----
    if len(categorical_cols) > 0:
        encoder = OneHotEncoder(sparse_output=False, drop='first')
        X_cat = encoder.fit_transform(X[categorical_cols])
    else:
        X_cat = np.array([]).reshape(len(X), 0)

    # ---- Scaling ----
    scaler = StandardScaler()        # Standard Scaler
    # scaler = MinMaxScaler()        # MinMax Scaler

    if len(numeric_cols) > 0:
        X_num = scaler.fit_transform(X[numeric_cols])
    else:
        X_num = np.array([]).reshape(len(X), 0)

    return np.hstack([X_num, X_cat])


def one_hot_encode_labels(y):
    """
    Convert y labels into one-hot encoded matrix (for softmax)
    """
    classes = np.unique(y)
    class_count = len(classes)

    onehot = np.zeros((len(y), class_count))
    for idx, cls in enumerate(classes):
        onehot[y.flatten() == cls, idx] = 1

    return onehot, classes


def split_data(X, y, test_size=0.2, seed=42):
    return train_test_split(X, y, test_size=test_size, random_state=seed)


# =========================================================
# =============== SOFTMAX LOGISTIC REGRESSION ============
# =========================================================

def softmax(z):
    """
    Numerically stable softmax
    """
    z -= np.max(z, axis=1, keepdims=True)
    exp_z = np.exp(z)
    return exp_z / np.sum(exp_z, axis=1, keepdims=True)


def cross_entropy_loss(y_true, y_pred):
    eps = 1e-10
    return -np.mean(np.sum(y_true * np.log(y_pred + eps), axis=1))


def compute_gradients(X, y_true, y_pred):
    m = X.shape[0]
    grad_W = (1 / m) * (X.T @ (y_pred - y_true))
    grad_b = (1 / m) * np.sum((y_pred - y_true), axis=0)
    return grad_W, grad_b


# =========================================================
# =============== TRAINING WRAPPER FUNCTION ===============
# =========================================================

def train_softmax_regression(X, y_onehot, lr=0.01, epochs=500):
    m, n = X.shape
    k = y_onehot.shape[1]   # number of classes

    W = np.zeros((n, k))
    b = np.zeros((1, k))
    losses = []

    for _ in range(epochs):
        logits = X @ W + b
        y_pred = softmax(logits)

        loss = cross_entropy_loss(y_onehot, y_pred)
        losses.append(loss)

        grad_W, grad_b = compute_gradients(X, y_onehot, y_pred)

        W -= lr * grad_W
        b -= lr * grad_b

    return W, b, losses


# =========================================================
# ===================== PREDICTION ========================
# =========================================================

def predict_softmax(W, b, X):
    logits = X @ W + b
    prob = softmax(logits)
    preds = np.argmax(prob, axis=1)
    return preds, prob


# =========================================================
# ======================= PLOTTING ========================
# =========================================================

def plot_losses(losses, title="Softmax Regression Loss Curve"):
    plt.figure(figsize=(8, 5))
    plt.plot(losses)
    plt.title(title)
    plt.xlabel("Epoch")
    plt.ylabel("Loss")
    plt.grid()
    plt.show()


# =========================================================
# ================= FULL EXECUTION EXAMPLE ================
# =========================================================

if __name__ == "__main__":
    # ---- Load ----
    X_df, y_raw = load_data("data.csv", target_column="target")

    # ---- Preprocess features ----
    X = preprocess_features(X_df)

    # ---- One hot encode labels ----
    y_onehot, classes = one_hot_encode_labels(y_raw)

    # ---- Split ----
    X_train, X_test, y_train, y_test_raw = split_data(X, y_onehot)

    # Keep raw labels too for metrics
    y_test = np.argmax(y_test_raw, axis=1)

    # ---- Train ----
    W, b, losses = train_softmax_regression(
        X_train, y_train,
        lr=0.01,
        epochs=500
    )

    # ---- Predict ----
    y_pred, y_prob = predict_softmax(W, b, X_test)

    # ---- Metrics ----
    acc = accuracy_score(y_test, y_pred)
    prec = precision_score(y_test, y_pred, average="macro")
    rec = recall_score(y_test, y_pred, average="macro")
    f1 = f1_score(y_test, y_pred, average="macro")

    print("\n=== METRICS ===")
    print("Accuracy :", acc)
    print("Precision:", prec)
    print("Recall   :", rec)
    print("F1 Score :", f1)

    # ---- Plot Loss ----
    plot_losses(losses)
