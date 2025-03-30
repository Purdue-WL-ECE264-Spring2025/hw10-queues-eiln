import numpy as np

x = "1 2 3 4 5 6 0 8 9 10 7 12 13 14 11 15"
tile = x.split()
tile = [int(t) for t in tile]
tile = np.array(tile)
tile = tile.reshape((4, 4))
print(tile)

start_row, start_col = np.where(tile == 0)
start_row = start_row[0]
start_col = start_col[0]
print(start_row, start_col)

def get_value(row, col):
    return (row * 4) + col + 1

expected = get_value(start_row, start_col)
print(expected)
moves = 0

stop = 0
for x in [-1, 0, 1]:
    if (stop): break
    for y in [-1, 0, 1]:
        if (x == 0 and y == 0): continue
        row = start_row + x
        col = start_col + y
        value = tile[row][col]
        if (value == expected):
            print("YO", row, col, value)
            tile[start_row][start_col] = value
            tile[row][col] = 0
            moves += 1
            start_row = row
            start_col = col
            stop = 1
            break

print(tile)
print(start_row, start_col)


start_row = 0
start_col = 0

for row in range(4):
    for col in range(4):
        if tile[row][col] == 0:
            start_row = row
            start_col = col
            found = 1
            break

        #if (((row * 4) + col + 1) != tile[row][col]):
        #    print(f"stop: row: {row} col: {col} val: {tile[row][col]}")
        #    break
