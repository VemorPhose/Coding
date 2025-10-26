#!/usr/bin/env python
import sys

current_id = None
sum_sl = 0.0
sum_sw = 0.0
count = 0

for line in sys.stdin:
    line = line.strip()
    if not line:
        continue

    cid, values = line.split("\t")
    cid = int(cid)

    sl, sw, cnt = values.split(",")
    sl = float(sl)
    sw = float(sw)
    cnt = int(cnt)

    if current_id is None:
        current_id = cid

    if cid != current_id:
        if count > 0:
            print("%d\t%f,%f,%d" % (current_id, sum_sl / count, sum_sw / count, count))
        current_id = cid
        sum_sl = 0.0
        sum_sw = 0.0
        count = 0

    sum_sl += sl
    sum_sw += sw
    count += 1

if current_id is not None and count > 0:
    print("%d\t%f,%f,%d" % (current_id, sum_sl / count, sum_sw / count, count))
