#include<stdio.h>
#include<stdlib.h>

struct node {
    int value;
    struct node *right, *left;
} *head;

struct node *getNode(int n) {
    if (head == NULL) return NULL;

    struct node *ptr = head;
    for (int i = 0; i < n; i++) ptr = ptr->right;
    return ptr;
}

void insert(int n, int v) {
    if (n == 0) {
        struct node *temp = malloc(sizeof(struct node));
        temp->value = v;
        if (head != NULL) {
            temp->right = head;
            temp->left = head->left;
            head->left->right = temp;
            head->left = temp;
        } else {
            temp->right = temp;
            temp->left = temp;
        }
        head = temp;
    } else {
        struct node *ptr = getNode(n-1);
        struct node *temp = malloc(sizeof(struct node));
        temp->value = v;
        temp->right = ptr->right;
        temp->left = ptr->right->left;
        ptr->right->left = temp;
        ptr->right = temp;
    }
}

delete(n) {
    struct node *temp = getNode(n);
    int v = temp->value;
    if (temp->right == temp) head = NULL;
    else {
        temp->right->left = temp->left;
        temp->left->right = temp->right;
        if (head == temp) head = temp->right;
    }
    free(temp);
}