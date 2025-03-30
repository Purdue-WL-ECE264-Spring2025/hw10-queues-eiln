

x = "1 2 3 4 5 6 0 8 9 10 7 12 13 14 11 15"
tile = x.split()
tile = [int(t) for t in tile]
print(tile)


for n in range(len(tile)):
    if (n + 1 != tile[n]):
        print(f"stop: index: {n} val: {tile[n]}")
        break
