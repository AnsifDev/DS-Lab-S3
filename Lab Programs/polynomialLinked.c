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

void insertAtFirst(struct LinkedList *list, int value) {
    if (list == NULL) return;

    struct node *temp = malloc(sizeof(struct node));
    temp->value = value;
    if (list->head != NULL) temp->link = list->head;
    list->head = temp;
}

void insertAtEnd(struct LinkedList *list, int value) {
    if (list == NULL) return;

    struct node *ptr = list->head, *temp;

    temp = malloc(sizeof(struct node));
    temp->value = value;

    if (ptr == NULL) {
        list->head = temp;
        return;
    }
    while (ptr->link != NULL) ptr = ptr->link;

    if (ptr->link != NULL) temp->link = ptr->link;
    ptr->link = temp;
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

int get(struct LinkedList *list, int index, int *value) {
    if (list == NULL) return 1;

    struct node *temp;

    if (index < 0) return 1;

    temp = getNode(list, index);
    if (temp == NULL) return 1;

    *value = temp->value; 
    return 0;
}

void main() {
    struct LinkedList *poly1, *poly2;

    poly1 = new_LinkedList();
    poly2 = new_LinkedList();

    int poly1_order, poly2_order;
    printf("Enter the order of the polynomial1: ");
    scanf("%d", &poly1_order);

    for (int i = poly1_order; i >= 0; i--) {
        int coeff;
        printf("Coeffient of x^%d: ", i);
        scanf("%d", &coeff);

        insertAtFirst(poly1, coeff);
    }

    printf("Enter the order of the polynomial2: ");
    scanf("%d", &poly2_order);

    for (int i = poly2_order; i >= 0; i--) {
        int coeff;
        printf("Coeffient of x^%d: ", i);
        scanf("%d", &coeff);

        insertAtFirst(poly2, coeff);
    }

    struct LinkedList *sum = new_LinkedList();
    struct Iterator *iter1 = new_Iterator(poly1);
    struct Iterator *iter2 = new_Iterator(poly2);

    while(hasNextNode(iter1) && hasNextNode(iter2)) {
        insertAtEnd(sum, nextNode(iter1)->value + nextNode(iter2)->value);
    }
    
    while(hasNextNode(iter1)) insertAtEnd(sum, nextNode(iter1)->value);
    while(hasNextNode(iter2)) insertAtEnd(sum, nextNode(iter2)->value);

    printf("Sum: ");
    int sum_order = (poly1_order>poly2_order) ? poly1_order : poly2_order;
    for (int i = sum_order; i >=0; i--) {
        int coeff;
        get(sum, i, &coeff);
        if (coeff == 0) continue;
        if (coeff != 1) printf("%d", coeff);
        if (i > 1) printf("x^%d+", i);
        else if (i == 1) printf("x+");
        else if (coeff == 1) printf("%d", coeff);
    }
    printf("\n");
}