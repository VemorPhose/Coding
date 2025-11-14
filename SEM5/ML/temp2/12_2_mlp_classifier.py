import numpy as np
import pandas as pd
from sklearn.metrics import accuracy_score, precision_score, recall_score
from sklearn.model_selection import KFold
from sklearn.preprocessing import StandardScaler, MinMaxScaler


# ---------------------------------------------------------
# PREPROCESSING BLOCK (YOUR EXACT CODE)
# ---------------------------------------------------------
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

def preprocess_features(df, target_col, categorical_cols=None,
                        one_hot=True, scaler_type="standard", drop_first=False):

    df = df.copy()
    if categorical_cols is None:
        categorical_cols = infer_categorical_columns(df)

    y = df[target_col].values
    X_df = df.drop(columns=[target_col])

    # One-hot encoding
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


# ---------------------------------------------------------
# MANUAL MLP IMPLEMENTATION (1 hidden layer, sigmoid)
# ---------------------------------------------------------

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def sigmoid_deriv(x):
    s = sigmoid(x)
    return s * (1 - s)

class ManualMLP:
    def __init__(self, input_dim, hidden_dim=2, lr=0.1):
        self.lr = lr

        # Weight initialization
        self.W1 = np.random.randn(input_dim, hidden_dim) * 0.1
        self.b1 = np.zeros((1, hidden_dim))

        self.W2 = np.random.randn(hidden_dim, 1) * 0.1
        self.b2 = np.zeros((1, 1))

    def forward(self, X):
        self.z1 = X @ self.W1 + self.b1
        self.a1 = sigmoid(self.z1)

        self.z2 = self.a1 @ self.W2 + self.b2
        self.a2 = sigmoid(self.z2)

        return self.a2
    
    def backward(self, X, y, output):
        m = X.shape[0]
        y = y.reshape(-1, 1)

        # Output layer error
        dz2 = (output - y) * sigmoid_deriv(self.z2)  
        dW2 = self.a1.T @ dz2 / m
        db2 = np.sum(dz2, axis=0, keepdims=True) / m

        # Hidden layer error
        dz1 = (dz2 @ self.W2.T) * sigmoid_deriv(self.z1)
        dW1 = X.T @ dz1 / m
        db1 = np.sum(dz1, axis=0, keepdims=True) / m

        # Gradient descent update
        self.W2 -= self.lr * dW2
        self.b2 -= self.lr * db2
        self.W1 -= self.lr * dW1
        self.b1 -= self.lr * db1

    def train(self, X, y, epochs=50):
        for ep in range(epochs):
            out = self.forward(X)
            self.backward(X, y, out)

    def predict(self, X):
        yhat = self.forward(X)
        return (yhat >= 0.5).astype(int).flatten()


# ---------------------------------------------------------
# EVALUATION FUNCTION
# ---------------------------------------------------------
def evaluate_fold(y_true, y_pred):
    classes = np.unique(y_true)

    class_acc = {}
    for c in classes:
        idx = (y_true == c)
        class_acc[c] = accuracy_score(y_true[idx], y_pred[idx])

    precision = precision_score(y_true, y_pred, average=None, zero_division=0)
    recall = recall_score(y_true, y_pred, average=None, zero_division=0)
    overall = accuracy_score(y_true, y_pred)

    return class_acc, precision, recall, overall


# ---------------------------------------------------------
# MAIN: 5-FOLD CV FOR EPOCH=50 & 100
# ---------------------------------------------------------
def run_mlp_pima(path, target_col="Outcome", epochs=50):
    print("\n================================================")
    print(f" Manual MLP on Pima Dataset (epochs = {epochs})")
    print("================================================\n")

    df = load_csv(path, target_col)
    X, y, _, _ = preprocess_features(df, target_col, categorical_cols=[])

    kf = KFold(n_splits=5, shuffle=True, random_state=42)

    all_prec, all_rec, all_overall, all_class_acc = [], [], [], []

    fold = 1
    for train_idx, test_idx in kf.split(X):
        print(f"--- Fold {fold} ---")

        X_train, X_test = X[train_idx], X[test_idx]
        y_train, y_test = y[train_idx], y[test_idx]

        mlp = ManualMLP(input_dim=X.shape[1], hidden_dim=2, lr=0.1)
        mlp.train(X_train, y_train, epochs=epochs)

        y_pred = mlp.predict(X_test)

        class_acc, precision, recall, overall = evaluate_fold(y_test, y_pred)

        print("Class-wise Accuracy:", class_acc)
        print("Precision:", precision)
        print("Recall:", recall)
        print("Overall Accuracy:", overall)
        print()

        all_prec.append(precision)
        all_rec.append(recall)
        all_overall.append(overall)
        all_class_acc.append(class_acc)

        fold += 1

    print("\n========== FINAL 5-FOLD AVERAGES ==========")
    print("Average Overall Accuracy:", np.mean(all_overall))
    print("Average Precision:", np.mean(all_prec, axis=0))
    print("Average Recall:", np.mean(all_rec, axis=0))
    print("Average Class-wise Accuracy:", pd.DataFrame(all_class_acc).mean().to_dict())
    print("===========================================\n")


# ---------------------------------------------------------
# RUN BOTH EXPERIMENTS
# ---------------------------------------------------------

pima_path = "pima_diabetes.csv"   # update this if needed

run_mlp_pima(pima_path, epochs=50)
run_mlp_pima(pima_path, epochs=100)
