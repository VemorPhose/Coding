import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# --- Helper Function: Distance ---

def euclidean_distance_squared(point1, point2):
    """
    Calculates the squared Euclidean distance between two points.
    We use squared distance because it's required for Ward's linkage
    formula and is more efficient.
    
    Args:
        point1 (np.array): First point (1D array, n_features).
        point2 (np.array): Second point (1D array, n_features).

    Returns:
        float: Squared Euclidean distance.
    """
    return np.sum((point1 - point2)**2)

# --- Subpart 1: Initial Point Distance Matrix ---

def calculate_point_distance_matrix(X):
    """
    Calculates the initial distance matrix between all pairs of points.
    
    Args:
        X (np.array): The input data (n_samples, n_features).

    Returns:
        np.array: A (n_samples, n_samples) matrix of pairwise squared
                  Euclidean distances. Diagonal is set to np.inf.
    """
    n_samples = X.shape[0]
    dist_matrix = np.zeros((n_samples, n_samples))
    
    for i in range(n_samples):
        for j in range(i, n_samples):
            dist = euclidean_distance_squared(X[i], X[j])
            dist_matrix[i, j] = dist
            dist_matrix[j, i] = dist
            
    # Set diagonal to infinity so a point doesn't merge with itself
    np.fill_diagonal(dist_matrix, np.inf)
    
    return dist_matrix

# --- Subpart 2: Find Closest Clusters ---

def find_closest_clusters(cluster_dist_matrix):
    """
    Finds the pair of clusters with the minimum distance.
    
    Args:
        cluster_dist_matrix (np.array): The current (n_samples, n_samples)
                                        distance matrix between active clusters.
                                        Merged clusters have their rows/cols
                                        set to np.inf.
    
    Returns:
        tuple: (c1_id, c2_id), the indices of the two closest clusters.
    """
    # Find the linear index of the minimum value in the flattened matrix
    flat_idx = np.argmin(cluster_dist_matrix)
    
    # Convert the linear index back to 2D (row, col) indices
    c1_id, c2_id = np.unravel_index(flat_idx, cluster_dist_matrix.shape)
    
    return (c1_id, c2_id)

# --- Subpart 3: Update Distance Matrix (Linkage) ---

def update_distances(
    cluster_dist_matrix, 
    centroids, 
    cluster_sizes,
    c_new, 
    c_old,
    c1_id,
    c2_id,
    active_cluster_ids, 
    linkage
):
    """
    Updates the cluster distance matrix after a merge.
    This function modifies cluster_dist_matrix and centroids in-place.
    
    Args:
        cluster_dist_matrix (np.array): The distance matrix.
        centroids (np.array): Array of centroids for each cluster.
        cluster_sizes (np.array): Array of sizes for each cluster.
        c_new (int): The ID of the merged cluster (e.g., c1_id).
        c_old (int): The ID of the cluster that was merged (e.g., c2_id).
        c1_id (int): Original ID of the first merging cluster.
        c2_id (int): Original ID of the second merging cluster.
        active_cluster_ids (list): List of IDs of currently active clusters.
        linkage (str): The linkage method to use.
    """
    
    # 1. Get sizes of the two clusters being merged
    size_c1 = cluster_sizes[c1_id]
    size_c2 = cluster_sizes[c2_id]
    new_size = size_c1 + size_c2
    
    # 2. Update the size and centroid of the new cluster
    # Get centroids *before* merge
    cent_c1 = centroids[c1_id]
    cent_c2 = centroids[c2_id]
    
    # Calculate new centroid
    new_centroid = (size_c1 * cent_c1 + size_c2 * cent_c2) / new_size
    
    # Store new info in the `c_new` slot
    centroids[c_new] = new_centroid
    cluster_sizes[c_new] = new_size
    
    # 3. Get distance between the two clusters that were just merged
    dist_c1_c2 = cluster_dist_matrix[c1_id, c2_id]

    # 4. Iterate over all *other* active clusters (k) to update distances
    for k in active_cluster_ids:
        if k == c_new:
            continue
            
        dist_k_c1 = cluster_dist_matrix[k, c1_id]
        dist_k_c2 = cluster_dist_matrix[k, c2_id]
        size_k = cluster_sizes[k]
        
        # Calculate new distance from k to the new cluster (c_new)
        if linkage == 'single':
            new_dist = min(dist_k_c1, dist_k_c2)
            
        elif linkage == 'complete':
            new_dist = max(dist_k_c1, dist_k_c2)
            
        elif linkage == 'average':
            new_dist = (size_c1 * dist_k_c1 + size_c2 * dist_k_c2) / new_size
            
        elif linkage == 'centroid':
            # Distance between the centroid of k and the new centroid
            cent_k = centroids[k]
            new_dist = euclidean_distance_squared(cent_k, new_centroid)
            
        elif linkage == 'ward':
            # Lance-Williams formula for Ward's (using squared distances)
            total_size_with_k = size_k + new_size
            term1 = (size_k + size_c1) * dist_k_c1
            term2 = (size_k + size_c2) * dist_k_c2
            term3 = size_k * dist_c1_c2
            new_dist = (term1 + term2 - term3) / total_size_with_k
            
        # Update the matrix symmetrically
        cluster_dist_matrix[k, c_new] = new_dist
        cluster_dist_matrix[c_new, k] = new_dist

    # 5. "Deactivate" the old cluster (c_old) by setting its row/col to infinity
    cluster_dist_matrix[c_old, :] = np.inf
    cluster_dist_matrix[:, c_old] = np.inf

