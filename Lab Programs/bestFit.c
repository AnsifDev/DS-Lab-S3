#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int pID, pSize;
    char pName[16];
    struct node *link;
} *head;

struct node* SLL_getNode(int index) {
    if (index < -2) return NULL;
    if (head == NULL) return NULL;
    if (index == -2 && head->link == NULL) return NULL;
    
    struct node* ptr;
    int i = 0;

    for (ptr = head; 1; ptr = ptr->link)
        if (index == -2 && ptr->link->link == NULL) break;
        else if (index == -1 && ptr->link == NULL) break;
        else if (index >= 0) 
            if (ptr == NULL) return NULL;
            else if (index <= i++) break;
    return ptr;
}

void SLL_insertNode(int index, struct node *temp) {
    struct node *prev, *next;

    if (index == 0 || index == -1 && head == NULL) {
        prev = NULL;
        next = head;
    } else {
        if (index == -1) prev = SLL_getNode(-1);
        else if (index > 0) prev = SLL_getNode(index-1); 
        if (prev == NULL) printf("InvalidIndexException: Unable to locate the node at index: %d\n\t@ function SLL_insert(SLL, int, int): void\n", index-1);
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
    printf("%s", str);
    printf("SL No.\tName\t\tID\tSize\n");
    int sl = 0;
    for (struct node *ptr = head; ptr != NULL; ptr = ptr->link) {
        if (ptr->pID == -2) for (int i = 0; i < 5*8; i++) printf("-");
        else {
            printf("%d\t", sl++);
            if (ptr->pID == -1) printf("Free\t\t\t");
            else {
                printf("%s\t", ptr->pName);
                if (strlen(ptr->pName) < 8) printf("\t");
                printf("%d\t", ptr->pID);
            }
            printf("%d", ptr->pSize);
        }
        printf("\n");
    }
}

int pickBestFit(int pSize, int maxSize) {
    int index = -1, min = maxSize+10, i = 0;
    for (struct node *ptr = head; ptr != NULL; ptr = ptr->link) {
        //printf("Log:\tBlock Size: %d\tProcess Size: %d\tCurrent Min: %d\tCurrent Index: %d\n", size, pSize, min, index);
        if (ptr->pID == -1 && ptr->pSize >= pSize && min > ptr->pSize) {
            min = ptr->pSize;
            index = i;
        }
        i++;
    }
    return index;
}

void gets(char* str) {
    int i = 0;
    for (int a = getc(stdin); 1; a = getc(stdin)) {
        if (a == '\n')
            if (i != 0) break;
            else continue;
        str[i++] = a;
    }
    str[i] = '\0';
}

void create(int pID, int maxSize) {
    int pSize;
    char pName[50];

    printf("---Creating New Process---\n");
    printf(">> Enter the process Name: ");
    gets(pName);
    pName[15] = '\0';
    printf(">> Enter the process Size: ");
    scanf("%d", &pSize);

    if (pSize > maxSize) {
        printf("Process Size is too large!!!\n");
        return;
    }

    printf("Process created with ID %d\n", pID);
    int index = pickBestFit(pSize, maxSize);

    if (index == -1) {
        printf("Error: Process cannot be loaded, Low Memory\n");
        return;
    }
    
    struct node *this = SLL_getNode(index);
    struct node *new = malloc(sizeof(struct node));

    this->pSize -= pSize;

    new->pID = pID;
    strcpy(new->pName, pName);
    new->pSize = pSize;

    SLL_insertNode(index, new);
    if (this->pSize <= 0) {
        new->link = this->link;
        free(this);
    }
    
    printf("Process: %s,\tpID: %d\t\t[Started]\n", pName, pID);
}

void main() {

    int fBlockMax = 0, maxSize = 0, input;

    printf("---Creating Memory Partitions---\n");

    printf(">> Total Partitions count: ");
    scanf("%d", &fBlockMax);
    if (fBlockMax <= 0) {
        printf("Terminating: Atleast 1 Partition is expected!!!\n");
        return;
    }

    for (int i = 0; i < fBlockMax; i++) {
        int size;
        printf(">> Partition %d Size (KB): ", i);
        scanf("%d", &size);
        if (size > 0) {
            if (size > maxSize) maxSize = size;
            SLL_insert(-1, -1, size, "Free");
            SLL_insert(-1, -2, 10, "Data");
        } else {
            printf("Terminating: Expected size greater than zero!!!\n");
            return;
        }
    }
    SLL_insert(0, -2, 10, "Data");

    display("---Current State of Memory---\n");

    printf("\n----Menu----\n  1. Create new process\n  2. View Process List\n");
    printf("  3. Exit\n");
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