import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.preprocessing import OneHotEncoder, StandardScaler, MinMaxScaler
from sklearn.model_selection import train_test_split
from sklearn.metrics import pairwise_distances


# =========================================================
# =============== COMMON PREPROCESSING CODE ===============
# =========================================================

def load_data(filepath):
    df = pd.read_csv(filepath)
    return df


def preprocess_features(df):
    categorical_cols = df.select_dtypes(include=['object', 'category']).columns.tolist()
    numeric_cols = df.select_dtypes(include=[np.number]).columns.tolist()

    # --- One Hot Encoding ---
    if len(categorical_cols) > 0:
        encoder = OneHotEncoder(sparse_output=False, drop='first')
        X_cat = encoder.fit_transform(df[categorical_cols])
    else:
        X_cat = np.array([]).reshape(len(df), 0)

    # --- Scaling ---
    scaler = StandardScaler()
    # scaler = MinMaxScaler()

    if len(numeric_cols) > 0:
        X_num = scaler.fit_transform(df[numeric_cols])
    else:
        X_num = np.array([]).reshape(len(df), 0)

    # Combine
    X_processed = np.hstack([X_num, X_cat])
    return X_processed


# =========================================================
# ===================== K-MEANS CORE ======================
# =========================================================

def initialize_centroids(X, k):
    """
    Randomly picks k unique points from dataset as initial centroids.
    """
    indices = np.random.choice(X.shape[0], k, replace=False)
    return X[indices]


def assign_clusters(X, centroids):
    """
    Assign each point to the nearest centroid.
    """
    distances = pairwise_distances(X, centroids)
    return np.argmin(distances, axis=1)


def update_centroids(X, labels, k):
    """
    Recompute centroids by taking mean of assigned points.
    """
    new_centroids = []
    for cluster in range(k):
        points = X[labels == cluster]
        if len(points) == 0:
            # handle empty clusters by reinitializing
            new_centroids.append(X[np.random.randint(0, X.shape[0])])
        else:
            new_centroids.append(points.mean(axis=0))
    return np.vstack(new_centroids)


def kmeans(X, k, max_iters=100, tolerance=1e-4):
    """
    Full K-means algorithm (functional, no classes).
    """
    centroids = initialize_centroids(X, k)

    for _ in range(max_iters):
        old_centroids = centroids.copy()

        labels = assign_clusters(X, centroids)
        centroids = update_centroids(X, labels, k)

        shift = np.linalg.norm(centroids - old_centroids)
        if shift < tolerance:
            break

    return centroids, labels


# =========================================================
# =============== EVALUATION & VISUALIZATION =============
# =========================================================

def compute_within_cluster_sum_of_squares(X, labels, centroids):
    wcss = 0
    for cluster in range(len(centroids)):
        points = X[labels == cluster]
        wcss += np.sum((points - centroids[cluster]) ** 2)
    return wcss


def elbow_method(X, max_k=10):
    wcss_values = []

    for k in range(1, max_k + 1):
        centroids, labels = kmeans(X, k)
        wcss = compute_within_cluster_sum_of_squares(X, labels, centroids)
        wcss_values.append(wcss)

    plt.figure(figsize=(8, 5))
    plt.plot(range(1, max_k+1), wcss_values, marker='o')
    plt.title("Elbow Method (WCSS vs K)")
    plt.xlabel("Number of Clusters (k)")
    plt.ylabel("WCSS")
    plt.grid()
    plt.show()


def silhouette_score_manual(X, labels):
    """
    Manual silhouette score implementation using pairwise distances.
    Works because only sklearn.metrics is allowed.
    """
    distances = pairwise_distances(X, X)
    n = len(X)
    sil_scores = []

    for i in range(n):
        same_cluster = (labels == labels[i])
        other_clusters = (labels != labels[i])

        a = np.mean(distances[i][same_cluster]) if np.sum(same_cluster) > 1 else 0
        b = np.min([
            np.mean(distances[i][labels == c]) 
            for c in np.unique(labels) if c != labels[i]
        ])
        sil = (b - a) / max(a, b)
        sil_scores.append(sil)

    return np.mean(sil_scores)


def plot_clusters_2d(X, labels, centroids):
    """
    Plot only first 2 dimensions.
    """
    if X.shape[1] < 2:
        print("Cannot plot 2D — dataset has <2 dimensions.")
        return

    plt.figure(figsize=(7, 5))
    sns.scatterplot(x=X[:, 0], y=X[:, 1], hue=labels, palette="viridis")
    plt.scatter(centroids[:, 0], centroids[:, 1], s=300, c="red", marker="X", label="Centroids")
    plt.title("K-Means Cluster Visualization (2D)")
    plt.legend()
    plt.show()


# =========================================================
# ===================== FULL EXECUTION ====================
# =========================================================

if __name__ == "__main__":
    # --- Load ---
    df = load_data("data.csv")

    # --- Preprocess ---
    X = preprocess_features(df)

    # --- Run K-Means ---
    k = 3
    centroids, labels = kmeans(X, k)

    # --- Metrics ---
    wcss = compute_within_cluster_sum_of_squares(X, labels, centroids)
    silhouette = silhouette_score_manual(X, labels)

    print("WCSS:", wcss)
    print("Silhouette Score:", silhouette)

    # --- Visualize 2D (if dataset > 1 dimension) ---
    plot_clusters_2d(X, labels, centroids)

    # --- Elbow Plot ---
    elbow_method(X, max_k=10)
