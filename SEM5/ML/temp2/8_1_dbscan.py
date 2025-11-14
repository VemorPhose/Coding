# ================================================================
# IMPORTS
# ================================================================
import numpy as np
import pandas as pd
from sklearn.preprocessing import StandardScaler, MinMaxScaler
from sklearn.metrics import silhouette_score
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
import seaborn as sns

# ================================================================
# DATA PREPROCESSING (common template)
# ================================================================
def load_data(path, target_column):
    df = pd.read_csv(path)
    return df

def preprocess_data(df, target_column):
    X = df.drop(columns=[target_column])
    y = df[target_column]

    # One-hot encoding
    X = pd.get_dummies(X, drop_first=True)

    # Scaling (choose one)
    scaler = StandardScaler()
    # scaler = MinMaxScaler()
    X_scaled = scaler.fit_transform(X)

    return X_scaled, y, X.columns


# ================================================================
# MANUAL DBSCAN IMPLEMENTATION
# ================================================================
def region_query(X, point_idx, eps):
    """
    Find all points within distance eps of point_idx.
    """
    distances = np.linalg.norm(X - X[point_idx], axis=1)
    neighbors = np.where(distances <= eps)[0]
    return neighbors


def expand_cluster(X, labels, point_idx, neighbors, cluster_id, eps, min_pts, visited):
    """
    Expand the cluster using neighbors.
    """
    labels[point_idx] = cluster_id

    i = 0
    while i < len(neighbors):
        n_idx = neighbors[i]

        if not visited[n_idx]:
            visited[n_idx] = True
            n_neighbors = region_query(X, n_idx, eps)

            # If core point, add neighbors to queue
            if len(n_neighbors) >= min_pts:
                neighbors = np.append(neighbors, n_neighbors)

        # If not yet assigned to a cluster
        if labels[n_idx] == -1:
            labels[n_idx] = cluster_id

        i += 1


def dbscan_manual(X, eps, min_pts):
    """
    Fully manual DBSCAN.
    """
    n = X.shape[0]
    labels = np.full(n, -1)
    visited = np.full(n, False)

    cluster_id = 0

    for point_idx in range(n):

        if visited[point_idx]:
            continue

        visited[point_idx] = True
        neighbors = region_query(X, point_idx, eps)

        # Not enough neighbors → noise
        if len(neighbors) < min_pts:
            labels[point_idx] = -1
        else:
            expand_cluster(X, labels, point_idx, neighbors, cluster_id, eps, min_pts, visited)
            cluster_id += 1

    return labels


# ================================================================
# GRID SEARCH OVER eps AND minPts
# ================================================================
def grid_search_dbscan(X, minpts_list, eps_list):
    best_score = -1
    best_params = None
    best_labels = None

    for minpts in minpts_list:
        for eps in eps_list:

            labels = dbscan_manual(X, eps, minpts)

            # Must have ≥2 clusters, and ignore runs where everything is noise
            unique_clusters = set(labels)
            if len(unique_clusters) <= 1:
                continue

            # noise label -1 should be removed for silhouette
            mask = labels != -1
            if np.sum(mask) < 2:
                continue

            try:
                score = silhouette_score(X[mask], labels[mask])
            except:
                continue

            print(f"minPts={minpts}, eps={eps}, score={score}")

            if score > best_score:
                best_score = score
                best_labels = labels
                best_params = (eps, minpts)

    return best_params, best_labels, best_score


# ================================================================
# MANUAL K-DISTANCE GRAPH
# ================================================================
def compute_k_distances(X, k):
    n = X.shape[0]
    k_dists = np.zeros(n)

    for i in range(n):
        distances = np.linalg.norm(X - X[i], axis=1)
        distances = np.sort(distances)
        k_dists[i] = distances[k]  # k-th nearest neighbor (0-based indexing)

    return np.sort(k_dists)


def plot_k_distance_graph(k_distances, k):
    plt.figure(figsize=(8, 5))
    plt.plot(k_distances)
    plt.title(f"{k}-Distance Graph (manual)")
    plt.xlabel("Points sorted by distance")
    plt.ylabel(f"{k}-NN Distance")
    plt.grid(True)
    plt.show()


# ================================================================
# VISUALIZATION
# ================================================================
def visualize_clusters(X, labels):
    if X.shape[1] > 2:
        X_vis = X[:, :2]  # take first 2 features
    else:
        X_vis = X

    plt.figure(figsize=(7, 6))
    sns.scatterplot(x=X_vis[:, 0], y=X_vis[:, 1],
                    hue=labels, palette="tab10")
    plt.title("Manual DBSCAN Clusters")
    plt.show()


# ================================================================
# MAIN WORKFLOW
# ================================================================
def main():
    # 1. Load and preprocess
    df = load_data("your_dataset.csv", target_column="y")
    X, y, feat_names = preprocess_data(df, "y")

    # 2. Search space
    minpts_list = [3, 4, 5, 6]
    eps_list = [0.2, 0.4, 0.6, 0.8, 1.0]

    # 3. Grid search
    best_params, best_labels, best_score = grid_search_dbscan(
        X, minpts_list, eps_list
    )

    print("\nBest Params:", best_params)
    print("Best Silhouette Score:", best_score)

    best_eps, best_minpts = best_params

    # 4. K-distance graph
    k_distances = compute_k_distances(X, best_minpts)
    plot_k_distance_graph(k_distances, best_minpts)

    # (Optional) user refines eps manually from graph
    refined_eps = best_eps

    # 5. Final DBSCAN run
    final_labels = dbscan_manual(X, refined_eps, best_minpts)

    # 6. Plot clusters
    visualize_clusters(X, final_labels)


# Run script
main()
