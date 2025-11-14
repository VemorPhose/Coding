"""
Modular ML template (functional, no classes)
Allowed libraries: sklearn.covariance, sklearn.metrics, sklearn.model_selection,
sklearn.preprocessing, matplotlib, seaborn, numpy, pandas

Linear Regression (OLS) implementation + preprocessing + evaluation + plots.

Author: (template)
"""

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.preprocessing import StandardScaler, MinMaxScaler
from sklearn.model_selection import train_test_split, KFold
from sklearn.metrics import mean_squared_error, mean_absolute_error, r2_score

# -------------------------
# === Data utilities ======
# -------------------------

def load_csv(path, target_col, dropna=True):
    """
    Read CSV into pandas DataFrame and optionally drop NA rows.
    Returns DataFrame.
    """
    df = pd.read_csv(path)
    if dropna:
        df = df.dropna()
    if target_col not in df.columns:
        raise ValueError(f"Target column '{target_col}' not found in {path}")
    return df


def infer_categorical_columns(df, explicit_cats=None):
    """
    Return list of categorical columns.
    If explicit_cats provided (list), return that after checking they exist.
    Otherwise infer object/category dtype columns.
    """
    if explicit_cats:
        missing = [c for c in explicit_cats if c not in df.columns]
        if missing:
            raise ValueError(f"Categorical columns not found in dataframe: {missing}")
        return explicit_cats
    else:
        cats = df.select_dtypes(include=['object', 'category']).columns.tolist()
        return cats


def preprocess_features(
    df,
    target_col,
    categorical_cols=None,
    one_hot=True,
    scaler_type='standard',
    drop_first=False
):
    """
    - Splits df into X (numpy array) and y (numpy array)
    - One-hot encodes categorical columns (pandas.get_dummies) if one_hot True.
    - Scales features using StandardScaler or MinMaxScaler depending on scaler_type.
      Both options are shown below; change `scaler_type` to 'minmax' to use MinMaxScaler.
    - Returns: X (np.ndarray), y (np.ndarray), feature_names (list), scaler_object
    """
    df = df.copy()
    if categorical_cols is None:
        categorical_cols = infer_categorical_columns(df)

    # Separate features and target
    y = df[target_col].values
    X_df = df.drop(columns=[target_col])

    # One-hot encoding
    if one_hot and len(categorical_cols) > 0:
        X_df = pd.get_dummies(X_df, columns=categorical_cols, drop_first=drop_first)
    else:
        # If not one-hot encoding, ensure categorical labels are encoded numerically:
        for col in categorical_cols:
            if col in X_df.columns:
                X_df[col] = X_df[col].astype('category').cat.codes

    feature_names = X_df.columns.tolist()
    X = X_df.values.astype(float)

    # Scaling - choose one. Default is StandardScaler.
    if scaler_type == 'standard':
        scaler = StandardScaler()
        X = scaler.fit_transform(X)
    elif scaler_type == 'minmax':
        scaler = MinMaxScaler()
        X = scaler.fit_transform(X)
    else:
        raise ValueError("scaler_type must be 'standard' or 'minmax'")

    return X, y, feature_names, scaler


def add_intercept(X):
    """Add a column of ones as intercept term. X is numpy array."""
    ones = np.ones((X.shape[0], 1))
    return np.hstack([ones, X])


# -------------------------
# === OLS implementation ==
# -------------------------

