import numpy as np
import pandas as pd
from sklearn.preprocessing import StandardScaler, MinMaxScaler
from sklearn.metrics import accuracy_score, precision_score, recall_score, confusion_matrix
from sklearn.model_selection import train_test_split
import warnings
warnings.filterwarnings("ignore")

# -----------------------------------------------------
# PREPROCESSING BLOCK (unchanged)
# -----------------------------------------------------

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
            raise ValueError(f"Categorical columns not found: {missing}")
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

    if one_hot and len(categorical_cols) > 0:
        X_df = pd.get_dummies(X_df, columns=categorical_cols, drop_first=drop_first)
    else:
        for col in categorical_cols:
            if col in X_df:
                X_df[col] = X_df[col].astype("category").cat.codes

    feature_names = X_df.columns.tolist()
    X = X_df.values.astype(float)

    # scaling
    if scaler_type == "standard":
        scaler = StandardScaler()
        X = scaler.fit_transform(X)
    elif scaler_type == "minmax":
        scaler = MinMaxScaler()
        X = scaler.fit_transform(X)
    else:
        raise ValueError("Invalid scaler type")

    return X, y, feature_names, scaler


def add_intercept(X):
    return np.hstack([np.ones((X.shape[0], 1)), X])


# -----------------------------------------------------
# ACTIVATION FUNCTIONS
# -----------------------------------------------------

def sigmoid(z):
    return 1 / (1 + np.exp(-z))

def sigmoid_derivative(a):
    return a * (1 - a)


# -----------------------------------------------------
# MLP FOR XOR (1 hidden layer, 2 neurons)
# -----------------------------------------------------

def initialize_weights(input_dim, hidden_dim, output_dim):
    W1 = np.random.randn(input_dim, hidden_dim) * 0.1
    W2 = np.random.randn(hidden_dim, output_dim) * 0.1
    return W1, W2


def forward(X, W1, W2):
    Z1 = np.dot(X, W1)
    A1 = sigmoid(Z1)

    Z2 = np.dot(A1, W2)
    A2 = sigmoid(Z2)

    return Z1, A1, Z2, A2


def backward(X, y, Z1, A1, Z2, A2, W1, W2, lr=0.1):
    m = len(y)
    y = y.reshape(-1, 1)

    # Output layer error
    dZ2 = (A2 - y) * sigmoid_derivative(A2)
    dW2 = np.dot(A1.T, dZ2) / m

    # Hidden layer error
    dZ1 = np.dot(dZ2, W2.T) * sigmoid_derivative(A1)
    dW1 = np.dot(X.T, dZ1) / m

    # Update
    W2 -= lr * dW2
    W1 -= lr * dW1

    return W1, W2


# -----------------------------------------------------
# Prediction
# -----------------------------------------------------

def predict(X, W1, W2):
    _, _, _, A2 = forward(X, W1, W2)
    return (A2 >= 0.5).astype(int).flatten()


# -----------------------------------------------------
# Reporting metrics
# -----------------------------------------------------

def report_metrics(y_true, y_pred, label):
    print(f"\n===== {label} Metrics =====")
    print("Accuracy:", accuracy_score(y_true, y_pred))
    print("Precision:", precision_score(y_true, y_pred, average=None, zero_division=0))
    print("Recall:", recall_score(y_true, y_pred, average=None, zero_division=0))
    print("Confusion Matrix:\n", confusion_matrix(y_true, y_pred))


# -----------------------------------------------------
# MAIN PROGRAM FOR XOR
# -----------------------------------------------------

# XOR dataset
df = pd.DataFrame({
    "x1": [0, 0, 1, 1],
    "x2": [0, 1, 0, 1],
    "y":  [0, 1, 1, 0]
})

# Preprocess (though XOR does not need scaling, we follow your spec)
X, y, f, scaler = preprocess_features(df, target_col="y", scaler_type="standard")
X = add_intercept(X)

# 70:10:20 split
X_train, X_temp, y_train, y_temp = train_test_split(X, y, test_size=0.30, random_state=42)
X_val, X_test, y_val, y_test = train_test_split(X_temp, y_temp, test_size=2/3, random_state=42)

# Initialize weights
input_dim = X_train.shape[1]
hidden_dim = 2
output_dim = 1

W1, W2 = initialize_weights(input_dim, hidden_dim, output_dim)

# Train for EXACTLY 2 epochs
epochs = 2
for epoch in range(epochs):
    Z1, A1, Z2, A2 = forward(X_train, W1, W2)
    W1, W2 = backward(X_train, y_train, Z1, A1, Z2, A2, W1, W2, lr=0.1)

# Predict Training + Test
train_pred = predict(X_train, W1, W2)
test_pred = predict(X_test, W1, W2)

# Metrics
report_metrics(y_train, train_pred, "Training")
report_metrics(y_test, test_pred, "Testing")
