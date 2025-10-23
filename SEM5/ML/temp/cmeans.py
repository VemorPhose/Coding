import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# --- Helper Function: Distance ---

def euclidean_distance_squared(point1, point2):
    """
    Calculates the squared Euclidean distance between two points.
    
    Args:
        point1 (np.array): First point (1D array, n_features).
        point2 (np.array): Second point (1D array, n_features).

    Returns:
        float: Squared Euclidean distance.
    """
    return np.sum((point1 - point2)**2)

# --- Subpart 1: Initialize Membership Matrix ---

def initialize_membership_matrix(n_samples, n_clusters):
    """
    Initializes the membership matrix 'U' with random values,
    such that each row (point) sums to 1.
    
    Args:
        n_samples (int): The number of data points.
        n_clusters (int): The number of clusters (k).

    Returns:
        np.array: The (n_samples, n_clusters) membership matrix U.
    """
    # Create random values
    U = np.random.rand(n_samples, n_clusters)
    
    # Normalize each row so it sums to 1
    # U = U / U.sum(axis=1, keepdims=True)
    # Using keepdims ensures (n_samples, 1) shape for broadcasting
    
    # A more robust way to avoid division by zero if a row sums to 0
    row_sums = U.sum(axis=1)
    # Set rows that sum to 0 to 1 to avoid division by zero,
    # they will be replaced by 1/n_clusters
    row_sums[row_sums == 0] = 1.0
    U = U / row_sums[:, np.newaxis]
    
    # Handle any NaN (if all row entries were 0)
    U[np.isnan(U)] = 1.0 / n_clusters
    
    return U

# --- Subpart 2: Update Centroids ---

def update_centroids(X, U, m, n_clusters):
    """
    Calculates the new cluster centroids based on the membership matrix.
    
    Formula: C_j = sum( (U_ij^m) * X_i ) / sum( U_ij^m )
    
    Args:
        X (np.array): The input data (n_samples, n_features).
        U (np.array): The membership matrix (n_samples, n_clusters).
        m (float): The fuzziness parameter.
        n_clusters (int): The number of clusters.

    Returns:
        np.array: The new cluster centroids (n_clusters, n_features).
    """
    n_samples, n_features = X.shape
    centroids = np.zeros((n_clusters, n_features))
    
    # Calculate U^m
    Um = U ** m
    
    for j in range(n_clusters):
        # Get the membership weights for this cluster
        weights_j = Um[:, j]
        
        # Calculate numerator (weighted sum of points)
        # np.dot(weights_j, X) performs:
        # (w_1*x_1_f1 + w_2*x_2_f1 + ...), (w_1*x_1_f2 + w_2*x_2_f2 + ...)
        numerator = np.dot(weights_j, X)
        
        # Calculate denominator (sum of weights)
        denominator = np.sum(weights_j)
        
        if denominator > 0:
            centroids[j] = numerator / denominator
        else:
            # Handle rare case where a cluster has 0 membership
            # Re-initialize this centroid randomly
            centroids[j] = X[np.random.choice(n_samples)]
            
    return centroids

# --- Subpart 3: Update Membership Matrix ---

def update_membership_matrix(X, centroids, m):
    """
    Updates the membership matrix 'U' based on the new centroids.
    
    Formula: U_ij = 1 / sum_k( (dist_ij / dist_ik)^(2 / (m - 1)) )
    
    Args:
        X (np.array): The input data (n_samples, n_features).
        centroids (np.array): The cluster centroids (n_clusters, n_features).
        m (float): The fuzziness parameter.

    Returns:
        np.array: The updated (n_samples, n_clusters) membership matrix U.
    """
    n_samples = X.shape[0]
    n_clusters = centroids.shape[0]
    U_new = np.zeros((n_samples, n_clusters))
    
    # Calculate the exponent
    power_val = 2.0 / (m - 1.0)
    
    # Calculate all pairwise distances (using sqrt for the formula)
    distances = np.zeros((n_samples, n_clusters))
    for i in range(n_samples):
        for j in range(n_clusters):
            # We need actual distance, not squared, for the formula
            distances[i, j] = np.sqrt(euclidean_distance_squared(X[i], centroids[j]))
            
    # Now, calculate the membership U_ij for each point i and cluster j
    for i in range(n_samples):
        dists_i = distances[i, :]
        
        # Check if any point is exactly on a centroid
        zero_dists_idx = np.where(dists_i == 0)[0]
        
        if len(zero_dists_idx) > 0:
            # Point is on one or more centroids
            # Assign full membership to that centroid(s), split if on multiple
            U_new[i, :] = 0.0
            U_new[i, zero_dists_idx] = 1.0 / len(zero_dists_idx)
        else:
            # Standard case: point is not on any centroid
            for j in range(n_clusters):
                sum_k = 0.0
                for k in range(n_clusters):
                    sum_k += (dists_i[j] / dists_i[k]) ** power_val
                
                U_new[i, j] = 1.0 / sum_k
                
    return U_new

