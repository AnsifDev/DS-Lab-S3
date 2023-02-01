#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *right, *left;
};

struct LinkedList {
    struct node *start, *end;
};

struct Iterator {
    struct node *next, *prev, **start, **end;
};

struct LinkedList *new_LinkedList() {return malloc(sizeof(struct LinkedList));}

struct Iterator *new_Iterator(struct LinkedList *list) {
    if (list == NULL) return NULL;

    struct Iterator *iter = malloc(sizeof(struct Iterator));
    iter->next = list->start;
    iter->start = &(list->start);
    iter->end = &(list->end);
    return iter;
}

struct node* getNode(struct LinkedList *list, int index) {
    if (list == NULL) return NULL;

    if (index == 0) return list->start;

    struct node *ptr = index>0 ? list->start : list->end;
    for (int i = 0; i != ((index>0)?index:((index*-1)-1)); i++) {
        if (ptr == NULL) return NULL;
        ptr = index>0?ptr->right:ptr->left;
    }

    return ptr;
}

int insert(struct LinkedList *list, int index, int value) {
    if (list == NULL) return 1;

    if (index == 0 || list->end == NULL) {
        struct node *temp = malloc(sizeof(struct node));
        struct node *next = list->start;

        temp->value = value;
        temp->right = list->start;

        if (list->start == NULL) list->end = temp;
        else {
            temp->left = next->left;
            next->left = temp;
        }
        list->start = temp;
    } else if (index == -1) {
        struct node *temp = malloc(sizeof(struct node));
        struct node *prev = list->end;

        temp->value = value;
        temp->left = list->end;
        temp->right = prev->right;

        if (list->end == NULL) list->start = temp;
        else prev->right = temp;
        list->end = temp;
    } else {
        struct node *ptr = getNode(list, index-1);
        if (ptr == NULL) return 1;

        struct node *temp = malloc(sizeof(struct node));
        temp->value = value;

        temp->right = ptr->right;
        temp->left = ptr;
        if (ptr->right != NULL) ptr->right->left = temp;
        else list->end = temp;
        ptr->right = temp;
    }

    return 0;
}

int delete(struct LinkedList *list, int index, int *value) {
    if (list == NULL) return 1;

    struct node *temp, *ptr;

    if (list->start == NULL) return 1;
    
    if (index == 0) {
        temp = list->start;
        list->start = temp->right;
        if (list->start == NULL) list->end == NULL;
        else list->start->left = NULL;
    } else if (index == -1) {
        temp = list->end;
        list->end = temp->left;
        if (list->end == NULL) list->start = NULL;
        else list->end->right = NULL;
    } else {
        ptr = getNode(list, index-1);
        if (ptr == NULL) return 1;
        temp = ptr->right;
        if (temp == NULL) return 1;
        ptr->right = temp->right;
        temp->right->left = ptr;
    }
    
    *value = temp->value;
    free(temp);

    return 0;
}

struct node* nextNode(struct Iterator *iter) {
    if (iter == NULL) return NULL;

    struct node *temp = iter->next;
    if (iter->next != NULL) {
        iter->prev = iter->next;
        iter->next = temp->right;
    }
    return temp;
}

struct node* prevNode(struct Iterator *iter) {
    if (iter == NULL) return NULL;

    struct node *temp = iter->prev;
    if (iter->next != NULL) {
        iter->next = iter->prev;
        iter->prev = temp->left;
    }
    return temp;
}

int hasNextNode(struct Iterator *iter) {
    if (iter == NULL) return 0;
    return iter->next != NULL;
}

int hasPrevNode(struct Iterator *iter) {
    if (iter == NULL) return 0;
    return iter->prev != NULL;
}

void resetIterToStart(struct Iterator *iter) {
    if (iter == NULL) return;
    iter->next = *(iter->start);
    iter->prev = NULL;
}

void resetIterToEnd(struct Iterator *iter) {
    if (iter == NULL) return;
    iter->prev = *(iter->end);
    iter->start = NULL;
}

int get(struct LinkedList *list, int index, int *value) {
    if (list == NULL) return 1;

    struct node *temp;

    temp = getNode(list, index);
    if (temp == NULL) return 1;

    *value = temp->value; 
    return 0;
}

int set(struct LinkedList *list, int index, int value) {
    if (list == NULL) return 1;

    struct node *temp;

    temp = getNode(list, index);
    if (temp == NULL) return 1;

    temp->value = value; 
    return 0;
}

int length(struct LinkedList *list) {
    if (list == NULL) return -1;

    struct Iterator *iter = new_Iterator(list);
    int i = 0;
    while (nextNode(iter) != NULL) i++;
    return i;
}

void main() {}