def fit_ols_closed_form(X, y, add_bias=True, ridge_lambda=0.0):
    """
    Fit OLS using pseudo-inverse (stable) with optional ridge regularization.
    X: numpy array of shape (n_samples, n_features) (without intercept unless add_bias=True)
    y: numpy array shape (n_samples,)
    add_bias: if True, add intercept column
    ridge_lambda: if >0, performs ridge-like regularization (lambda * I) on weights excluding intercept
    Returns: weights vector w of length (n_features + 1 if add_bias else n_features)
    """
    X_mat = X.copy()
    if add_bias:
        X_mat = add_intercept(X_mat)  # now shape (n, d+1)

    # Closed form with optional ridge:
    # w = (X^T X + lambda * I)^(-1) X^T y
    # For stability use pinv if lambda == 0
    if ridge_lambda and ridge_lambda > 0.0:
        # Regularize only non-intercept terms if bias present
        d = X_mat.shape[1]
        I = np.eye(d)
        if add_bias:
            I[0, 0] = 0.0  # do not regularize intercept
        A = X_mat.T.dot(X_mat) + ridge_lambda * I
        w = np.linalg.solve(A, X_mat.T.dot(y))
    else:
        w = np.linalg.pinv(X_mat).dot(y)

    return w


def predict_ols(X, w, add_bias=True):
    """
    Predict using weight vector w. If add_bias assumed when training, it will add intercept term.
    """
    X_mat = X.copy()
    if add_bias:
        X_mat = add_intercept(X_mat)
    return X_mat.dot(w)


# -------------------------
# === Evaluation ==========
# -------------------------

def regression_metrics(y_true, y_pred):
    """
    Compute MSE, RMSE, MAE, R2. Returns dict.
    """
    mse = mean_squared_error(y_true, y_pred)
    rmse = np.sqrt(mse)
    mae = mean_absolute_error(y_true, y_pred)
    r2 = r2_score(y_true, y_pred)
    return {'mse': mse, 'rmse': rmse, 'mae': mae, 'r2': r2}


# -------------------------
# === Plotting ===========
# -------------------------

def plot_pred_vs_actual(y_true, y_pred, title="Predicted vs Actual", save_path=None):
    plt.figure(figsize=(6, 6))
    sns.scatterplot(x=y_true, y=y_pred, alpha=0.7)
    lims = [min(y_true.min(), y_pred.min()), max(y_true.max(), y_pred.max())]
    plt.plot(lims, lims, linestyle='--', linewidth=1, label='y = x')
    plt.xlabel('Actual')
    plt.ylabel('Predicted')
    plt.title(title)
    plt.legend()
    plt.grid(True)
    if save_path:
        plt.savefig(save_path, bbox_inches='tight')
    plt.show()


def plot_residuals_vs_pred(y_true, y_pred, title="Residuals vs Predicted", save_path=None):
    residuals = y_true - y_pred
    plt.figure(figsize=(7, 4))
    sns.scatterplot(x=y_pred, y=residuals, alpha=0.6)
    plt.axhline(0, color='k', linestyle='--', linewidth=1)
    plt.xlabel('Predicted')
    plt.ylabel('Residual (Actual - Predicted)')
    plt.title(title)
    plt.grid(True)
    if save_path:
        plt.savefig(save_path, bbox_inches='tight')
    plt.show()


def plot_residuals_hist(y_true, y_pred, title="Residuals Histogram", save_path=None, bins=30):
    residuals = y_true - y_pred
    plt.figure(figsize=(6, 4))
    sns.histplot(residuals, bins=bins, kde=True)
    plt.xlabel('Residual (Actual - Predicted)')
    plt.title(title)
    if save_path:
        plt.savefig(save_path, bbox_inches='tight')
    plt.show()


# -------------------------
# === Wrapper & CV ========
# -------------------------

def train_test_ols_pipeline(
    X_train, y_train, X_test, y_test,
    add_bias=True, ridge_lambda=0.0,
    do_plots=True, save_plots_prefix=None
):
    """
    Train OLS on training data, predict on test set, evaluate and optionally plot.
    Returns dict with weights, y_pred_test, metrics.
    """
    w = fit_ols_closed_form(X_train, y_train, add_bias=add_bias, ridge_lambda=ridge_lambda)
    y_pred = predict_ols(X_test, w, add_bias=add_bias)
    metrics = regression_metrics(y_test, y_pred)

    if do_plots:
        title_prefix = save_plots_prefix if save_plots_prefix else "ols"
        plot_pred_vs_actual(y_test, y_pred, title=f"{title_prefix} - Pred vs Actual")
        plot_residuals_vs_pred(y_test, y_pred, title=f"{title_prefix} - Residuals vs Pred")
        plot_residuals_hist(y_test, y_pred, title=f"{title_prefix} - Residuals Histogram")

    return {'weights': w, 'y_pred': y_pred, 'metrics': metrics}


