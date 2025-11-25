### 1. Component Planes (Feature Maps)
- The heatmaps display the learned weights for each feature on the 4 x 2 grid.
- By cross-referencing the Income and Spending planes, we can pinpoint specific segments, such as high income matching with low spending.
- The smooth color gradients across the grid show that the SOM successfully preserved the topological relationships between similar data points.

### 2. Cluster Visualization
- The scatter plots show data points colored by their assigned neuron.
- Although the dataset likely contains five natural clusters, our eight-neuron grid causes slight over-segmentation of the larger groups.
- However, the plots confirm that customers with similar income and spending values are consistently grouped together, indicating the clustering process worked effectively.

### 3. Epoch Comparison (100 vs. 1000)
- At 100 epochs, the map is coarser, and weights may not have fully settled on cluster centers.
- Running 1000 epochs with a decaying radius allows the algorithm to fine-tune these weights.
- This results in tighter, more distinct clusters and a grid organization that better represents the true structure of the data.