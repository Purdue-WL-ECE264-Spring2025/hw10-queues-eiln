import numpy as np

x = "1 2 3 4 5 6 0 8 9 10 7 12 13 14 11 15"
x = "1 2 3 4 5 6 7 8 9 10 0 12 13 14 11 15"
#x = "1 3 6 4 5 2 11 7 9 10 15 8 13 14 0 12"
tile = x.split()
tile = [int(t) for t in tile]
tile = np.array(tile)
tile = tile.reshape((4, 4))
print(tile)

start_row, start_col = np.where(tile == 0)
start_row = start_row[0]
start_col = start_col[0]
print(start_row, start_col)
print("-"*60)

def get_value(row, col):
    return (row * 4) + col + 1

moves = 0
for n in range(3):
    if (tile[start_row][start_col] == 0 and start_row == 3 and start_col == 3):
        print("Found")
        print(f"moves: {moves}")
        break
    expected = get_value(start_row, start_col)

    stop = 0
    for x in [-1, 0, 1]:
        if (stop): break
        if (start_row + x) > 3 or (start_row + x) < 0: continue
        for y in [-1, 0, 1]:
            if (x == 0 and y == 0): continue
            if (start_col + y) > 3 or (start_col + y) < 0: continue
            row = start_row + x
            col = start_col + y
            value = tile[row][col]
            if (value == expected):
                print("YO", row, col, value)
                #continue
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
