#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *link;
};

struct LinkedList {
    struct node *head;
};

struct Iterator {
    struct node *ptr, **head;
};

struct LinkedList *new_LinkedList() {return malloc(sizeof(struct LinkedList));}

struct Iterator *new_Iterator(struct LinkedList *list) {
    if (list == NULL) return NULL;

    struct Iterator *iter = malloc(sizeof(struct Iterator));
    iter->ptr = list->head;
    iter->head = &(list->head);
    return iter;
}

int insert(struct LinkedList *list, int index, int value) {
    if (list == NULL) return 1;

    if (index == 0) {
        struct node *temp = malloc(sizeof(struct node));
        temp->value = value;
        if (list->head != NULL) temp->link = list->head;
        list->head = temp;
    } else {
        if (index < -1) return 1;

        struct node *ptr = list->head, *temp;

        if (index > 0) {
            if (ptr == NULL) return 1;
            for (int i = 0; i != index-1; i++) {
                if (ptr->link == NULL) return 1;
                ptr = ptr->link;
            }
        }
        
        temp = malloc(sizeof(struct node));
        temp->value = value;

        if (index == -1) {
            if (ptr == NULL) {
                list->head = temp;
                return 0;
            }
            while (ptr->link != NULL) ptr = ptr->link;
        }

        if (ptr->link != NULL) temp->link = ptr->link;
        ptr->link = temp;
    }

    return 0;
}

struct node* getNode(struct LinkedList *list, int index) {
    if (list == NULL) return NULL;

    if (index == 0) return list->head;
    else {
        struct node *ptr = list->head;
        if (ptr == NULL) return NULL;
        if (index > 0) {
            for (int i = 0; i != index; i++) {
                if (ptr == NULL) return NULL;
                ptr = ptr->link;
            }
        } else if (index == -1) while (ptr->link != NULL) ptr = ptr->link;
        else if (index == -2) {
            if (ptr->link == NULL) return NULL;
            while (ptr->link->link != NULL) ptr = ptr->link;
        } else return NULL;

        return ptr;
    }
}

int delete(struct LinkedList *list, int index, int *value) {
    if (list == NULL) return 1;

    struct node *temp, *ptr;

    if (list->head == NULL) return 1;
    
    if (index == 0 || index == -1 && list->head->link == NULL) {
        temp = list->head;
        list->head = temp->link;
    } else {
        ptr = getNode(list, index-1);
        if (ptr == NULL) return 1;
        temp = ptr->link;
        if (temp == NULL) return 1;
        ptr->link = temp->link;
    }
    
    *value = temp->value;
    free(temp);

    return 0;
}

struct node* nextNode(struct Iterator *iter) {
    if (iter == NULL) return NULL;

    struct node *temp = iter->ptr;
    if (iter->ptr != NULL) iter->ptr = temp->link;
    return temp;
}

int hasNextNode(struct Iterator *iter) {
    if (iter == NULL) return 0;
    //printf("Log: iter is not NULL\n");
    return iter->ptr != NULL;
}

void resetIter(struct Iterator *iter) {
    if (iter == NULL) return;
    iter->ptr = *(iter->head);
    if (iter->ptr == NULL) printf("Log: Iter reseted\n");
}

int get(struct LinkedList *list, int index, int *value) {
    if (list == NULL) return 1;

    struct node *temp;

    if (index < 0) return 1;

    temp = getNode(list, index);
    if (temp == NULL) return 1;

    *value = temp->value; 
    return 0;
}

int set(struct LinkedList *list, int index, int value) {
    if (list == NULL) return 1;

    struct node *temp;

    if (index < 0) return 1;

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

void main() {
    int size;
    struct LinkedList *list1 = new_LinkedList(), *list2 = new_LinkedList();
    struct Iterator *iter1 = new_Iterator(list1), *iter2 = new_Iterator(list2);

    if (iter1 == NULL) printf("Error in iter1\n");
    if (iter2 == NULL) printf("Error in iter2\n");

    printf("Enter the size: ");
    scanf("%d", &size);

    for (int i = 0; i < size; i++) {
        int value;
        printf("Enter the value for element[%d]: ", i);
        scanf("%d", &value);

        if (insert(list1, -1, value) != 0) {
            printf("Error on inserting!!!\n");
            return;
        }
    }

    resetIter(iter1);
    while (hasNextNode(iter1)) insert(list2, 0, nextNode(iter1)->value);

    
    //printf("Log: %d\n", hasNextNode(iter1));
    resetIter(iter2);
    for (int i = 0; hasNextNode(iter2); i++) printf("Element[%d]: %d\n", i, nextNode(iter2)->value);
}
