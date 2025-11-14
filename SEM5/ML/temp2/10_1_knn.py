import numpy as np
import pandas as pd
from sklearn.preprocessing import StandardScaler, MinMaxScaler
from sklearn.metrics import accuracy_score, confusion_matrix
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
import seaborn as sns

# ============================================================
#                 1. PREPROCESSING FUNCTIONS
# ============================================================

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

# ============================================================
#                     2. DISTANCE FUNCTION
# ============================================================

def euclidean_distance(a, b):
    return np.sqrt(np.sum((a - b)**2, axis=1))

# ============================================================
#            3. KNN PREDICTION FUNCTIONS (NO CLASSES)
# ============================================================

def knn_predict_single(x, X_train, y_train, k=5):
    distances = euclidean_distance(X_train, x)
    idx = np.argsort(distances)[:k]
    neighbors = y_train[idx]

    # Standard majority vote
    (values, counts) = np.unique(neighbors, return_counts=True)
    return values[np.argmax(counts)]


def knn_weighted_predict_single(x, X_train, y_train, k=5, power=1):
    """
    Weighted KNN:
        power = 1  -> weight = 1/d
        power = 2  -> weight = 1/d^2
    """

    distances = euclidean_distance(X_train, x)
    idx = np.argsort(distances)[:k]

    eps = 1e-8
    weights = 1 / (distances[idx] ** power + eps)
    classes = y_train[idx]

    # Weighted vote
    unique_labels = np.unique(y_train)
    vote_sum = {c: 0.0 for c in unique_labels}

    for c, w in zip(classes, weights):
        vote_sum[c] += w

    return max(vote_sum, key=vote_sum.get)


# ============================================================
#          4. BATCH PREDICTION FOR TEST SET
# ============================================================

def knn_predict(X_test, X_train, y_train, k=5):
    preds = []
    for i in range(len(X_test)):
        preds.append(knn_predict_single(X_test[i], X_train, y_train, k))
    return np.array(preds)


def knn_weighted_predict(X_test, X_train, y_train, k=5, power=1):
    preds = []
    for i in range(len(X_test)):
        preds.append(knn_weighted_predict_single(X_test[i], X_train, y_train, k, power))
    return np.array(preds)

# ============================================================
#         5. CONFUSION MATRIX + METRICS + PLOTTING
# ============================================================

def plot_confusion_matrix(y_true, y_pred):
    cm = confusion_matrix(y_true, y_pred)
    plt.figure(figsize=(6,5))
    sns.heatmap(cm, annot=True, fmt="d", cmap="Blues")
    plt.xlabel("Predicted")
    plt.ylabel("Actual")
    plt.title("Confusion Matrix")
    plt.show()


# ============================================================
#                           6. MAIN
# ============================================================

def main_knn_pipeline(path, target_col, k=5):
    # ---- Load ----
    df = load_csv(path, target_col)

    # ---- Preprocess ----
    X, y, feature_names, scaler = preprocess_features(
        df,
        target_col,
        categorical_cols=None,
        one_hot=True,
        scaler_type="standard"
    )

    # ---- Split ----
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.2, random_state=42, shuffle=True
    )

    # ========= STANDARD KNN =========
    y_pred_standard = knn_predict(X_test, X_train, y_train, k)
    acc_standard = accuracy_score(y_test, y_pred_standard)
    print(f"\nStandard KNN Accuracy (k={k}):", acc_standard)

    # ========= WEIGHTED KNN (1/d) =========
    y_pred_w1 = knn_weighted_predict(X_test, X_train, y_train, k, power=1)
    acc_w1 = accuracy_score(y_test, y_pred_w1)
    print(f"\nWeighted KNN Accuracy (1/d):", acc_w1)

    # ========= WEIGHTED KNN (1/d²) =========
    y_pred_w2 = knn_weighted_predict(X_test, X_train, y_train, k, power=2)
    acc_w2 = accuracy_score(y_test, y_pred_w2)
    print(f"\nWeighted KNN Accuracy (1/d²):", acc_w2)

    # ===== Confusion Matrix for 1/d² (most common best) =====
    print("\nConfusion Matrix (Weighted 1/d²):")
    plot_confusion_matrix(y_test, y_pred_w2)


# ============================================================
# Example call
# ============================================================

# main_knn_pipeline("your_dataset.csv", target_col="target", k=7)
