#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {

}

struct game_state dequeue(struct queue *q) {
    return (struct game_state){0};
}

static int get_expected_value(int row, int col)
{
    if (row == 3 && col == 3) return 0;
    return (row * 4) + col + 1;
}

static int is_tile_done(struct game_state start)
{
    int found = 1;
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            if (start.tiles[row][col] != get_expected_value(row, col))
            {
                found = 0;
                break;
            }
        }
    }
    return found;
}

int number_of_moves(struct game_state start)
{
    if (is_tile_done(start))
    {
        printf("found\n");
        return 0;
    }

    return 0;
}
