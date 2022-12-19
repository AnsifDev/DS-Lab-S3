#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int pID, pSize;
    char pName[8];
    struct node *link;
};

struct SLL {
    struct node *head, *tail;
};

struct SLL* new_SLL() {
    return malloc(sizeof(struct SLL));
}

struct SLL_Iter {
    struct node *ptr, **head;
};

struct SLL_Iter* new_SLL_Iter(struct SLL* list) {
    if (list == NULL) return NULL;
    struct SLL_Iter* iter = malloc(sizeof(struct SLL_Iter));
    iter->ptr = list->head;
    iter->head = &(list->head);
    return iter;
}

int SLL_Iter_hasNextNode(struct SLL_Iter* iter) {
    if (iter == NULL) return 0;
    return iter->ptr != NULL;
}

struct node* SLL_Iter_nextNode(struct SLL_Iter* iter) {
    if (iter == NULL) return NULL;
    struct node* temp = iter->ptr;
    if (temp != NULL) iter->ptr = temp->link;
    return temp;
}

void SLL_Iter_reset(struct SLL_Iter* iter) {
    if (iter == NULL) return;
    iter->ptr = *(iter->head);
}

struct node* SLL_getNode(struct SLL* list, int index) {
    if (list == NULL) return NULL;

    if (index < -2) return NULL;
    if (index == 0) return list->head;
    if (index == -1) return list->tail;
    
    struct node* ptr;
    struct SLL_Iter* iter = new_SLL_Iter(list);
    if (index == -2) {
        if (list->head->link != NULL) while (1) {
            ptr = SLL_Iter_nextNode(iter);
            if (ptr->link->link == NULL) break;
        }
    } else {
        for (int i = 0; i <= index; i++) {
            if (SLL_Iter_hasNextNode(iter)) ptr = SLL_Iter_nextNode(iter);
            else {
                free(iter);
                return NULL;
            }
        }
    }

    free(iter);
    return ptr;
}

int SLL_insertNode(struct SLL* list, int index, struct node* temp) {
    if (list == NULL) return 1;

    if (index == 0 || index == -1 && list->head == NULL) {
        temp->link = list->head;
        list->head = temp;
        if (temp->link == NULL) list->tail = temp;
        return 0;
    }

    struct node* ptr;
    if (index == -1) ptr = SLL_getNode(list, -1);
    else if (index > 0) ptr = SLL_getNode(list, index-1); 
    else return 1;

    if (ptr == NULL) return 1;
    temp->link = ptr->link;
    ptr->link = temp;
    if (temp->link == NULL)  list->tail = temp;
    return 0;
}

int SLL_insert(struct SLL* list, int index, int pID, int pSize, char* pName) {
    if (list == NULL) return 1;
    
    struct node* temp = malloc(sizeof(struct node));
    strcpy(temp->pName, pName);
    temp->pID = pID;
    temp->pSize = pSize;

    int returnCode = SLL_insertNode(list, index, temp);
    if (returnCode == 1) free(temp);
    return returnCode;
}

void display (struct SLL *list, char* str) {
    printf("%s", str);
    struct SLL_Iter *iter = new_SLL_Iter(list);
    printf("SL No.\tName\tID\tSize\n");
    SLL_Iter_reset(iter);
    for (int i = 0; SLL_Iter_hasNextNode(iter); i++) {
        struct node *n = SLL_Iter_nextNode(iter);
        if (n->pID == -2) {
            for (int i = 0; i < 4*8; i++) printf("-");
            printf("\n");
            i--;
        } else {
            printf("%d\t", i);
            if (n->pID == -1) printf("Free\t\t");
            else printf("%s\t%d\t", n->pName, n->pID);
            printf("%d\n", n->pSize);
        }
        
    }
}

void create(struct SLL *memory, int pID, int maxSize) {
    int pSize;
    char pName[50];

    printf("---Creating New Process---\n");
    printf(">> Enter the process Name: ");
    scanf("%s", pName);
    pName[7] = '\0';
    printf(">> Enter the process Size: ");
    scanf("%d", &pSize);
    if (pSize > maxSize) printf("Process Size is too large!!!\n");
    else {
        printf("Process created with ID %d\n", pID);
        struct SLL_Iter *iter = new_SLL_Iter(memory);
        int index = -1, min = maxSize+10;
        for (int i = 0; SLL_Iter_hasNextNode(iter); i++) {
            struct node *n = SLL_Iter_nextNode(iter);
            //printf("Log:\tBlock Size: %d\tProcess Size: %d\tCurrent Min: %d\tCurrent Index: %d\n", size, pSize, min, index);
            if (n->pID == -1 && n->pSize >= pSize && min > n->pSize) {
                min = n->pSize;
                index = i;
            }
        }

        if (index == -1) printf("Error: Process cannot be loaded, Low Memory\n");
        else {
            struct node *this = SLL_getNode(memory, index);
            struct node *new = malloc(sizeof(struct node));

            this->pSize -= pSize;

            new->pID = pID;
            strcpy(new->pName, pName);
            new->pSize = pSize;

            SLL_insertNode(memory, index, new);
            if (this->pSize <= 0) {
                new->link = this->link;
                free(this);
            }
            
            printf("Process: %s,\tpID: %d\t\t[Started]\n", pName, pID);
        }
        free(iter);
    }
}

void main() {
    struct SLL *memory = new_SLL();
    struct SLL_Iter *iter = new_SLL_Iter(memory);
    int fBlockMax = 0;
    int maxSize = 0;

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
            SLL_insert(memory, -1, -1, size, "Free");
            SLL_insert(memory, -1, -2, 10, "Data");
        } else {
            printf("Terminating: Expected size greater than zero!!!\n");
            return;
        }
    }
    SLL_insert(memory, 0, -2, 10, "Data");

    display(memory, "---Current State of Memory---\n");

    int input;

    printf("\n----Menu----\n  1. Create new process\n  2. View Process List\n");
    printf("  3. Exit\n");
    for (int id = 0; 1; id++) {
        printf(">> ");
        scanf("%d", &input);

        switch (input) {
            case 1: create(memory, id, maxSize); break;
            case 2: display(memory, "----Memory----\n"); break;
            case 3: printf("Exiting...\n"); return;
            default: printf("Invalid Input!!!\n");
        }
    }
}