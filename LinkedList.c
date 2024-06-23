#include <stdio.h>
#include <stdlib.h>


typedef struct node_t
{
    int data;
    struct node_t *next;
} node_t;

node_t *head = NULL;

void insert(int index, int data)
{
    node_t *node = malloc(sizeof(node_t) * 1);
    node->data = data;
    node->next = NULL;

    if (head == NULL) {
        head = node;
        return;
    }

    int idx = 0;
    node_t *prev = NULL;
    node_t * cur = head;

    // iterate over the list until `index` or the end of list
    while (cur != NULL && idx != index) {
        ++idx;
        prev = cur;
        cur = cur->next;
    }

    // if the index is at the beginning, update head
    if (idx == 0) {
        head = node;
        node->next = cur;
        return;
    }

    // end
    if (cur == NULL) {
        prev->next = node;
        return;
    }

    prev->next = node;
    node->next = cur;
}

void print_list()
{
    node_t *temp = head;

    while (temp != NULL) {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
}

int main(int argc, char **argv)
{
    insert(0, 1);
    insert(2, 3);
    insert(1, 2);
    insert(4, 5);
    insert(3, 4);
    print_list();
    return 0;
}