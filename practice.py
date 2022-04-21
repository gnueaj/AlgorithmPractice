drinks = {
    'martini': {'vodka', 'vermouth'},
    'black russian': {'vodka','kahlua'},
    'white russian': {'cream', 'kahlua', 'vodka'},
    'manhattan': {'rye', 'vermouth', 'bitters'},
    'screwdriver': {'orange juice', 'vodka'}
    }
for name, contents in drinks.items():
        if {'vodka'} & contents and not contents & {'vermouth', 'orange juice'}:
            print(name)
            
a = {1, 2}
b = {2, 3}

print(a & b, a.intersection(b), a | b, a.union(b))
