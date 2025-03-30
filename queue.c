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

static inline int get_dx(int m)
{
    int dx[4] = {-1,  1,  0,  0};
    return dx[m];
}

static inline int get_dy(int m)
{
    int dy[4] = { 0,  0, -1,  1};
    return dy[m];
}

#if 1
static void print_tile(uint8_t t[4][4])
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            printf("%2d ", t[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}
#endif

int test(struct linked_list list)
{
    int ret = 0;

    while (1)
    {
        struct linked_list list_new;
        list_new.head = NULL;

        struct list_node *curr = list.head;
        while (1)
        {
            if (curr == NULL) break;
            struct game_state start = deserialize(curr->value);
            if (is_tile_done(start))
            {
                //printf("found: steps: %d\n", start.num_steps);
                ret = start.num_steps;
                free_list(list);
                return ret;
            }

            int m_list[4] = {-1, -1, -1, -1};
            int m_count = 0;
            for (int m = 0; m < 4; m++)
            {
                int x = get_dx(m);
                int y = get_dy(m);
                if ((start.empty_row + x) > 3 || (start.empty_row + x) < 0) continue;
                if ((start.empty_col + y) > 3 || (start.empty_col + y) < 0) continue;
                int row = start.empty_row + x;
                int col = start.empty_col + y;
                if (start.tiles[row][col] != get_expected_value(row, col))
                {
                    //printf("path: row: %d col: %d val: %d\n", row, col, start.tiles[row][col]);
                    m_list[m_count++] = m;
                }
            }

            for (int i = 0; i < m_count; i++)
            {
                int m = m_list[i];
                struct game_state new;
                memcpy(new.tiles, start.tiles, sizeof(start.tiles));
                int x = get_dx(m);
                int y = get_dy(m);

                int row = start.empty_row + x;
                int col = start.empty_col + y;
                int value = start.tiles[row][col];
                new.tiles[start.empty_row][start.empty_col] = value;
                new.tiles[row][col] = 0;
                new.empty_row = row;
                new.empty_col = col;
                new.num_steps = start.num_steps + 1;

                insert_at_tail(&list_new, serialize(new));
            }
            curr = curr->next;
        }

        //dump_list(NULL, list_new);
        free_list(list);
        list = list_new;
    }

    free_list(list);
#if 0
    struct list_node *c = NULL;
    c = list_new.head;
    for (int n = 0; n < 9; n++)
    {
        if (c == NULL)
            break;
        struct game_state state = deserialize(c->value);
        printf("num_steps: %d\n", state.num_steps);
        print_tile(state.tiles);
        c = c->next;
    }
#endif

    return ret;
}

int number_of_moves(struct game_state start)
{
    print_tile(start.tiles);
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

    insert_at_tail(&list, serialize(start));
    int num_steps = test(list);

    //get_pos(&start, &list);
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

    return num_steps;
}
