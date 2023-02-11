#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int pID, pSize;
    char pName[8];
    struct node *link;
} *head, *tail;

struct node* SLL_getNode(int index) {
    if (index < 0 || head == NULL) return NULL;
    
    struct node* ptr;
    int i = 0;
    for (ptr = head; index > i++; ptr = ptr->link)
        if (ptr == NULL) return NULL;
    return ptr;
}

void SLL_insertNode(int index, struct node *temp) {
    struct node *prev, *next;

    if (index == 0 || index == -1 && head == NULL) {
        next = head;
        if (head == NULL) tail = temp;
    } else {
        if (index == -1) tail;
        else if (index > 0) prev = SLL_getNode(index-1); 
        next = prev->link;
    }
    
    temp->link = next;
    if (prev != NULL) prev->link = temp;
    else head = temp;
}

void SLL_insert(int index, int pID, int pSize, char* pName) {
    struct node* temp = malloc(sizeof(struct node));

    strcpy(temp->pName, pName);
    temp->pID = pID;
    temp->pSize = pSize;

    SLL_insertNode(index, temp);
}

void display (char* str) {
    printf("%sSL No.\tName\t\tID\tSize\n", str);
    int sl = 0;
    for (struct node *ptr = head; ptr != NULL; ptr = ptr->link) {
        if (ptr->pID == -2) for (int i = 0; i < 5*8; i++) printf("-");
        else {
            printf("%d\t", sl++);
            if (ptr->pID == -1) printf("Free\t\t\t%d");
            else printf("%s\t%d\t", ptr->pName, ptr->pID);
            printf("%d", ptr->pSize);
        }
        printf("\n");
    }
}

int pickBestFit(int pSize, int maxSize) {
    int index = -1, min = maxSize+10, i = 0;
    for (struct node *ptr = head; ptr != NULL; ptr = ptr->link) {
        if (ptr->pID == -1 && ptr->pSize >= pSize && min > ptr->pSize) {
            min = ptr->pSize;
            index = i;
        }
        i++;
    }
    return index;
}

void create(int pID, int maxSize) {
    int pSize;
    char pName[50];

    printf(">> Enter the process Name: ");
    scanf("%s", &pName);
    pName[8] = '\0';
    printf(">> Enter the process Size: ");
    scanf("%d", &pSize);

    int index = pickBestFit(pSize, maxSize);

    if (index == -1) { printf("Error: Low Memory\n"); return; }
    
    struct node *new = malloc(sizeof(struct node)), *this;

    new->pID = pID;
    strcpy(new->pName, pName);
    new->pSize = pSize;

    SLL_insertNode(index, new);
    this = new->link;
    if (this->pSize == pSize) { new->link = this->link; free(this);}
    else this->pSize -= pSize;

    printf("Process created with ID %d\n", pID);
}

void main() {
    int fBlockMax = 0, maxSize = 0, input, size;

    printf(">> Total Partitions count: ");
    scanf("%d", &fBlockMax);

    SLL_insert(0, -2, 10, "Data");
    for (int i = 0; i < fBlockMax; i++) {
        printf(">> Partition %d Size (KB): ", i);
        scanf("%d", &size);
        if (size > maxSize) maxSize = size;
        SLL_insert(-1, -1, size, "Free");
        SLL_insert(-1, -2, 10, "Data");
    }

    printf("\nMenu:\n  1. Create new process\n  2. View Process List\n  3. Exit\n");
    for (int id = 0; 1; id++) {
        printf(">> ");
        scanf("%d", &input);

        switch (input) {
            case 1: create(id, maxSize); break;
            case 2: display("----Memory----\n"); break;
            case 3: printf("Exiting...\n"); return;
            default: printf("Invalid Input!!!\n");
        }
    }
}