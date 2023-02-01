#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *link;
};

struct LinkedList {
    struct node *head, *tail;
};

struct node* getNode(struct LinkedList *list, int index) {
    if (index < 0) return NULL;

    struct node *ptr = list->head;
    for (int i = 0; i < index; i++) {
        if (ptr == NULL) return NULL;
        ptr = ptr->link;
    }
    return ptr;
}

void insertAtFirst(struct LinkedList *list, int value) {
    struct node *temp = malloc(sizeof(struct node));
    temp->value = value;

    temp->link = list->head;
    if (list->head == NULL) list->tail = temp;
    list->head = temp;
}

void insertAtEnd(struct LinkedList *list, int value) {
    if (list->head == NULL) {
        insertAtFirst(list, value);
        return;
    }

    struct node *prev = list->tail;
    struct node *temp = malloc(sizeof(struct node));
    temp->value = value;

    temp->link = prev->link;
    prev->link = temp;
    list->tail = temp;
}

int getInput(struct LinkedList *list, char *str) {
    int order;
    printf("%sEnter the order: ", str);
    scanf("%d", &order);

    for (int i = order; i >= 0; i--) {
        int coeff;
        printf("Coeffient of x^%d: ", i);
        scanf("%d", &coeff);

        insertAtFirst(list, coeff);
    }
    return order;
}

void display(struct LinkedList *list, int order, char *str) {
    printf("%s", str);
    for (int i = order; i >= 0; i--) {
        int coeff = getNode(list, i)->value;
        if (coeff == 0) continue;
        
        if (i != order) printf("+");
        if (coeff != 1 || i == 0) printf("%d", coeff);
        if (i != 0) printf("x");
        if (i > 1) printf("^%d", i);
    }
    printf("\n");
}

void main() {
    struct LinkedList *p1, *p2;

    p1 = malloc(sizeof(struct LinkedList));
    p2 = malloc(sizeof(struct LinkedList));

    int p1_order = getInput(p1, "Polynomial1:\n");
    int p2_order = getInput(p2, "Polynomial2:\n");

    int sum_order = (p1_order>p2_order)? p1_order: p2_order;
    struct LinkedList *sum = malloc(sizeof(struct LinkedList));

    for(int i = 0; i <= sum_order; i++) {
        int v1, v2;
        struct node *n1 = getNode(p1, i);
        struct node *n2 = getNode(p2, i);

        if (n1 == NULL) v1 = 0;
        else v1 = n1->value;
        if (n2 == NULL) v2 = 0;
        else v2 = n2->value;

        insertAtEnd(sum, v1+v2);
    }

    display(p1, p1_order, "Polynomial1: ");
    display(p2, p2_order, "Polynomial2: ");
    display(sum, sum_order, "Sum: ");
}