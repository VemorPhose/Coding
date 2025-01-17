a = 5

def local():
    a = 4
    print(a)

def glob():
    global a
    a = 6
    print(a)

print(a)
local()
print(a)
glob()
print(a)