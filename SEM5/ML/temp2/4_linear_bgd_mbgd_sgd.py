"""
Linear Regression – Batch, Mini-Batch, Stochastic Gradient Descent
Functional, Modular, No Classes

Includes full preprocessing code (copied 100% from previous templates).
"""

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.preprocessing import StandardScaler, MinMaxScaler
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error, mean_absolute_error, r2_score

# ============================================================================
# === FULL PREPROCESSING PIPELINE (COPIED EXACTLY FROM PREVIOUS TEMPLATES) ===
# ============================================================================

def load_csv(path, target_col, dropna=True):
    df = pd.read_csv(path)
    if dropna:
        df = df.dropna()
    if target_col not in df.columns:
        raise ValueError(f"Target column '{target_col}' not found.")
    return df


def infer_categorical_columns(df, explicit_cats=None):
    if explicit_cats:
        missing = [c for c in explicit_cats if c not in df.columns]
        if missing:
            raise ValueError(f"Categorical columns missing: {missing}")
        return explicit_cats
    return df.select_dtypes(include=["object", "category"]).columns.tolist()


def preprocess_features(
    df, target_col,
    categorical_cols=None,
    one_hot=True,
    scaler_type="standard",
    drop_first=False
):
    df = df.copy()

    if categorical_cols is None:
        categorical_cols = infer_categorical_columns(df)

    y = df[target_col].values
    X_df = df.drop(columns=[target_col])

    if one_hot and len(categorical_cols) > 0:
        X_df = pd.get_dummies(X_df, columns=categorical_cols, drop_first=drop_first)
    else:
        for col in categorical_cols:
            if col in X_df:
                X_df[col] = X_df[col].astype("category").cat.codes

    feature_names = X_df.columns.tolist()
    X = X_df.values.astype(float)

    if scaler_type == "standard":
        scaler = StandardScaler()
        X = scaler.fit_transform(X)
    elif scaler_type == "minmax":
        scaler = MinMaxScaler()
        X = scaler.fit_transform(X)
    else:
        raise ValueError("scaler_type must be 'standard' or 'minmax'")

    return X, y, feature_names, scaler


def add_intercept(X):
    return np.hstack([np.ones((X.shape[0], 1)), X])


# ============================================================================
# === COST + METRICS =========================================================
# ============================================================================

def compute_cost(X, y, w):
    n = len(y)
    return (1 / (2 * n)) * np.sum((X @ w - y) ** 2)


def regression_metrics(y_true, y_pred):
    mse = mean_squared_error(y_true, y_pred)
    rmse = np.sqrt(mse)
    mae = mean_absolute_error(y_true, y_pred)
    r2 = r2_score(y_true, y_pred)
    return {"mse": mse, "rmse": rmse, "mae": mae, "r2": r2}


def predict(X, w, add_bias=True):
    if add_bias:
        X = add_intercept(X)
    return X @ w


# ============================================================================
# === BATCH GRADIENT DESCENT (BGD) ===========================================
# ============================================================================

