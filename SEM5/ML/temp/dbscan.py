import numpy as np
import pandas as pd

# --- Helper Function: Distance ---

def euclidean_distance(point1, point2):
    """
    Calculates the squared Euclidean distance between two points.
    Comparing squared distance to eps^2 is more efficient than
    calculating the square root.
    
    Args:
        point1 (np.array): First point (1D array, n_features).
        point2 (np.array): Second point (1D array, n_features).

    Returns:
        float: Squared Euclidean distance.
    """
    return np.sum((point1 - point2)**2)

# --- Subpart 1: Find Neighbors ---

def get_neighbors(X, point_index, eps_squared):
    """
    Finds all points in X that are within eps (using eps_squared) of the
    point at point_index.
    
    Args:
        X (np.array): The input data (n_samples, n_features).
        point_index (int): The index of the point to find neighbors for.
        eps_squared (float): The squared epsilon (radius) for the neighborhood.

    Returns:
        list: A list of indices of the neighboring points (including the
              point itself, as min_pts includes the point).
    """
    n_samples = X.shape[0]
    center_point = X[point_index]
    neighbors_indices = []
    
    for i in range(n_samples):
        # Calculate squared distance
        dist = euclidean_distance(center_point, X[i])
        
        # Check if the point is within the epsilon-neighborhood
        if dist <= eps_squared:
            neighbors_indices.append(i)
            
    return neighbors_indices

# --- Subpart 2: Expand Cluster ---

def expand_cluster(X, labels, point_index, cluster_id, eps_squared, min_pts, neighbors_of_start_point):
    """
    Expands a cluster from a starting core point.
    This function modifies the 'labels' array in-place.
    
    Args:
        X (np.array): The input data (n_samples, n_features).
        labels (np.array): Array of labels for each point (-2=Unclassified, -1=Noise, >=0=Cluster ID).
        point_index (int): The index of the core point to start expansion from.
        cluster_id (int): The new cluster ID to assign.
        eps_squared (float): The squared epsilon (radius) for the neighborhood.
        min_pts (int): The minimum number of points to form a dense region.
        neighbors_of_start_point (list): The pre-computed neighbors of the starting point.
    """
    
    # Label the starting core point
    labels[point_index] = cluster_id
    
    # Create a queue from the neighbors (making a copy)
    # We will process every point in this list, and add more points
    # if they are also core points.
    queue = neighbors_of_start_point[:]
    
    i = 0
    while i < len(queue):
        # Get the next point index from the queue
        current_idx = queue[i]
        
        # Case 1: Point was labeled as Noise (-1)
        # This point is density-reachable from a core point, so it's
        # a border point. It becomes part of the cluster.
        if labels[current_idx] == -1:
            labels[current_idx] = cluster_id
        
        # Case 2: Point is Unclassified (-2)
        # This is a new point to add to the cluster.
        elif labels[current_idx] == -2:
            labels[current_idx] = cluster_id
            
            # Find the neighbors of this new point
            neighbors_of_current = get_neighbors(X, current_idx, eps_squared)
            
            # Check if this new point is ALSO a core point
            if len(neighbors_of_current) >= min_pts:
                # If it is, add all its unclassified or noise neighbors
                # to the queue to be processed.
                for idx in neighbors_of_current:
                    if labels[idx] in [-1, -2]: # If Noise or Unclassified
                        if idx not in queue:
                            queue.append(idx)
                            
        # Case 3: Point is already part of this cluster or another
        # Do nothing.
        
        # Move to the next item in the queue
        i += 1
    
    # This loop finishes when the queue is empty, meaning the
    # cluster is fully expanded.

# --- Wrapper Function: DBSCAN Model ---

