#!/usr/bin/env python
import sys

word_counts = {}

for line in sys.stdin:
    line = line.strip()
    if not line:
        continue
    word, count = line.split(',', 1)
    count = int(count)
    word_counts[word] = word_counts.get(word, 0) + count

for word in sorted(word_counts.keys()):
    print("%s" % (word))
