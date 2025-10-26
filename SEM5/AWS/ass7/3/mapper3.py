#!/usr/bin/env python
import sys
import math

centroids = [
    (1, 5.8, 4.0),  # Iris-setosa
    (2, 6.1, 2.8),  # Iris-versicolor
    (3, 6.3, 2.7)   # Iris-virginica
]

first_line = True

for line in sys.stdin:
    line = line.strip()
    if not line:
        continue

    if first_line:
        first_line = False
        if "sepallength" in line.lower():
            continue

    parts = line.split(",")
    if len(parts) < 2:
        continue

    try:
        sl = float(parts[0])  # Sepal Length
        sw = float(parts[1])  # Sepal Width
    except ValueError:
        continue

    best_id = None
    best_dist = float("inf")

    for cid, cx, cy in centroids:
        dist = (sl - cx) ** 2 + (sw - cy) ** 2
        if dist < best_dist:
            best_id = cid
            best_dist = dist

    print("%d\t%f,%f,1" % (best_id, sl, sw))
