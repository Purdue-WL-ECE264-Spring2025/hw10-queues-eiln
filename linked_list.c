#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) {
  struct list_node *new = malloc(sizeof(struct list_node));
  //printf("new node: %p: %lx\n", new, value);
  new->value = value;
  new->next = NULL;
  return new;
}

void insert_at_head(struct linked_list *list, size_t value) {
}

void insert_at_tail(struct linked_list *list, size_t value) {
  struct list_node *curr = list->head;
  if (curr == NULL)
  {
    list->head = new_node(value);
  }
  else
  {
    while (1)
    {
      if (curr->next == NULL)
        break;
      else
        curr = curr->next;
    }
    curr->next = new_node(value);
  }
}

size_t remove_from_head(struct linked_list *list) {
  struct list_node *curr = list->head;
  size_t value = curr->value;
  list->head = curr->next;
  free(curr);
  return value;
}

size_t remove_from_tail(struct linked_list *list)
{
  struct list_node *prev = NULL;
  struct list_node *curr = list->head;
  size_t value = 0;
  if (curr == NULL)
  {
    ;
  }
  else
  {
    while (1)
    {
      if (curr->next == NULL)
      {
        break;
      }
      else
      {
        prev = curr;
        curr = curr->next;
      }
    }
    value = curr->value;
    free(curr);
    if (prev) prev->next = NULL;
  }

  return value;
}

void free_list(struct linked_list list)
{
  struct list_node *curr = list.head;
  int count = 0;
  if (!curr) return;
  while (1)
  {
    if (curr->next == NULL)
    {
      break;
    }
    else
    {
      curr = curr->next;
      count++;
    }
  }
  for (int i = 0; i < count; i++)
  {
    remove_from_tail(&list);
  }
  list.head->next = NULL;
  free(list.head);
  //printf("head: %p\n", list.head);
  //list.head = NULL;
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  (void)fp;
  printf("[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    printf("%zu ", cur->value);
  }
  printf("]\n");
}
