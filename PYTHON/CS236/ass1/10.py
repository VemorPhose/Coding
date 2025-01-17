def fun(l):
    new = []
    for i in l:
        if i in new:
            continue
        else:
            new.append(i)
    return new

l = [1, 2, 3, 4, 1, 2, 5, 4]
new = fun(l)
print(new)