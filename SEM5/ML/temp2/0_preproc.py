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