# --- Wrapper Function: Fuzzy C-Means Model ---

def fuzzy_c_means_model(X, n_clusters, m=2.0, max_iters=100, tolerance=1e-5):
    """
    Performs Fuzzy C-Means clustering.
    
    Args:
        X (pd.DataFrame or np.array): The input data (n_samples, n_features).
                                      'y' is not used.
        n_clusters (int): The number of clusters to find (hyperparameter).
        m (float): The fuzziness parameter (hyperparameter, > 1).
        max_iters (int): Maximum number of iterations (hyperparameter).
        tolerance (float): Stop if the change in U is less than this
                           (hyperparameter).

    Returns:
        tuple: (U, centroids)
            U (np.array): The final membership matrix (n_samples, n_clusters).
            centroids (np.array): The final cluster centroids (n_clusters, n_features).
    """
    
    # 1. Handle Input Type
    if isinstance(X, pd.DataFrame):
        X_np = X.values
    elif isinstance(X, np.ndarray):
        X_np = X
    else:
        raise TypeError("Input X must be a pandas DataFrame or a numpy array.")
        
    n_samples, _ = X_np.shape
    
    if m <= 1:
        raise ValueError("'m' (fuzziness) must be greater than 1.")
        
    # 2. Initialization
    U = initialize_membership_matrix(n_samples, n_clusters)
    
    # 3. Iteration Loop
    for i in range(max_iters):
        # Store old U to check for convergence
        U_old = U.copy()
        
        # a. Update centroids
        centroids = update_centroids(X_np, U, m, n_clusters)
        
        # b. Update membership matrix
        U = update_membership_matrix(X_np, centroids, m)
        
        # c. Check for convergence
        change = np.linalg.norm(U - U_old)
        if change < tolerance:
            # print(f"Converged at iteration {i+1}")
            break
            
    # 4. Final centroid calculation (just in case loop ended on max_iters)
    centroids = update_centroids(X_np, U, m, n_clusters)
    
    return U, centroids

# --- Example Usage (Optional, for demonstration) ---
if __name__ == "__main__":
    # 1. Create dummy data (three overlapping blobs)
    np.random.seed(42)
    X1 = np.random.randn(50, 2) + np.array([0, 0])
    X2 = np.random.randn(50, 2) + np.array([4, 4])
    X3 = np.random.randn(50, 2) + np.array([0, 4])
    X_train = np.vstack((X1, X2, X3))
    
    X_df = pd.DataFrame(X_train, columns=['feature_1', 'feature_2'])
    
    print(f"Shape of training data: {X_df.shape}")
    
    # 2. Set hyperparameters
    N_CLUSTERS = 3
    M_FUZZINESS = 2.0  # Standard value
    
    # 3. Run the model
    print(f"\n--- Running Fuzzy C-Means (k={N_CLUSTERS}, m={M_FUZZINESS}) ---")
    U_matrix, final_centroids = fuzzy_c_means_model(
        X=X_df,
        n_clusters=N_CLUSTERS,
        m=M_FUZZINESS
    )
    
    # 4. Get "hard" cluster assignments for plotting
    hard_labels = np.argmax(U_matrix, axis=1)
    X_df['cluster'] = hard_labels
    
    print("\nCluster counts (based on highest membership):")
    print(X_df['cluster'].value_counts().sort_index())
    
    print("\nExample membership scores (first 5 points):")
    U_df = pd.DataFrame(U_matrix, columns=[f'Cluster_{j}' for j in range(N_CLUSTERS)])
    print(U_df.head().to_string(float_format="%.4f"))

    # 5. Visualize the results
    if X_train.shape[1] == 2:
        plt.figure(figsize=(10, 7))
        
        # Plot data points (colored by "hard" cluster)
        scatter = plt.scatter(
            X_df['feature_1'], 
            X_df['feature_2'], 
            c=X_df['cluster'], 
            cmap='viridis', 
            s=50, 
            alpha=0.7
        )
        
        # Plot centroids
        plt.scatter(
            final_centroids[:, 0], 
            final_centroids[:, 1], 
            c='red', 
            marker='X', 
            s=200, 
            edgecolor='black',
            label='Centroids'
        )
        
        plt.title(f'Fuzzy C-Means Clustering (k={N_CLUSTERS}, m={M_FUZZINESS})')
        plt.xlabel('Feature 1')
        plt.ylabel('Feature 2')

        # Create a legend
        handles, labels = scatter.legend_elements(prop="colors", alpha=0.7)
        legend_labels = [f'Cluster {i}' for i in range(N_CLUSTERS)]
        
        centroid_handle = plt.Line2D(
            [0], [0], 
            marker='X', 
            color='w', 
            label='Centroids', 
            markerfacecolor='red', 
            markeredgecolor='black',
            markersize=15, 
            linestyle='None'
        )
        handles.append(centroid_handle)
        legend_labels.append('Centroids')

        plt.legend(handles=handles, labels=legend_labels, title="Legend")
        plt.grid(True)
        plt.show()
