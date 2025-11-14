import numpy as np
import pandas as pd
from sklearn.preprocessing import StandardScaler, MinMaxScaler
from sklearn.metrics import accuracy_score, confusion_matrix
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
import seaborn as sns

# -------------------------
# Preprocessing (your template)
# -------------------------
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


# ============================================
#        PERCEPTRON LEARNING ALGORITHM
#        (STANDARD IMPLEMENTATION)
# ============================================

def perceptron_train(X, y, lr=1.0, epochs=50):
    w = np.zeros(X.shape[1])  # includes bias term if added

    for _ in range(epochs):
        for xi, yi in zip(X, y):
            # Standard decision:
            # y_hat = 1 if w·x >= 0 else 0
            y_hat = 1 if np.dot(w, xi) >= 0 else 0

            # Update only when incorrect
            if yi == 1 and y_hat == 0:
                w = w + lr * xi
            elif yi == 0 and y_hat == 1:
                w = w - lr * xi

    return w


def perceptron_predict(X, w):
    return (np.dot(X, w) >= 0).astype(int)


# ============================================
#       Example Usage
# ============================================
# You will replace this with your own CSV
df = pd.DataFrame({
    "x1": np.random.randn(300),
    "x2": np.random.randn(300),
    "target": (np.random.randn(300) > 0).astype(int)
})

X, y, feature_names, scaler = preprocess_features(df, target_col="target")
X_b = add_intercept(X)

# Train-test split
X_train, X_test, y_train, y_test = train_test_split(
    X_b, y, test_size=0.3, random_state=42, stratify=y
)

# Train PLA
w = perceptron_train(X_train, y_train, lr=1.0, epochs=50)

# Predict
y_pred = perceptron_predict(X_test, w)

# Accuracy
test_acc = accuracy_score(y_test, y_pred)
print("Test Accuracy:", test_acc)