def dbscan_model(X, eps, min_pts):
    """
    Performs DBSCAN clustering on the dataset X.
    
    Args:
        X (pd.DataFrame or np.array): The input data (n_samples, n_features).
                                      'y' is not used (unsupervised).
        eps (float): The maximum distance between two samples for one to be
                     considered as in the neighborhood of the other (hyperparameter).
        min_pts (int): The number of samples (or total weight) in a neighborhood
                       for a point to be considered as a core point (hyperparameter).
                       This includes the point itself.

    Returns:
        np.array: An array of cluster labels for each point.
                  Noise points are labeled -1.
                  Clusters are labeled 0, 1, 2, ...
    """
    
    # 1. Handle Input Type
    if isinstance(X, pd.DataFrame):
        X_np = X.values
    elif isinstance(X, np.ndarray):
        X_np = X
    else:
        raise TypeError("Input X must be a pandas DataFrame or a numpy array.")
        
    n_samples, _ = X_np.shape
    
    # 2. Pre-calculate eps_squared for efficiency
    eps_squared = eps**2
    
    # 3. Initialize labels array
    # -2 = Unclassified
    # -1 = Noise
    # >= 0 = Cluster ID
    labels = np.full(n_samples, -2, dtype=int)
    
    cluster_id = 0
    
    # 4. Iterate over all points
    for i in range(n_samples):
        # Skip if point is already classified
        if labels[i] != -2:
            continue
            
        # a. Find neighbors for the current point
        neighbors = get_neighbors(X_np, i, eps_squared)
        
        # b. Check if it's a core point
        if len(neighbors) < min_pts:
            # Not a core point. Mark as Noise (for now).
            # It might be re-labeled as a border point later.
            labels[i] = -1
            continue
            
        # c. It IS a core point. Start a new cluster.
        # We pass the pre-computed neighbors to save computation.
        expand_cluster(
            X=X_np,
            labels=labels,
            point_index=i,
            cluster_id=cluster_id,
            eps_squared=eps_squared,
            min_pts=min_pts,
            neighbors_of_start_point=neighbors
        )
        
        # Increment cluster ID for the next cluster
        cluster_id += 1
        
    return labels

# --- Example Usage (Optional, for demonstration) ---
if __name__ == "__main__":
    # This block runs only when the script is executed directly
    
    # 1. Create dummy data (two moons)
    np.random.seed(42)
    n_pts = 200
    # Moon 1
    t = np.linspace(0, np.pi, n_pts // 2)
    X1 = np.array([1 * np.cos(t) + 0.5, 1 * np.sin(t)]).T + np.random.rand(n_pts // 2, 2) * 0.1
    # Moon 2
    t = np.linspace(np.pi, 2 * np.pi, n_pts // 2)
    X2 = np.array([1 * np.cos(t) - 0.5, 1 * np.sin(t)]).T + np.random.rand(n_pts // 2, 2) * 0.1
    # Add some noise
    X_noise = (np.random.rand(20, 2) - 0.5) * 4
    
    X_train = np.vstack((X1, X2, X_noise))
    X_df = pd.DataFrame(X_train, columns=['feature_1', 'feature_2'])
    
    print(f"Shape of training data: {X_df.shape}")
    
    # 2. Set hyperparameters
    EPSILON = 0.2
    MIN_POINTS = 5
    
    # 3. Run the model
    cluster_labels = dbscan_model(
        X=X_df,
        eps=EPSILON,
        min_pts=MIN_POINTS
    )
    
    print("\n--- DBSCAN Clustering Results ---")
    print(f"Epsilon (eps): {EPSILON}")
    print(f"Min Points (min_pts): {MIN_POINTS}")
    
    # Add labels to the dataframe
    X_df['cluster'] = cluster_labels
    
    print("\nCluster counts (Noise = -1):")
    # Use pandas to count occurrences of each cluster label
    print(X_df['cluster'].value_counts().sort_index())

    # You could visualize this data with matplotlib to see the clusters
    # (requires adding `import matplotlib.pyplot as plt`)
    # if 'matplotlib' in sys.modules:
    #     plt.figure(figsize=(8, 6))
    #     plt.scatter(X_df['feature_1'], X_df['feature_2'], c=X_df['cluster'], cmap='viridis', s=10)
    #     plt.title(f'DBSCAN Clustering (eps={EPSILON}, min_pts={MIN_POINTS})')
    #     plt.xlabel('Feature 1')
    #     plt.ylabel('Feature 2')
    #     plt.show()
