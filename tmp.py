import numpy as np

#x = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 0"
#x = "1 2 3 4 5 6 0 8 9 10 7 12 13 14 11 15"
#x = "1 2 3 4 5 6 7 8 9 10 0 12 13 14 11 15"
x = "1 3 6 4 5 2 11 7 9 10 15 8 13 14 0 12"
tile = x.split()
tile = [int(t) for t in tile]
tile = np.array(tile)
tile = tile.reshape((4, 4))
print(tile)

expected_tile = np.array([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 0]])
start_row, start_col = np.where(tile == 0)
start_row = start_row[0]
start_col = start_col[0]
print(start_row, start_col)
print("-"*60)

def get_value(row, col):
    return (row * 4) + col + 1

moves = 0
for n in range(10):
    if ((tile == expected_tile).all()):
        print("Found")
        print(f"moves: {moves}")
        break
    #expected = get_value(start_row, start_col)

    stop = 0
    paths = []
    dx = [-1, 1,  0, 0]
    dy = [ 0, 0, -1, 1]
    for m in range(4):
        x, y = dx[m], dy[m]
        if (start_row + x) > 3 or (start_row + x) < 0: continue
        if (start_col + y) > 3 or (start_col + y) < 0: continue
        row = start_row + x
        col = start_col + y
        value = tile[row][col]
        if (value != get_value(row, col)): # == expected
            print("incorrect value: ", row, col, value)
            paths.append((x, y))

    if (len(paths) == 1):
        x, y = paths[0]
        row = start_row + x
        col = start_col + y
        value = tile[row][col]
        tile[start_row][start_col] = value
        tile[row][col] = 0
        moves += 1
        start_row = row
        start_col = col
        stop = 1
        print("moved", x, y)
    elif len(paths) > 1:
        print("multiple paths:")
        print(paths)

        index = 0
        if (n == 2): #raise ValueError("stop")
            index = 0
        if (n == 3):
            index = 1

        x, y = paths[index]
        row = start_row + x
        col = start_col + y
        value = tile[row][col]
        #print(get_value(start_row, start_col), get_value(row, col))
        # n0: 0th
        # n1: 0th
        if (value == get_value(start_row, start_col) or 1): # == expected
            print("YO", row, col, value)
            tile[start_row][start_col] = value
            tile[row][col] = 0
            moves += 1
            start_row = row
            start_col = col
            stop = 1
            paths = []
            #break
        if (len(paths)): raise ValueError("fuck")
    print(n)
    print("-"*60)

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