# --- Wrapper Function: Hierarchical Clustering Model ---

def hierarchical_clustering_model(X, n_clusters, linkage='single'):
    """
    Performs Agglomerative Hierarchical Clustering.
    
    Args:
        X (pd.DataFrame or np.array): The input data (n_samples, n_features).
                                      'y' is not used.
        n_clusters (int): The number of clusters to find (hyperparameter).
        linkage (str): The linkage criterion to use. One of:
                       'single', 'complete', 'average', 'centroid', 'ward'.
                       (hyperparameter).

    Returns:
        np.array: An array of cluster labels (n_samples,).
    """
    
    # 1. Handle Input Type
    if isinstance(X, pd.DataFrame):
        X_np = X.values
    elif isinstance(X, np.ndarray):
        X_np = X
    else:
        raise TypeError("Input X must be a pandas DataFrame or a numpy array.")
        
    n_samples, _ = X_np.shape
    
    if n_clusters < 1 or n_clusters > n_samples:
        raise ValueError("n_clusters must be between 1 and n_samples.")
        
    valid_linkages = ['single', 'complete', 'average', 'centroid', 'ward']
    if linkage not in valid_linkages:
        raise ValueError(f"Unknown linkage: {linkage}. Must be one of {valid_linkages}")
        
    # 2. Initialization
    # `clusters` tracks which original points belong to which active cluster ID
    clusters = {i: [i] for i in range(n_samples)}
    
    # `active_cluster_ids` tracks which cluster IDs are still in use
    active_cluster_ids = list(range(n_samples))
    
    # `centroids` stores the centroid for each potential cluster ID
    centroids = X_np.copy()
    
    # `cluster_sizes` stores the number of points in each cluster
    cluster_sizes = np.ones(n_samples)
    
    # `cluster_dist_matrix` is the core. Starts as point-to-point distances.
    cluster_dist_matrix = calculate_point_distance_matrix(X_np)
    
    n_current_clusters = n_samples
    
    # 3. Agglomerative Merging Loop
    while n_current_clusters > n_clusters:
        # a. Find the two closest clusters
        c1_id, c2_id = find_closest_clusters(cluster_dist_matrix)
        
        # b. Determine which ID to keep (c_new) and which to merge/deactivate (c_old)
        c_new = min(c1_id, c2_id)
        c_old = max(c1_id, c2_id)
        
        # c. Update distances in the matrix based on linkage
        update_distances(
            cluster_dist_matrix, 
            centroids, 
            cluster_sizes,
            c_new, 
            c_old,
            c1_id, # Pass original IDs for size/centroid lookup
            c2_id,
            active_cluster_ids, 
            linkage
        )
        
        # d. Perform the merge in our tracking structures
        clusters[c_new].extend(clusters[c_old]) # Add old's points to new
        del clusters[c_old]                    # Remove old cluster
        active_cluster_ids.remove(c_old)       # Deactivate old ID
        
        n_current_clusters -= 1
        
    # 4. Assign final labels
    final_labels = np.zeros(n_samples, dtype=int)
    
    # `clusters.values()` now contains lists of points for the final clusters
    for i, point_indices in enumerate(clusters.values()):
        for idx in point_indices:
            final_labels[idx] = i
            
    return final_labels

# --- Example Usage (Optional, for demonstration) ---
if __name__ == "__main__":
    # 1. Create dummy data
    np.random.seed(42)
    # Create three distinct clusters
    X1 = np.random.randn(30, 2) + np.array([0, 0])
    X2 = np.random.randn(30, 2) + np.array([5, 5])
    X3 = np.random.randn(30, 2) + np.array([0, 5])
    X_train = np.vstack((X1, X2, X3))
    
    X_df = pd.DataFrame(X_train, columns=['feature_1', 'feature_2'])
    
    print(f"Shape of training data: {X_df.shape}")
    
    # 2. Set hyperparameters
    N_CLUSTERS = 3
    LINKAGE_METHODS = ['single', 'complete', 'average', 'centroid', 'ward']
    
    # 3. Run the model for each linkage and plot
    print(f"\n--- Hierarchical Clustering Results (Target={N_CLUSTERS} clusters) ---")
    
    plt.figure(figsize=(24, 5))
    
    for i, linkage_method in enumerate(LINKAGE_METHODS):
        print(f"Running with linkage: '{linkage_method}'...")
        
        # Run the model
        cluster_labels = hierarchical_clustering_model(
            X=X_df,
            n_clusters=N_CLUSTERS,
            linkage=linkage_method
        )
        
        # Add to subplot
        ax = plt.subplot(1, len(LINKAGE_METHODS), i + 1)
        
        # Plot data points
        scatter = ax.scatter(
            X_df['feature_1'], 
            X_df['feature_2'], 
            c=cluster_labels, 
            cmap='viridis', 
            s=50, 
            alpha=0.7
        )
        
        ax.set_title(f'Linkage: {linkage_method}')
        ax.set_xlabel('Feature 1')
        ax.set_ylabel('Feature 2')
        ax.grid(True)
        
        # Create a legend
        handles, labels = scatter.legend_elements(prop="colors", alpha=0.7)
        legend_labels = [f'Cluster {j}' for j in range(N_CLUSTERS)]
        ax.legend(handles=handles, labels=legend_labels, title="Clusters", loc='best')

    plt.suptitle(f'Hierarchical Clustering with {N_CLUSTERS} Clusters', fontsize=16, y=1.05)
    plt.tight_layout()
    plt.show()
