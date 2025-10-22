import numpy as np
import pandas as pd

# --- Helper Function: Distance ---

def euclidean_distance(point1, point2):
    """
    Calculates the squared Euclidean distance between two points.
    Using squared distance is computationally cheaper and sufficient
    for finding the minimum distance.
    
    Args:
        point1 (np.array): First point (1D array, n_features).
        point2 (np.array): Second point (1D array, n_features).

    Returns:
        float: Squared Euclidean distance.
    """
    return np.sum((point1 - point2)**2)

# --- Subpart 1: Centroid Initialization ---

def initialize_centroids(X, k):
    """
    Initializes 'k' centroids by randomly selecting 'k' points from the dataset X.
    This is a simple "Forgy" initialization method.
    
    Args:
        X (np.array): The input data (n_samples, n_features).
        k (int): The number of clusters.

    Returns:
        np.array: The initial centroids (k, n_features).
    """
    n_samples, _ = X.shape
    # Get random indices without replacement
    random_indices = np.random.choice(n_samples, k, replace=False)
    centroids = X[random_indices]
    return centroids

# --- Subpart 2: Cluster Assignment ---

def assign_clusters(X, centroids):
    """
    Assigns each data point in X to the nearest centroid.
    
    Args:
        X (np.array): The input data (n_samples, n_features).
        centroids (np.array): The current cluster centroids (k, n_features).

    Returns:
        np.array: An array of cluster indices (0 to k-1) for each data point (n_samples,).
    """
    n_samples = X.shape[0]
    k = centroids.shape[0]
    cluster_assignments = np.zeros(n_samples, dtype=int)

    # Iterate over each data point
    for i in range(n_samples):
        point = X[i]
        
        # Calculate distance from the point to each centroid
        distances = [euclidean_distance(point, centroids[j]) for j in range(k)]
        
        # Find the index of the closest centroid
        closest_centroid_index = np.argmin(distances)
        cluster_assignments[i] = closest_centroid_index
        
    return cluster_assignments

# --- Subpart 3: Centroid Update ---

def update_centroids(X, cluster_assignments, k):
    """
    Updates the centroids by calculating the mean of all points assigned to each cluster.
    
    Args:
        X (np.array): The input data (n_samples, n_features).
        cluster_assignments (np.array): Cluster indices for each point (n_samples,).
        k (int): The number of clusters.

    Returns:
        np.array: The new centroids (k, n_features).
    """
    n_features = X.shape[1]
    new_centroids = np.zeros((k, n_features))
    
    # Iterate over each cluster index
    for j in range(k):
        # Get all data points assigned to the current cluster
        points_in_cluster = X[cluster_assignments == j]
        
        # Check if the cluster is not empty
        if len(points_in_cluster) > 0:
            # Calculate the mean of the points and update the centroid
            new_centroids[j] = np.mean(points_in_cluster, axis=0)
        else:
            # Handle empty cluster: re-initialize this centroid
            # We pick a new random point from X to be the centroid
            # This helps prevent cluster collapse.
            random_index = np.random.choice(X.shape[0])
            new_centroids[j] = X[random_index]

    return new_centroids

# --- Wrapper Function: K-Means Model ---

def kmeans_model(X, k, max_iters=100, tol=1e-4):
    """
    Performs K-Means clustering on the dataset X.
    
    Args:
        X (pd.DataFrame or np.array): The input data (n_samples, n_features).
                                      'y' is not used as K-Means is unsupervised.
        k (int): The number of clusters (hyperparameter).
        max_iters (int): Maximum number of iterations (hyperparameter).
        tol (float): Tolerance for convergence (hyperparameter).
                     Stops if the sum of squared changes in centroids is less than tol.

    Returns:
        tuple: A tuple containing:
            - np.array: The final cluster centroids (k, n_features).
            - np.array: The final cluster assignments for each point (n_samples,).
    """
    
    # 1. Handle Input Type (Pandas DataFrame or NumPy Array)
    if isinstance(X, pd.DataFrame):
        X_np = X.values
    elif isinstance(X, np.ndarray):
        X_np = X
    else:
        raise TypeError("Input X must be a pandas DataFrame or a numpy array.")

    # 2. Initialize Centroids
    centroids = initialize_centroids(X_np, k)
    
    # 3. Iterative Refinement
    for i in range(max_iters):
        # Store old centroids for convergence check
        old_centroids = np.copy(centroids)
        
        # a. Assign clusters
        cluster_assignments = assign_clusters(X_np, centroids)
        
        # b. Update centroids
        centroids = update_centroids(X_np, cluster_assignments, k)
        
        # c. Check for convergence
        # Calculate the total squared change in centroids
        change = np.sum((centroids - old_centroids)**2)
        
        if change < tol:
            # print(f"Converged at iteration {i+1}")
            break
            
    return centroids, cluster_assignments

# --- Example Usage (Optional, for demonstration) ---
if __name__ == "__main__":
    # This block runs only when the script is executed directly
    
    # 1. Create dummy data
    np.random.seed(42)
    # Create two distinct clusters
    X1 = np.random.randn(50, 2) + np.array([0, 0])
    X2 = np.random.randn(50, 2) + np.array([5, 5])
    X_train = np.vstack((X1, X2))
    
    # Convert to DataFrame to test that functionality
    X_df = pd.DataFrame(X_train, columns=['feature_1', 'feature_2'])
    
    print(f"Shape of training data: {X_df.shape}")
    
    # 2. Set hyperparameters
    K_CLUSTERS = 2
    MAX_ITERATIONS = 100
    
    # 3. Run the model
    final_centroids, final_clusters = kmeans_model(
        X=X_df, 
        k=K_CLUSTERS, 
        max_iters=MAX_ITERATIONS
    )
    
    print("\n--- K-Means Clustering Results ---")
    print(f"Number of clusters (k): {K_CLUSTERS}")
    
    print("\nFinal Centroids:")
    print(pd.DataFrame(final_centroids, columns=X_df.columns))
    
    # Add assignments to the original dataframe for inspection
    X_df['cluster'] = final_clusters
    print("\nData with assigned clusters (first 10 rows):")
    print(X_df.head(10))
    
    print("\nCluster counts:")
    print(X_df['cluster'].value_counts())