def batch_gradient_descent(X, y, lr=0.01, n_iters=1000, verbose=False):
    X = add_intercept(X)
    n, d = X.shape
    w = np.zeros(d)
    cost_history = []

    for it in range(n_iters):
        preds = X @ w
        grad = (1 / n) * (X.T @ (preds - y))
        w -= lr * grad

        cost = compute_cost(X, y, w)
        cost_history.append(cost)

        if verbose and it % max(1, n_iters // 10) == 0:
            print(f"Batch GD | Iter {it} | Cost {cost:.6f}")

    return w, cost_history


# ============================================================================
# === MINI-BATCH GRADIENT DESCENT (MBGD) =====================================
# ============================================================================

def mini_batch_gradient_descent(
    X, y,
    lr=0.01,
    n_iters=1000,
    batch_size=32,
    verbose=False
):
    X = add_intercept(X)
    n, d = X.shape
    w = np.zeros(d)
    cost_history = []

    for it in range(n_iters):
        perm = np.random.permutation(n)
        X_shuffled = X[perm]
        y_shuffled = y[perm]

        for start in range(0, n, batch_size):
            end = start + batch_size
            X_batch = X_shuffled[start:end]
            y_batch = y_shuffled[start:end]

            preds = X_batch @ w
            grad = (1 / len(y_batch)) * (X_batch.T @ (preds - y_batch))
            w -= lr * grad

        cost = compute_cost(X, y, w)
        cost_history.append(cost)

        if verbose and it % max(1, n_iters // 10) == 0:
            print(f"Mini-Batch GD | Iter {it} | Cost {cost:.6f}")

    return w, cost_history


# ============================================================================
# === STOCHASTIC GRADIENT DESCENT (SGD) ======================================
# ============================================================================

def stochastic_gradient_descent(
    X, y,
    lr=0.01,
    n_iters=1000,
    verbose=False
):
    X = add_intercept(X)
    n, d = X.shape
    w = np.zeros(d)
    cost_history = []

    for it in range(n_iters):
        perm = np.random.permutation(n)
        X_shuffled = X[perm]
        y_shuffled = y[perm]

        for i in range(n):
            xi = X_shuffled[i:i+1]
            yi = y_shuffled[i]

            preds = xi @ w
            grad = (preds - yi) * xi.flatten()
            w -= lr * grad

        cost = compute_cost(X, y, w)
        cost_history.append(cost)

        if verbose and it % max(1, n_iters // 10) == 0:
            print(f"Stochastic GD | Iter {it} | Cost {cost:.6f}")

    return w, cost_history


# ============================================================================
# === PLOTTING ================================================================
# ============================================================================

def plot_cost(cost_history, title="Cost Curve"):
    plt.figure(figsize=(6,4))
    plt.plot(cost_history)
    plt.title(title)
    plt.xlabel("Iterations")
    plt.ylabel("Cost (MSE/2)")
    plt.grid(True)
    plt.show()


def plot_pred_vs_actual(y_true, y_pred, title="Predicted vs Actual"):
    plt.figure(figsize=(6,6))
    sns.scatterplot(x=y_true, y=y_pred, alpha=0.7)
    lims = [min(y_true.min(), y_pred.min()), max(y_true.max(), y_pred.max())]
    plt.plot(lims, lims, 'k--')
    plt.xlabel("Actual")
    plt.ylabel("Predicted")
    plt.title(title)
    plt.grid(True)
    plt.show()


def plot_residuals(y_true, y_pred, title="Residual Plot"):
    residuals = y_true - y_pred
    plt.figure(figsize=(6,4))
    sns.scatterplot(x=y_pred, y=residuals, alpha=0.6)
    plt.axhline(0, color='k', linestyle='--')
    plt.xlabel("Predicted")
    plt.ylabel("Residual")
    plt.title(title)
    plt.grid(True)
    plt.show()


# ============================================================================
# === WRAPPER API =============================================================
# ============================================================================

def train_test_pipeline(
    X_train, y_train,
    X_test, y_test,
    method="batch",       # "batch", "mini", "stochastic"
    lr=0.01,
    n_iters=1000,
    batch_size=32,
    verbose=False,
    do_plots=True
):
    if method == "batch":
        w, cost_history = batch_gradient_descent(
            X_train, y_train, lr, n_iters, verbose
        )
        title = "Batch Gradient Descent"

    elif method == "mini":
        w, cost_history = mini_batch_gradient_descent(
            X_train, y_train, lr, n_iters, batch_size, verbose
        )
        title = f"Mini-Batch Gradient Descent (batch={batch_size})"

    elif method == "stochastic":
        w, cost_history = stochastic_gradient_descent(
            X_train, y_train, lr, n_iters, verbose
        )
        title = "Stochastic Gradient Descent"

    else:
        raise ValueError("method must be 'batch', 'mini', or 'stochastic'")

    y_pred = predict(X_test, w)
    metrics = regression_metrics(y_test, y_pred)

    if do_plots:
        plot_cost(cost_history, title + " – Cost Curve")
        plot_pred_vs_actual(y_test, y_pred, title + " – Predictions")
        plot_residuals(y_test, y_pred, title + " – Residuals")

    return {
        "weights": w,
        "metrics": metrics,
        "y_pred": y_pred,
        "cost_history": cost_history
    }


# ============================================================================
# === EXAMPLE MAIN ============================================================
# ============================================================================

def example_usage():
    DATA_PATH = "data.csv"
    TARGET = "target"

    df = load_csv(DATA_PATH, TARGET)

    X, y, feature_names, scaler = preprocess_features(
        df, TARGET,
        categorical_cols=None,
        one_hot=True,
        scaler_type="standard"
    )

    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.2, random_state=42
    )

    result = train_test_pipeline(
        X_train, y_train, X_test, y_test,
        method="mini",      # batch / mini / stochastic
        lr=0.01,
        n_iters=200,
        batch_size=16,
        verbose=True
    )

    print("Test Metrics:")
    for k, v in result["metrics"].items():
        print(f"{k}: {v:.6f}")


if __name__ == "__main__":
    print("GD (Batch, Mini, Stochastic) Template Loaded. Call example_usage().")
