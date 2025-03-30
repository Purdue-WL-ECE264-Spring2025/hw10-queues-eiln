#include "queue.h"
#include "tile_game.h"
#include <string.h>

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

#if 0
static int check_end(struct game_state start, int move)
{
    int dx[4] = {-1,  1,  0,  0};
    int dy[4] = { 0,  0, -1,  1};
    int x = dx[move];
    int y = dy[move];
}
#endif

static void print_tile(uint8_t t[4][4])
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            printf("%d ", t[row][col]);
        }
    }
}

static int get_pos(struct game_state *start)
{
    uint8_t t[4][4];
    memcpy(t, start->tiles, sizeof(start->tiles));
    print_tile(t);
    #if 0
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            printf("%d ", t[row][col]);
        }
    }
    #endif

#if 0
    // tmp, start_row, start_col
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
#endif
    return 0;
}

int number_of_moves(struct game_state start)
{
    if (is_tile_done(start))
    {
        printf("found\n");
        return 0;
    }

    struct linked_list list;
    list.head = NULL;
    (void)list;
    #if 0
    insert_at_tail(&list, 3);
    insert_at_tail(&list, 4);
    insert_at_tail(&list, 5);
    remove_from_tail(&list);
    remove_from_tail(&list);
    //remove_from_tail(&list);
    dump_list(NULL, list);
    free_list(list);
    #endif

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
            printf("path: row: %d col: %d val: %d\n", row, col, start.tiles[row][col]);
            insert_at_tail(&list, m);
        }
    }

    get_pos(&start);
#if 0
    //uint8_t t[4][4];
    //memcpy(t, start.tiles, sizeof(start.tiles));
    struct list_node *curr = list.head;
    for (int n = 0; n < 9; n++)
    {
        if (curr == NULL)
        {
            break;
        }

        printf("m: %ld\n", curr->value);
        curr = curr->next;
    }
#endif

    return 0;
}
