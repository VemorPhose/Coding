import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.preprocessing import OneHotEncoder, StandardScaler, MinMaxScaler
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, confusion_matrix


# =========================================================
# =============== COMMON PREPROCESSING CODE ===============
# =========================================================

def load_data(filepath, target_column):
    """
    Reads a CSV file and separates features and target.
    """
    df = pd.read_csv(filepath)

    X = df.drop(columns=[target_column])
    y = df[target_column].values.reshape(-1, 1)

    return X, y


def preprocess_features(X):
    """
    One-hot encodes categorical features and scales numerical features.
    """
    categorical_cols = X.select_dtypes(include=['object', 'category']).columns.tolist()
    numeric_cols = X.select_dtypes(include=[np.number]).columns.tolist()

    # ---- One Hot Encoding ----
    if len(categorical_cols) > 0:
        encoder = OneHotEncoder(sparse_output=False, drop='first')
        X_cat = encoder.fit_transform(X[categorical_cols])
    else:
        X_cat = np.array([]).reshape(len(X), 0)

    # ---- Scaling ----
    scaler = StandardScaler()        # Standard Scaler (comment/uncomment)
    # scaler = MinMaxScaler()        # MinMax Scaler

    if len(numeric_cols) > 0:
        X_num = scaler.fit_transform(X[numeric_cols])
    else:
        X_num = np.array([]).reshape(len(X), 0)

    # ---- Combine Features ----
    X_processed = np.hstack([X_num, X_cat])

    return X_processed


def split_data(X, y, test_size=0.2, random_seed=42):
    """
    Splits dataset into train and test sets.
    """
    return train_test_split(X, y, test_size=test_size, random_state=random_seed)


# =========================================================
# =============== LOGISTIC REGRESSION CORE ===============
# =========================================================

def sigmoid(z):
    return 1 / (1 + np.exp(-z))


def compute_loss(y_true, y_pred):
    """
    Binary cross-entropy loss.
    """
    epsilon = 1e-10
    return -np.mean(y_true * np.log(y_pred + epsilon) + (1 - y_true) * np.log(1 - y_pred + epsilon))


def compute_gradient(X, y, y_pred):
    """
    Gradient for logistic regression using full dataset (Batch GD).
    """
    m = len(y)
    return (1 / m) * X.T @ (y_pred - y)


# =========================================================
# =============== GRADIENT DESCENT VARIANTS ===============
# =========================================================

def batch_gradient_descent(X, y, lr, epochs):
    m, n = X.shape
    W = np.zeros((n, 1))
    b = 0
    losses = []

    for _ in range(epochs):
        y_pred = sigmoid(X @ W + b)
        loss = compute_loss(y, y_pred)
        losses.append(loss)

        grad_W = compute_gradient(X, y, y_pred)
        grad_b = np.mean(y_pred - y)

        W -= lr * grad_W
        b -= lr * grad_b

    return W, b, losses


def mini_batch_gradient_descent(X, y, lr, epochs, batch_size):
    m, n = X.shape
    W = np.zeros((n, 1))
    b = 0
    losses = []

    for _ in range(epochs):
        idx = np.random.permutation(m)
        X_shuffled = X[idx]
        y_shuffled = y[idx]

        for i in range(0, m, batch_size):
            X_batch = X_shuffled[i:i + batch_size]
            y_batch = y_shuffled[i:i + batch_size]

            y_pred = sigmoid(X_batch @ W + b)
            loss = compute_loss(y_batch, y_pred)
            losses.append(loss)

            grad_W = compute_gradient(X_batch, y_batch, y_pred)
            grad_b = np.mean(y_pred - y_batch)

            W -= lr * grad_W
            b -= lr * grad_b

    return W, b, losses


def stochastic_gradient_descent(X, y, lr, epochs):
    m, n = X.shape
    W = np.zeros((n, 1))
    b = 0
    losses = []

    for _ in range(epochs):
        for i in range(m):
            xi = X[i:i+1]
            yi = y[i:i+1]

            y_pred = sigmoid(xi @ W + b)
            loss = compute_loss(yi, y_pred)
            losses.append(loss)

            grad_W = xi.T @ (y_pred - yi)
            grad_b = np.mean(y_pred - yi)

            W -= lr * grad_W
            b -= lr * grad_b

    return W, b, losses


# =========================================================
# =============== WRAPPER MODEL FUNCTION =================
# =========================================================

def logistic_regression_train(X, y, mode="batch", lr=0.01, epochs=1000, batch_size=32):
    """
    mode: "batch", "mini-batch", "sgd"
    """
    if mode == "batch":
        return batch_gradient_descent(X, y, lr, epochs)

    elif mode == "mini-batch":
        return mini_batch_gradient_descent(X, y, lr, epochs, batch_size)

    elif mode == "sgd":
        return stochastic_gradient_descent(X, y, lr, epochs)

    else:
        raise ValueError("Invalid mode. Choose from 'batch', 'mini-batch', 'sgd'.")


# =========================================================
# ============== MAIN TRAINING + EVALUATION ==============
# =========================================================

def evaluate_logistic_regression(W, b, X_test, y_test):
    y_pred_prob = sigmoid(X_test @ W + b)
    y_pred = (y_pred_prob >= 0.5).astype(int)

    acc = accuracy_score(y_test, y_pred)
    prec = precision_score(y_test, y_pred)
    rec = recall_score(y_test, y_pred)
    f1 = f1_score(y_test, y_pred)

    return acc, prec, rec, f1, y_pred, y_pred_prob


def plot_losses(losses, title="Loss Curve"):
    plt.figure(figsize=(8, 5))
    plt.plot(losses)
    plt.title(title)
    plt.xlabel("Iterations")
    plt.ylabel("Loss")
    plt.grid()
    plt.show()


# =========================================================
# =============== FULL EXECUTION EXAMPLE =================
# =========================================================

if __name__ == "__main__":
    # ---- Load & Preprocess ----
    X, y = load_data("data.csv", target_column="target")
    X = preprocess_features(X)
    X_train, X_test, y_train, y_test = split_data(X, y)

    # ---- Train Model ----
    W, b, losses = logistic_regression_train(
        X_train, y_train,
        mode="mini-batch",
        lr=0.01,
        epochs=300,
        batch_size=32
    )

    # ---- Evaluate ----
    acc, prec, rec, f1, y_pred, y_prob = evaluate_logistic_regression(W, b, X_test, y_test)

    print("\n=== METRICS ===")
    print("Accuracy :", acc)
    print("Precision:", prec)
    print("Recall   :", rec)
    print("F1 Score :", f1)

    # ---- Plot Loss ----
    plot_losses(losses, "Mini-Batch Gradient Descent Loss")


