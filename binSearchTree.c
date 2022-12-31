#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *left, *right;
};

struct BinTree {
    struct node *root;
};

struct BinTree *new_BinTree() {
    return malloc(sizeof(struct BinTree));
}

int BinTree_insert(struct BinTree *self, int value) {
    if (self == NULL) return 1;

    struct node *ptr = self->root;
    struct node *new = malloc(sizeof(struct node));
    new->value = value;
    if (ptr == NULL) self->root = new;
    else
        while(1)
            if (ptr->value == value) return 1;
            else if (ptr->value > value)
                if (ptr->left == NULL) {
                    ptr->left = new;
                    break;
                } else ptr = ptr->left;
            else if (ptr->value < value)
                if (ptr->right == NULL) {
                    ptr->right = new;
                    break;
                } else ptr = ptr->right;
    return 0;
}

void insert(struct BinTree *tree) {
    int value;
    printf(">> Enter the value: ");
    scanf("%d", &value);

    if (BinTree_insert(tree, value) == 0) printf("Inserted\n");
    else printf("Insertion failed\n");
}

void viewTree_Pre (struct node *tree) {
    printf("\t%d", tree->value);
    if (tree->left != NULL) viewTree_Pre(tree->left);
    if (tree->right != NULL) viewTree_Pre(tree->right);
}

void pre(struct BinTree *tree) {
    printf("Tree in Pre order: ");
    if (tree->root != NULL) viewTree_Pre(tree->root);
    printf("\n");
}

void viewTree_In (struct node *tree) {
    if (tree->left != NULL) viewTree_In(tree->left);
    printf("\t%d", tree->value);
    if (tree->right != NULL) viewTree_In(tree->right);
}

void in(struct BinTree *tree) {
    printf("Tree in In order: ");
    if (tree->root != NULL) viewTree_In(tree->root);
    printf("\n");
}

void viewTree_Post (struct node *tree) {
    if (tree->left != NULL) viewTree_Post(tree->left);
    if (tree->right != NULL) viewTree_Post(tree->right);
    printf("\t%d", tree->value);
}

void post(struct BinTree *tree) {
    printf("Tree in Post order: ");
    if (tree->root != NULL) viewTree_Post(tree->root);
    printf("\n");
}

int getNodeChildrenStatus(struct node *n) {
    if (n == NULL) return -2;
    if (n->left == NULL)
        if (n->right == NULL) return 0;
        return 1;
    if (n->right == NULL) return -1;
    return 2;
}

void deleteNode(struct BinTree *tree, int value, struct node *offset) {
    int ch = getNodeChildrenStatus(tree->root);

    if (ch == -2) return;
    if (tree->root->value == value) {
        if (ch == 0) {
            free(tree->root);
            tree->root = NULL;
            return;
        }
        
        struct node *replaceNode;
        if (ch == -1) {
            replaceNode = tree->root->left;
            while (replaceNode->right != NULL) replaceNode = replaceNode->right;
        } else if (ch > 0) {
            replaceNode = tree->root->right;
            while (replaceNode->left != NULL) replaceNode = replaceNode->left;
        }
        int replaceValue = replaceNode->value;
        deleteNode(tree, replaceValue, NULL);
        tree->root->value = replaceValue; 
    } else {
        struct node *dNode, *pNode;
        if (offset == NULL) dNode = tree->root;
        else if (offset->value != value) dNode = offset;
        else dNode = tree->root;

        while (dNode->value != value) {
            pNode = dNode;
            if (dNode->value > value) dNode = dNode->left;
            else dNode = dNode->right;
            if (dNode == NULL) return;
        }

        ch = getNodeChildrenStatus(dNode);
        if (ch == 0) {
            if (pNode->left == dNode) {
                free(pNode->left);
                pNode->left = NULL;
            } else {
                free(pNode->right);
                pNode->right = NULL;
            }
            return;
        }
        
        struct node *replaceNode;
        if (ch == -1) {
            replaceNode = dNode->left;
            while (replaceNode->right != NULL) replaceNode = replaceNode->right;
        } else if (ch > 0) {
            replaceNode = dNode->right;
            while (replaceNode->left != NULL) replaceNode = replaceNode->left;
        }
        int replaceValue = replaceNode->value;
        deleteNode(tree, replaceValue, dNode);
        dNode->value = replaceValue; 
    }
}

void delete(struct BinTree *tree) {
    if (tree == NULL) return;

    int value;
    printf("Value to delete: ");
    scanf("%d", &value);

    deleteNode(tree, value, NULL);
}

void main() {
    struct BinTree *tree = new_BinTree();

    printf("---Menu---\n  1. Insert\n  2. Pre-oder\n  3. In-oder\n  4. Post-order\n  5. Delete\n  6. Exit\n");

    int input;
    while(1) {
        printf(">> ");
        scanf("%d", &input);

        switch (input) {
            case 1: insert(tree); break;
            case 2: pre(tree); break;
            case 3: in(tree); break;
            case 4: post(tree); break;
            case 5: delete(tree); break;
            case 6: printf("Exiting...\n"); return;
        }
    }
}