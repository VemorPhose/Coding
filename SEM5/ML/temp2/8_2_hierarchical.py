# ================================================================
# IMPORTS
# ================================================================
import numpy as np
import pandas as pd
from sklearn.preprocessing import StandardScaler, MinMaxScaler
import matplotlib.pyplot as plt
import seaborn as sns

# ================================================================
# PREPROCESSING (your template reused verbatim)
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


def add_intercept(X):
    return np.hstack([np.ones((X.shape[0], 1)), X])


# ================================================================
# HIERARCHICAL CLUSTERING IMPLEMENTATION (MANUAL)
# ================================================================

def pairwise_dist_matrix(X):
    """Compute full NxN distance matrix."""
    n = X.shape[0]
    dist = np.zeros((n, n))
    for i in range(n):
        diff = X - X[i]
        dist[i] = np.sqrt(np.sum(diff * diff, axis=1))
    return dist


def linkage_distance(cluster1, cluster2, dist_mat, method):
    """
    Compute distance between two clusters (list of indices).
    method: 'single', 'complete', 'centroid'
    """
    if method == "single":
        # Minimum distance between any pair
        return np.min(dist_mat[np.ix_(cluster1, cluster2)])

    elif method == "complete":
        # Maximum distance
        return np.max(dist_mat[np.ix_(cluster1, cluster2)])

    elif method == "centroid":
        # Distance between centroids
        c1 = np.mean(dist_mat[cluster1][:, cluster1], axis=1).mean()
        c2 = np.mean(dist_mat[cluster2][:, cluster2], axis=1).mean()
        return abs(c1 - c2)

    else:
        raise ValueError("Invalid linkage method")


def hierarchical_clustering(X, method="single"):
    """
    Fully manual hierarchical clustering.
    Returns:
        merges: [(cluster1, cluster2, distance, new_cluster_size), ...]
    """
    n = X.shape[0]
    dist_mat = pairwise_dist_matrix(X)

    # Start with each point as a cluster
    clusters = {i: [i] for i in range(n)}

    # For dendrogram data
    merges = []
    current_cluster_id = n

    while len(clusters) > 1:
        keys = list(clusters.keys())
        best_pair = None
        best_dist = float("inf")

        # Find closest pair
        for i in range(len(keys)):
            for j in range(i + 1, len(keys)):
                c1, c2 = keys[i], keys[j]
                d = linkage_distance(clusters[c1], clusters[c2], dist_mat, method)

                if d < best_dist:
                    best_dist = d
                    best_pair = (c1, c2)

        # Merge
        c1, c2 = best_pair
        new_cluster = clusters[c1] + clusters[c2]

        merges.append((c1, c2, best_dist, len(new_cluster)))

        # Remove old clusters, add new one
        del clusters[c1]
        del clusters[c2]
        clusters[current_cluster_id] = new_cluster
        current_cluster_id += 1

    return merges


# ================================================================
# DENDROGRAM (manual)
# ================================================================
def plot_dendrogram(merges, labels=None, title="Dendrogram"):
    """
    Plot dendrogram manually from merge info.
    """
    fig, ax = plt.subplots(figsize=(10, 5))

    # Number of original points
    n = len(merges) + 1

    # Position each original point
    x_positions = {i: i for i in range(n)}
    heights = {}

    for merge in merges:
        c1, c2, height, size = merge

        x1 = x_positions[c1]
        x2 = x_positions[c2]

        xm = (x1 + x2) / 2
        x_positions[len(x_positions)] = xm
        heights[(c1, c2)] = height

        ax.plot([x1, x1], [0, height], c='k')
        ax.plot([x2, x2], [0, height], c='k')
        ax.plot([x1, x2], [height, height], c='k')

    ax.set_title(title)
    ax.set_xlabel("Data Point Index")
    ax.set_ylabel("Distance")
    plt.show()


# ================================================================
# CUTTING THE DENDROGRAM INTO K CLUSTERS
# ================================================================
def get_cluster_assignments(merges, k, n_points):
    """
    Assign points to clusters by cutting dendrogram.
    """
    clusters = {i: [i] for i in range(n_points)}

    next_cluster_id = n_points
    for c1, c2, height, size in merges:
        # if we already have exactly k clusters, stop merging
        if len(clusters) <= k:
            break
        merged = clusters[c1] + clusters[c2]
        del clusters[c1]
        del clusters[c2]
        clusters[next_cluster_id] = merged
        next_cluster_id += 1

    # Map each point to a cluster ID
    labels = np.zeros(n_points, dtype=int)
    for cluster_id, points in enumerate(clusters.values()):
        for p in points:
            labels[p] = cluster_id

    return labels


# ================================================================
# VISUALIZATION
# ================================================================
def visualize_clusters(X, labels):
    if X.shape[1] > 2:
        X_vis = X[:, :2]
    else:
        X_vis = X

    plt.figure(figsize=(7, 6))
    sns.scatterplot(x=X_vis[:, 0], y=X_vis[:, 1], hue=labels, palette="tab10")
    plt.title("Hierarchical Clustering Result")
    plt.show()


# ================================================================
# MAIN EXECUTION PIPELINE
# ================================================================
def main():
    df = load_csv("your_dataset.csv", target_col="y")
    X, y, feat_names, scaler = preprocess_features(df, "y")

    # Choose method: "single", "complete", "centroid"
    method = "single"

    merges = hierarchical_clustering(X, method=method)

    # Plot dendrogram
    plot_dendrogram(merges, title=f"Dendrogram ({method}-linkage)")

    # Choose K clusters
    k = 3
    labels = get_cluster_assignments(merges, k, X.shape[0])

    visualize_clusters(X, labels)


main()