def cross_validate_ols(
    X, y, k=5, add_bias=True, ridge_lambda=0.0, random_state=42, shuffle=True
):
    """
    Perform K-Fold cross-validation with OLS. Returns per-fold metrics and aggregated stats.
    """
    kf = KFold(n_splits=k, shuffle=shuffle, random_state=random_state)
    fold_metrics = []
    fold_index = 0
    for train_idx, val_idx in kf.split(X):
        X_tr, X_val = X[train_idx], X[val_idx]
        y_tr, y_val = y[train_idx], y[val_idx]
        w = fit_ols_closed_form(X_tr, y_tr, add_bias=add_bias, ridge_lambda=ridge_lambda)
        y_val_pred = predict_ols(X_val, w, add_bias=add_bias)
        metrics = regression_metrics(y_val, y_val_pred)
        metrics['fold'] = fold_index
        fold_metrics.append(metrics)
        fold_index += 1

    # aggregate
    agg = {}
    for m in ['mse', 'rmse', 'mae', 'r2']:
        vals = np.array([fm[m] for fm in fold_metrics])
        agg[f'{m}_mean'] = vals.mean()
        agg[f'{m}_std'] = vals.std()

    return {'fold_metrics': fold_metrics, 'aggregate': agg}


# -------------------------
# === Example main ========
# -------------------------

def example_usage():
    """
    Example usage — change DATA_PATH and TARGET_COL to match your CSV.
    """
    # ---------- USER SETTINGS ----------
    DATA_PATH = "data.csv"      # <-- change to your CSV path
    TARGET_COL = "target"       # <-- change to your target column name
    CATEGORICAL_COLS = None     # e.g. ['gender', 'city'] or None to auto-detect
    TEST_SIZE = 0.2
    RANDOM_STATE = 42
    SCALER = 'standard'         # 'standard' or 'minmax'
    # -----------------------------------

    # Load
    df = load_csv(DATA_PATH, TARGET_COL)

    # Preprocess
    X, y, feature_names, scaler_obj = preprocess_features(
        df,
        target_col=TARGET_COL,
        categorical_cols=CATEGORICAL_COLS,
        one_hot=True,
        scaler_type=SCALER,
        drop_first=False
    )

    # Split
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=TEST_SIZE, random_state=RANDOM_STATE
    )

    # Train / Eval
    result = train_test_ols_pipeline(
        X_train, y_train, X_test, y_test,
        add_bias=True, ridge_lambda=0.0,
        do_plots=True, save_plots_prefix="ols_example"
    )

    print("Test metrics:")
    for k, v in result['metrics'].items():
        print(f"  {k}: {v:.6f}")

    # Cross-validate
    cv_res = cross_validate_ols(X, y, k=5, add_bias=True, ridge_lambda=0.0)
    print("\nCross-validation (5-fold) aggregate:")
    for k, v in cv_res['aggregate'].items():
        print(f"  {k}: {v:.6f}")

    # Example: access learned weights and feature names (intercept is first)
    w = result['weights']
    print("\nLearned coefficients (intercept first):")
    for idx, coef in enumerate(w):
        name = "intercept" if idx == 0 else feature_names[idx - 1]
        print(f"  {name}: {coef:.6f}")


if __name__ == "__main__":
    # To run the example, uncomment the line below and ensure DATA_PATH & TARGET_COL are set.
    # example_usage()
    print("Template loaded. Call `example_usage()` after editing DATA_PATH and TARGET_COL to run a demo.")
