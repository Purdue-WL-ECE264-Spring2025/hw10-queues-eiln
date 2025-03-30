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
    is_tile_done(start);
    #if 0
    if (is_tile_done(start))
    {
        printf("found\n");
        return 0;
    }
    #endif

    struct linked_list list;
    list.head = NULL;
    insert_at_tail(&list, 3);
    insert_at_tail(&list, 4);
    dump_list(NULL, list);
    free_list(list);

    #if 0
    int dx[4] = {-1,  1,  0,  0};
    int dy[4] = { 0,  0, -1,  1};
    for (int m = 0; m < 4; m++)
    {
        int x = dx[m];
        int y = dy[m];
        if ((start.empty_row + x) > 3 || (start.empty_row + x) < 0) continue;
        if ((start.empty_col + y) > 3 || (start.empty_col + y) < 0) continue;
        int row = start.empty_row + x;
        int col = start.empty_col + y;
        if (start.tiles[row][col] != get_expected_value(row, col))
        {
            printf("incorrect: row: %d col: %d val: %d\n", row, col, start.tiles[row][col]);
        }
    }
    #endif

    return 0;
}
