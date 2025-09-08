### In this assignment:

1. Batch gradient descent
2. Mini-batch gradient descent
3. Stochastic gradient descent

Were implemented, training on the “mental health digital behaviour dataset” from kaggle.

Working with different train-test splits and different combinations of hyperparameters alpha and delta, and optimizing them using grid search,
the best train-test split and hyperparameters were found by plotting graphs and analyzing different model errors.

1. Best train-val-test split: 80:10:10
2. Best learning rate (alpha): 0.1
3. Best stopping parameter (delta): 0.001

Mean RSS value was lower for higher test set sizes. This would signify that the increased training data is causing the model to learn better.
The noticed performance of the different gradient descent algorithms was in the order:

### SGD > MGD > BGD

Other than this, the following plots can be referred to for more details:
1. Batch Gradient Descent - Train set size vs. Mean RSS
2. Mini-batch Gradient Descent - Train set size vs. Mean RSS
3. Stochastic Gradient Descent - Train set size vs. Mean RSS
4. Batch Gradient Descent - Training phase epochs vs. Mean RSS
5. Mini-batch Gradient Descent - Training phase epochs vs. Mean RSS
6. Stochastic Gradient Descent - Training phase epochs vs. Mean RSS