"""
Linear Regression via Gradient Descent (Functional, No Classes)
Includes full preprocessing pipeline identical to previous OLS template.
"""

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.preprocessing import StandardScaler, MinMaxScaler
from sklearn.model_selection import train_test_split, KFold
from sklearn.metrics import (
    mean_squared_error, mean_absolute_error, r2_score
)

# ---------------------------------------------------------------------
# === DATA PREPROCESSING (FULLY COPIED FROM PREVIOUS SNIPPET) =========
# ---------------------------------------------------------------------

def load_csv(path, target_col, dropna=True):
    df = pd.read_csv(path)
    if dropna:
        df = df.dropna()
    if target_col not in df.columns:
        raise ValueError(f"Target column '{target_col}' not found in {path}")
    return df


def infer_categorical_columns(df, explicit_cats=None):
    if explicit_cats:
        missing = [c for c in explicit_cats if c not in df.columns]
        if missing:
            raise ValueError(f"Categorical columns not found in dataframe: {missing}")
        return explicit_cats
    return df.select_dtypes(include=["object", "category"]).columns.tolist()


def preprocess_features(
    df,
    target_col,
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

    # One hot encoding
    if one_hot and len(categorical_cols) > 0:
        X_df = pd.get_dummies(X_df, columns=categorical_cols, drop_first=drop_first)
    else:
        for col in categorical_cols:
            if col in X_df:
                X_df[col] = X_df[col].astype("category").cat.codes

    feature_names = X_df.columns.tolist()
    X = X_df.values.astype(float)

    # Scaling
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

# ---------------------------------------------------------------------
# === GRADIENT DESCENT LINEAR REGRESSION ==============================
# ---------------------------------------------------------------------

def compute_cost(X, y, w):
    """
    Mean Squared Error cost.
    X: (n_samples, n_features)
    w: (n_features,)
    """
    n = len(y)
    preds = X @ w
    return (1/(2*n)) * np.sum((preds - y)**2)


def gradient_descent(
    X, y,
    lr=0.01,
    n_iters=1000,
    add_bias=True,
    verbose=False
):
    """
    Perform gradient descent to fit linear regression.
    - X: numpy array WITHOUT intercept column
    - If add_bias=True, intercept column is added automatically
    """
    if add_bias:
        X = add_intercept(X)

    n, d = X.shape
    w = np.zeros(d)  # initialize weights
    cost_history = []

    for it in range(n_iters):
        preds = X @ w
        grad = (1/n) * (X.T @ (preds - y))
        w -= lr * grad

        cost = compute_cost(X, y, w)
        cost_history.append(cost)

        if verbose and it % max(1, n_iters//10) == 0:
            print(f"Iter {it:4d} | Cost = {cost:.6f}")

    return w, cost_history


def predict_gd(X, w, add_bias=True):
    if add_bias:
        X = add_intercept(X)
    return X @ w

# ---------------------------------------------------------------------
# === METRICS ==========================================================
# ---------------------------------------------------------------------

def regression_metrics(y_true, y_pred):
    mse = mean_squared_error(y_true, y_pred)
    rmse = np.sqrt(mse)
    mae = mean_absolute_error(y_true, y_pred)
    r2 = r2_score(y_true, y_pred)
    return {"mse": mse, "rmse": rmse, "mae": mae, "r2": r2}

# ---------------------------------------------------------------------
# === PLOT FUNCTIONS ===================================================
# ---------------------------------------------------------------------

def plot_cost(cost_history):
    plt.figure(figsize=(6,4))
    plt.plot(cost_history)
    plt.title("Gradient Descent Cost Curve")
    plt.xlabel("Iteration")
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


def plot_residuals(y_true, y_pred, title="Residuals vs Predicted"):
    residuals = y_true - y_pred
    plt.figure(figsize=(7,4))
    sns.scatterplot(x=y_pred, y=residuals, alpha=0.6)
    plt.axhline(0, ls='--', c='k')
    plt.xlabel("Predicted")
    plt.ylabel("Residual")
    plt.title(title)
    plt.grid(True)
    plt.show()


# ---------------------------------------------------------------------
# === WRAPPER PIPELINE ================================================
# ---------------------------------------------------------------------

def train_test_gd_pipeline(
    X_train, y_train,
    X_test, y_test,
    lr=0.01,
    n_iters=1000,
    add_bias=True,
    verbose=False,
    do_plots=True
):
    """Train → Predict → Metrics → Plots"""
    w, cost_history = gradient_descent(
        X_train, y_train,
        lr=lr,
        n_iters=n_iters,
        add_bias=add_bias,
        verbose=verbose
    )

    y_pred = predict_gd(X_test, w, add_bias=add_bias)
    metrics = regression_metrics(y_test, y_pred)

    if do_plots:
        plot_cost(cost_history)
        plot_pred_vs_actual(y_test, y_pred, "GD - Predicted vs Actual")
        plot_residuals(y_test, y_pred)

    return {
        "weights": w,
        "y_pred": y_pred,
        "metrics": metrics,
        "cost_history": cost_history
    }

# ---------------------------------------------------------------------
# === EXAMPLE MAIN ====================================================
# ---------------------------------------------------------------------

def example_usage():
    DATA_PATH = "data.csv"
    TARGET_COL = "target"
    CATEGORICAL_COLS = None
    TEST_SIZE = 0.2
    RANDOM_STATE = 42
    SCALER = "standard"  # or 'minmax'

    df = load_csv(DATA_PATH, TARGET_COL)

    X, y, feat_names, scaler_obj = preprocess_features(
        df, target_col=TARGET_COL,
        categorical_cols=CATEGORICAL_COLS,
        one_hot=True,
        scaler_type=SCALER
    )

    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=TEST_SIZE, random_state=RANDOM_STATE
    )

    result = train_test_gd_pipeline(
        X_train, y_train, X_test, y_test,
        lr=0.01,
        n_iters=2000,
        add_bias=True,
        verbose=True,
        do_plots=True
    )

    print("Test Metrics:")
    for k, v in result["metrics"].items():
        print(f"{k}: {v:.6f}")

    print("\nWeights (Intercept first):")
    print(result["weights"])


if __name__ == "__main__":
    print("Gradient Descent LR Template Loaded. Call example_usage() to test.")
