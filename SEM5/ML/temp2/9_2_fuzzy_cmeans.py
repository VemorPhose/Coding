# ================================================================
# IMPORTS
# ================================================================
import numpy as np
import pandas as pd
from sklearn.preprocessing import StandardScaler, MinMaxScaler
import matplotlib.pyplot as plt
import seaborn as sns

# ================================================================
# PREPROCESSING (your template)
# ================================================================
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


# ================================================================
# DISTANCE MATRIX
# ================================================================
def pairwise_distance(X, C):
    """
    X: (N, d)
    C: (k, d)
    Returns distance matrix: (k, N)
    """
    diff = X[None, :, :] - C[:, None, :]
    dist = np.sqrt(np.sum(diff**2, axis=2))
    return dist


# ================================================================
# FUZZY C-MEANS ALGORITHM (MANUAL)
# ================================================================
def initialize_membership(N, k):
    # Random membership values, normalized per sample
    U = np.random.rand(k, N)
    U = U / np.sum(U, axis=0, keepdims=True)
    return U


def update_centroids(X, U, m):
    """
    X: (N, d)
    U: (k, N)
    """
    um = U ** m
    numerator = um @ X
    denominator = np.sum(um, axis=1, keepdims=True)
    C = numerator / denominator
    return C


def update_membership(dist, m):
    """
    dist: (k, N)
    """
    # If any distance = 0, assign full membership to that cluster
    zero_idx = np.where(dist == 0)
    if zero_idx[0].size > 0:
        U = np.zeros_like(dist)
        for i in range(len(zero_idx[0])):
            cluster = zero_idx[0][i]
            sample = zero_idx[1][i]
            U[cluster, sample] = 1
        return U

    power = 2 / (m - 1)
    inv = (1.0 / dist) ** power
    U = inv / np.sum(inv, axis=0, keepdims=True)
    return U


def objective_function(dist, U, m):
    return np.sum((U ** m) * (dist ** 2))


def fuzzy_c_means(X, k=3, m=2.0, max_iter=200, tol=1e-4):
    """
    Manual fuzzy C-means.
    """
    N, d = X.shape
    U = initialize_membership(N, k)
    prev_obj = None

    obj_values = []

    for iteration in range(max_iter):
        # Update centroids
        C = update_centroids(X, U, m)

        # Distances
        dist = pairwise_distance(X, C)

        # Update memberships
        U = update_membership(dist, m)

        # Compute objective function
        obj = objective_function(dist, U, m)
        obj_values.append(obj)

        # Check convergence
        if prev_obj is not None and abs(prev_obj - obj) < tol:
            break

        prev_obj = obj

    return C, U, obj_values


# ================================================================
# HARD ASSIGNMENT
# ================================================================
def get_hard_labels(U):
    return np.argmax(U, axis=0)


# ================================================================
# VISUALIZATIONS
# ================================================================
def plot_objective(obj_values):
    plt.figure(figsize=(6, 4))
    plt.plot(obj_values, marker='o')
    plt.title("Fuzzy C-Means Objective Function")
    plt.xlabel("Iteration")
    plt.ylabel("Objective Value")
    plt.grid(True)
    plt.show()


def visualize_clusters(X, labels, C):
    if X.shape[1] > 2:
        X_vis = X[:, :2]
        C_vis = C[:, :2]
    else:
        X_vis = X
        C_vis = C

    plt.figure(figsize=(7, 6))
    sns.scatterplot(x=X_vis[:, 0], y=X_vis[:, 1], hue=labels, palette="tab10")
    plt.scatter(C_vis[:, 0], C_vis[:, 1], s=200, c='black', marker='X', label='Centroids')
    plt.legend()
    plt.title("Fuzzy C-Means Clustering")
    plt.show()


# ================================================================
# MAIN
# ================================================================
def main():
    df = load_csv("your_dataset.csv", target_col="y")
    X, y, feat_names, scaler = preprocess_features(df, "y")

    # FCM parameters
    k = 3
    m = 2.0
    max_iter = 150

    C, U, obj_values = fuzzy_c_means(X, k=k, m=m, max_iter=max_iter)

    labels = get_hard_labels(U)

    plot_objective(obj_values)
    visualize_clusters(X, labels, C)


# Run
main()
