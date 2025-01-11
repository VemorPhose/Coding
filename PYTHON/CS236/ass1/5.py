l1 = [1, 2, 3]
l2 = [4, 5, 6]

l = l1 + l2
print(l)

for x in l:
    if x%2 == 0:
        print(x, end=' ')
print()

# cool way
t = [val for val in l if val % 2 == 0]