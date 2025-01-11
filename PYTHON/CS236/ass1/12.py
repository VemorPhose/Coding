inventory = {'banana': 5, 'apple': 6, 'orange': 7}

# i
print(inventory)

# ii
for i in inventory:
    print(inventory[i], end=' ')
print()

# iii
item = input('Enter item to check stock: ')
if item in inventory:
    print(f'{item} stock: {inventory[item]}')
else:
    print(f'{item} not found in inventory.')