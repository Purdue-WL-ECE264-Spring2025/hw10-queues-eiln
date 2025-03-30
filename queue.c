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

#if 0

static int get_pos(struct game_state *start, struct linked_list *list)
{
    uint8_t t[4][4];
    memcpy(t, start->tiles, sizeof(start->tiles));

    int start_row = start->empty_row;
    int start_col = start->empty_col;

    for (int m = 0; m < m_count; m++)
    {
        int x = get_dx(m);
        int y = get_dy(m);

        int row = start_row + x;
        int col = start_col + y;

        t[start_row][start_col] = t[row][col];
        t[row][col] = 0;
        start_row = row;
        start_col = col;
    }

#if 0
    // traverse ll
    struct list_node *curr = list->head;

    // transform T
    while (1)
    {
        if (curr == NULL)
            break;

        int m = curr->value;
        int x = get_dx(m);
        int y = get_dy(m);

        int row = start_row + x;
        int col = start_col + y;

        t[start_row][start_col] = t[row][col];
        t[row][col] = 0;
        start_row = row;
        start_col = col;

        curr = curr->next;
    }
    print_tile(t);
#endif
#if 0
    // find new paths
    int m_list[4] = {-1, -1, -1, -1};
    int m_count = 0;
    for (int m = 0; m < 4; m++)
    {
        int x = get_dx(m);
        int y = get_dy(m);
        if ((start_row + x) > 3 || (start_row + x) < 0) continue;
        if ((start_col + y) > 3 || (start_col + y) < 0) continue;
        int row = start_row + x;
        int col = start_col + y;
        int value = t[row][col];
        if (value != get_expected_value(row, col))
        {
            printf("path: row: %d col: %d val: %d\n", row, col, value);
            m_list[m_count++] = m;
        }
    }

    struct game_state new;
    memcpy(new.tiles, t, sizeof(start->tiles));
    new.empty_row = start_row;
    new.empty_col = start_col;
#endif
    return 0;
}
#endif

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

    //insert_at_tail(&list, serialize(start));

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
            printf("path: row: %d col: %d val: %d\n", row, col, start.tiles[row][col]);
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
        insert_at_tail(&list, serialize(new));
    }
    
    dump_list(NULL, list);

    struct list_node *curr = list.head;
    while (1)
    {
        if (curr == NULL) break;
        struct game_state state = deserialize(curr->value);
        print_tile(state.tiles);
        curr = curr->next;
    }

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

    return 0;
}
