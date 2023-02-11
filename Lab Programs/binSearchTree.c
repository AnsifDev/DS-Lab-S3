#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *left, *right;
} *root;

int BinTree_insert(int value) {
    struct node *ptr = root;
    struct node *new = malloc(sizeof(struct node));
    new->value = value;

    if (ptr == NULL) root = new;
    else
        while(1)
            if (value == ptr->value) return 1;
            else if (value < ptr->value)
                if (ptr->left == NULL) {
                    ptr->left = new;
                    break;
                } else ptr = ptr->left;
            else if (value > ptr->value)
                if (ptr->right == NULL) {
                    ptr->right = new;
                    break;
                } else ptr = ptr->right;
    return 0;
}

void insert() {
    int value;
    printf(">> Enter the value: ");
    scanf("%d", &value);

    if (BinTree_insert(value) == 0) printf("Inserted\n");
    else printf("Insertion failed\n");
}

void pre (struct node *ptr) {
    printf("\t%d", ptr->value);
    if (ptr->left != NULL) viewTree_Pre(ptr->left);
    if (ptr->right != NULL) viewTree_Pre(ptr->right);
}

void in (struct node *ptr) {
    if (ptr->left != NULL) viewTree_In(ptr->left);
    printf("\t%d", ptr->value);
    if (ptr->right != NULL) viewTree_In(ptr->right);
}

void post (struct node *ptr) {
    if (ptr->left != NULL) viewTree_Post(ptr->left);
    if (ptr->right != NULL) viewTree_Post(ptr->right);
    printf("\t%d", ptr->value);
}

void main() {
    printf("---Menu---\n  1. Insert\n  2. Pre-oder\n  3. In-oder\n  4. Post-order\n  5. Exit\n");

    int input;
    while(1) {
        printf(">> ");
        scanf("%d", &input);

        switch (input) {
            case 1: insert(); break;
            case 2: printf("Tree in Pre order: "); pre(root); break;
            case 3: printf("Tree in In order: "); in(root); break;
            case 4: printf("Tree in Post order: "); post(root); break;
            case 5: printf("Exiting...\n"); return;
        }
    }
}