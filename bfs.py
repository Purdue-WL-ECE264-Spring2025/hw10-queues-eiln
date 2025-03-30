from collections import deque
import time

# Function to check if given position is valid on the chessboard
def is_valid(pos, N):
    x, y = pos
    if x < 0 or y < 0 or x >= N or y >= N:
        return False
    return True

# Function to find the minimum distance of a knight to reach the destination using BFS
def min_distance_knight(start, end, N):
    dx = [-2, -2, -1, -1, 1, 1, 2, 2]
    dy = [-1, 1, -2, 2, -2, 2, -1, 1]

    visited = [[False for j in range(N)] for i in range(N)]
    distance = [[0 for j in range(N)] for i in range(N)]

    x, y = start
    visited[x][y] = True
    q = deque([(x, y)])

    while q:
        curr_x, curr_y = q.popleft()

        if (curr_x, curr_y) == end:
            return distance[curr_x][curr_y]

        for i in range(8):
            new_x, new_y = curr_x + dx[i], curr_y + dy[i]
            if is_valid((new_x, new_y), N) and not visited[new_x][new_y]:
                visited[new_x][new_y] = True
                distance[new_x][new_y] = distance[curr_x][curr_y] + 1
                q.append((new_x, new_y))

    return -1

# Example usage
start = (0, 0)
end = (7, 7)
N = 8

start_time = time.time()
min_distance = min_distance_knight(start, end, N)
end_time = time.time()

if min_distance != -1:
    print("Minimum distance of knight to reach destination:", min_distance)
else:
    print("No path exists.")

print("Time taken:", end_time - start_time, "seconds")
