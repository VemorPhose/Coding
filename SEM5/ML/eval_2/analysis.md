After implementing batch and stochastic gradient descent for logistic regression, the observations are:

1. Batch GD converges smoothly, while stochastic GD showed very noisy cost curves
2. Hyperparameter choices were such that, with lower learning rate early stopping was too early, and with higher learning rate the algorithm was overshooting occasionally.
3. 60:10:30 split showed best results in terms of generalizing to test set.
4. Expanding on hyperparameter point - for small value of Rho => all epochs were run; while for larger Rho => early stopping was sooner

In plots directory, plots for best performing hyperparameter choices are saved per split, for each variant of GD.
And, accuracy numbers are shown in the notebook.