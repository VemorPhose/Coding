import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import precision_score, recall_score, accuracy_score

# -----------------------------
# (a) Create Synthetic Dataset
# -----------------------------
np.random.seed(42)
n_samples = 300

# Two numeric features
X = np.random.randn(n_samples, 2)

# Binary target: roughly separable
y = (X[:, 0] + X[:, 1] > 0).astype(int)  # linearly separable boundary

# -----------------------------
# (b) Split Dataset 70:10:20
# -----------------------------
train_end = int(0.7 * n_samples)
val_end = int(0.8 * n_samples)

X_train, y_train = X[:train_end], y[:train_end]
X_val, y_val = X[train_end:val_end], y[train_end:val_end]
X_test, y_test = X[val_end:], y[val_end:]

# Add bias term (x0 = 1)
def add_bias(X):
    bias = np.ones((X.shape[0], 1))
    return np.hstack((bias, X))

X_train_b = add_bias(X_train)
X_val_b = add_bias(X_val)
X_test_b = add_bias(X_test)

# -----------------------------
# (c) Perceptron Implementation
# -----------------------------
def perceptron_train(X, y, epochs=50, w_init=None):
    """
    Trains perceptron on given data for specified epochs.
    """
    n_samples, n_features = X.shape
    if w_init is None:
        w = np.random.uniform(-0.5, 0.5, n_features)
    else:
        w = w_init.copy()

    for epoch in range(epochs):
        errors = 0
        for i in range(n_samples):
            xi = X[i]
            target = y[i]
            activation = np.dot(w, xi)

            # Using given update rule
            if activation <= 0 and target == 1:
                w = w + xi
                errors += 1
            elif activation >= 0 and target == 0:
                w = w - xi
                errors += 1

        # Stop if perfect classification
        if errors == 0:
            break
    return w


def perceptron_predict(X, w):
    activations = np.dot(X, w)
    return (activations >= 0).astype(int)

# -----------------------------
# (d) Evaluate multiple scenarios
# -----------------------------
epoch_list = [50, 100, 150]
results = []

for seed in [1, 10, 100]:  # 3 different weight initializations
    np.random.seed(seed)
    w_init = np.random.uniform(-0.5, 0.5, 3)  # 2 features + bias

    for epochs in epoch_list:
        w_trained = perceptron_train(X_train_b, y_train, epochs, w_init)
        y_pred = perceptron_predict(X_test_b, w_trained)

        precision = precision_score(y_test, y_pred)
        recall = recall_score(y_test, y_pred)
        accuracy = accuracy_score(y_test, y_pred)

        results.append({
            'init_seed': seed,
            'epochs': epochs,
            'precision': precision,
            'recall': recall,
            'accuracy': accuracy
        })

# -----------------------------
# Report & Visualization
# -----------------------------
import pandas as pd
df = pd.DataFrame(results)
print("\n=== Performance Results ===")
print(df)

# Plot Accuracy, Precision, Recall vs Epochs
fig, axes = plt.subplots(1, 3, figsize=(15, 4))
metrics = ['accuracy', 'precision', 'recall']

for i, metric in enumerate(metrics):
    for seed in df['init_seed'].unique():
        subset = df[df['init_seed'] == seed]
        axes[i].plot(subset['epochs'], subset[metric], marker='o', label=f'Seed {seed}')
    axes[i].set_title(metric.capitalize() + " vs Epochs")
    axes[i].set_xlabel("Epochs")
    axes[i].set_ylabel(metric.capitalize())
    axes[i].legend()

plt.tight_layout()
plt.show()
