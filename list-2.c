// list/list.c
// Implementation for linked list.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

list_t *list_alloc() {
    list_t *mylist = (list_t *)malloc(sizeof(list_t));
    mylist->head = NULL;
    return mylist;
}

void list_free(list_t *l) {
    node_t *current = l->head;
    node_t *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(l);
}

void list_print(list_t *l) {
    node_t *current = l->head;
    while (current != NULL) {
        printf("%d->", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

char *listToString(list_t *l) {
    char *buf = (char *)malloc(sizeof(char) * 1024);
    char tbuf[20];
    node_t *curr = l->head;
    buf[0] = '\0';  // Start with an empty string
    while (curr != NULL) {
        sprintf(tbuf, "%d->", curr->value);
        strcat(buf, tbuf);
        curr = curr->next;
    }
    strcat(buf, "NULL");
    return buf;
}

int list_length(list_t *l) {
    int count = 0;
    node_t *current = l->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void list_add_to_back(list_t *l, elem value) {
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->value = value;
    new_node->next = NULL;
    if (l->head == NULL) {
        l->head = new_node;
    } else {
        node_t *current = l->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void list_add_to_front(list_t *l, elem value) {
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->value = value;
    new_node->next = l->head;
    l->head = new_node;
}

void list_add_at_index(list_t *l, elem value, int index) {
    if (index == 0) {
        list_add_to_front(l, value);
        return;
    }
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->value = value;
    node_t *current = l->head;
    int i;  // Declare the loop variable outside of the for loop
    for (i = 0; i < index - 1 && current != NULL; i++) {
        current = current->next;
    }
    if (current == NULL) {
        free(new_node);
        return;
    }
    new_node->next = current->next;
    current->next = new_node;
}

elem list_remove_from_back(list_t *l) {
    if (l->head == NULL) return -1;
    node_t *current = l->head;
    node_t *previous = NULL;
    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }
    if (previous == NULL) {
        l->head = NULL;
    } else {
        previous->next = NULL;
    }
    elem value = current->value;
    free(current);
    return value;
}

elem list_remove_from_front(list_t *l) {
    if (l->head == NULL) return -1;
    node_t *to_remove = l->head;
    elem value = to_remove->value;
    l->head = to_remove->next;
    free(to_remove);
    return value;
}

elem list_remove_at_index(list_t *l, int index) {
    if (index == 0) {
        return list_remove_from_front(l);
    }
    node_t *current = l->head;
    node_t *previous = NULL;
    int i;  // Declare the loop variable outside of the for loop
    for (i = 0; i < index && current != NULL; i++) {
        previous = current;
        current = current->next;
    }
    if (current == NULL) return -1;
    previous->next = current->next;
    elem value = current->value;
    free(current);
    return value;
}

bool list_is_in(list_t *l, elem value) {
    node_t *current = l->head;
    while (current != NULL) {
        if (current->value == value) return true;
        current = current->next;
    }
    return false;
}

elem list_get_elem_at(list_t *l, int index) {
    node_t *current = l->head;
    int i;  // Declare the loop variable outside of the for loop
    for (i = 0; i < index && current != NULL; i++) {
        current = current->next;
    }
    if (current == NULL) return -1;
    return current->value;
}

int list_get_index_of(list_t *l, elem value) {
    node_t *current = l->head;
    int index = 0;
    while (current != NULL) {
        if (current->value == value) return index;
        current = current->next;
        index++;
    }
    return -1;
}
