#!/usr/bin/env python
import sys

for line in sys.stdin:
    line = line.strip()
    words = line.split()
    for word in words:
        word = word.strip('.,!?;"()[]{}<>')
        if word:
            print("%s,1" % word.lower())