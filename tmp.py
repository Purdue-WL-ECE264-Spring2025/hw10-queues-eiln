import numpy as np
from collections import deque
from copy import deepcopy

#x = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 0"
#x = "1 2 3 4 5 6 0 8 9 10 7 12 13 14 11 15" # 3
#x = "1 2 3 4 5 6 7 8 9 10 0 12 13 14 11 15"  # 2
x = "1 3 6 4 5 2 11 7 9 10 15 8 13 14 0 12"
#x = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 0 15"
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
start_row_og = start_row
start_col_og = start_col

def get_value(row, col):
    return (row * 4) + col + 1

def check_end(tile, q):
    t = tile.copy()
    start_row = start_row_og
    start_col = start_col_og
    for n in range(len(q)):
        x, y = q[n]
        row = start_row + x
        col = start_col + y
        t[start_row][start_col] = t[row][col]
        t[row][col] = 0
        start_row = row
        start_col = col
    if ((t == expected_tile).all()):
        print("Found")
        return True
    else: return False

def get_pos(tile, q):
    t = tile.copy()
    start_row = start_row_og
    start_col = start_col_og
    for n in range(len(q)):
        x, y = q[n]
        #x, y = q.popleft()
        #print(x, y)
        row = start_row + x
        col = start_col + y
        t[start_row][start_col] = t[row][col]
        t[row][col] = 0
        start_row = row
        start_col = col
    return t, start_row, start_col

pot = []
moves = 0
for n in range(1):
    if ((tile == expected_tile).all()):
        print("Found")
        print(f"moves: {moves}")
        break
    #expected = get_value(start_row, start_col)

    paths = []
    dx = [-1, 1,  0, 0]
    dy = [ 0, 0, -1, 1]
    for m in range(4):
        x, y = dx[m], dy[m]
        if (start_row_og + x) > 3 or (start_row_og + x) < 0: continue
        if (start_col_og + y) > 3 or (start_col_og + y) < 0: continue
        row = start_row_og + x
        col = start_col_og + y
        value = tile[row][col]
        if (value != get_value(row, col)): # == expected
            print("incorrect value: ", row, col, value)
            paths.append((x, y))
            pot.append(deque([(x, y)]))

print(pot)
print("-"*60)

found = 0
for n in range(9):
    paths = []
    if (found): break
    for p in range(len(pot)):
        if (check_end(tile, pot[p])):
            found = 1
            print("FOUND")
            print(f"moves: {len(pot[p])}")
            break
        else:
            tmp, start_row, start_col = get_pos(tile, pot[p])
            #print(tmp)
            dx = [-1, 1,  0, 0]
            dy = [ 0, 0, -1, 1]
            #tmp_paths = []
            for m in range(4):
                x, y = dx[m], dy[m]
                if (start_row + x) > 3 or (start_row + x) < 0: continue
                if (start_col + y) > 3 or (start_col + y) < 0: continue
                row = start_row + x
                col = start_col + y
                value = tmp[row][col]
                if (value != get_value(row, col)): # == expected
                    print("incorrect value: ", row, col, value)
                    q = deepcopy(pot[p])
                    q.append((x, y))
                    paths.append(q)
                    #tmp_paths.append((x, y))
                    #paths.append((x, y))
                    #pot[p].append((x, y))
        print("="*50)
        #print(pot)
        #print(paths)
        #pot = paths
    if (found): break
    #print(paths)
    pot = paths
