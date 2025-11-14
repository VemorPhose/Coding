import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.metrics import confusion_matrix


def plot_confusion_matrix(y_true, y_pred, class_names=None, title="Confusion Matrix"):
    """
    Computes and plots the confusion matrix using seaborn heatmap.
    Works for binary and multiclass.
    """
    cm = confusion_matrix(y_true, y_pred)

    plt.figure(figsize=(6, 5))
    sns.heatmap(cm, annot=True, fmt='d', cmap='Blues',
                xticklabels=class_names,
                yticklabels=class_names)

    plt.title(title)
    plt.xlabel("Predicted Labels")
    plt.ylabel("True Labels")
    plt.tight_layout()
    plt.show()

    return cm


# ============================
# ====== Usage Example =======
# ============================

# y_pred: predicted labels from your model (argmax for softmax, threshold for binary)
# y_true: raw target labels (not one-hot)

# Example:
# y_pred = np.array([0, 1, 1, 2, 2, 1])
# y_true = np.array([0, 1, 2, 2, 1, 1])
# class_names = ["Class0", "Class1", "Class2"]

# cm = plot_confusion_matrix(y_true, y_pred, class_names)
