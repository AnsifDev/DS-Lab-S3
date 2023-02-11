#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int pID, pSize;
    char pName[16];
    struct node *link;
};

struct SLL {
    struct node *head, *tail;
};

struct SLL* new_SLL() {
    return malloc(sizeof(struct SLL));
}

struct node* SLL_getNode(struct SLL* list, int index) {
    if (list == NULL) printf("NullPointerException: Parameter passed as SLL is NULL\n\t@ function SLL_getNode(SLL, int, int): node\n");
    
    if (index < -2) return NULL;
    if (list->head == NULL);
    if (index == -2 && list->head->link == NULL) return NULL;
    
    struct node* ptr;
    int i = 0;

    for (ptr = list->head; 1; ptr = ptr->link)
        if (index == -2 && ptr->link->link == NULL) break;
        else if (index == -1 && ptr->link == NULL) break;
        else if (index >= 0) 
            if (ptr == NULL) return NULL;
            else if (index <= i++) break;
    return ptr;
}

void SLL_insertNode(struct SLL* list, int index, struct node *temp) {
    if (list == NULL) printf("NullPointerException: Parameter passed as SLL is NULL\n\t@ function SLL_insert(SLL, int, int): void\n");
    
    struct node *prev, *next;

    if (index == 0 || index == -1 && list->head == NULL) {
        prev = NULL;
        next = list->head;
    } else {
        if (index == -1) prev = SLL_getNode(list, -1);
        else if (index > 0) prev = SLL_getNode(list, index-1); 
        if (prev == NULL) printf("InvalidIndexException: Unable to locate the node at index: %d\n\t@ function SLL_insert(SLL, int, int): void\n", index-1);
        next = prev->link;
    }
    
    temp->link = next;
    if (prev != NULL) prev->link = temp;
    else list->head = temp;
}

struct node *SLL_deleteNode(struct SLL* list, int index) {
    if (list == NULL) printf("NullPointerException: Parameter passed as SLL is NULL\n\t@ function SLL_delete(SLL, int): int\n");
    
    struct node *temp, *prev, *next;
    if (index == 0 || index == -1 && list->head->link == NULL) {
        prev = NULL;
        temp = list->head;
    } else if (index > -2) {
        prev = SLL_getNode(list, index-1);
        if (prev == NULL) printf("InvalidIndexException: Unable to locate the node at index: %d\n\t@ function SLL_delete(SLL, int, int): void\n", index-1);
        temp = prev->link;
    }

    if (temp == NULL) printf("InvalidIndexException: Unable to locate the node at index: %d\n\t@ function SLL_delete(SLL, int, int): void\n", index);
    next = temp->link;
    
    if (prev != NULL) prev->link = next;
    else list->head = next;
    
    return temp;
}

int SLL_insert(struct SLL* list, int index, int pID, int pSize, char* pName) {
    if (list == NULL) return 1;
    
    struct node* temp = malloc(sizeof(struct node));
    strcpy(temp->pName, pName);
    temp->pID = pID;
    temp->pSize = pSize;

    SLL_insertNode(list, index, temp);
}

void display (struct SLL* list, char* str) {
    printf("%s", str);
    printf("SL No.\tName\tID\tSize\n");
    int sl = 0;
    for (struct node *ptr = list->head; ptr != NULL; ptr = ptr->link) {
        if (ptr->pID == -2) for (int i = 0; i < 4*8; i++) printf("-");
        else {
            printf("%d\t", sl++);
            if (ptr->pID == -1) printf("Free\t\t");
            else printf("%s\t%d\t", ptr->pName, ptr->pID);
            printf("%d", ptr->pSize);
        }
        printf("\n");
    }
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

void create(struct SLL *memory, struct SLL *que, int pID, int maxSize) {
    int pSize;
    char pName[50];

    printf("---Creating New Process---\n");
    printf(">> Enter the process Name: ");
    gets(pName);
    pName[15] = '\0';
    printf(">> Enter the process Size: ");
    scanf("%d", &pSize);
    if (pSize > maxSize) printf("Process Size is too large!!!\n");
    else {
        printf("Process created with ID %d\n", pID);
        int index = -1, min = maxSize+10, i = 0;
        for (struct node *n = memory->head; n != NULL; n = n->link) {
            //printf("Log:\tBlock Size: %d\tProcess Size: %d\tCurrent Min: %d\tCurrent Index: %d\n", size, pSize, min, index);
            if (n->pID == -1 && n->pSize >= pSize && min > n->pSize) {
                min = n->pSize;
                index = i;
            }
            i++;
        }

        if (index == -1) {
            printf("Process: %s,\tpID: %d\t\t[Queued]\n", pName, pID);
            SLL_insert(que, -1, pID, pSize, pName);
        } else {
            struct node *prev = SLL_getNode(memory, index-1);
            struct node *this = prev->link;
            struct node *new = malloc(sizeof(struct node));

            this->pSize -= pSize;
            new->pID = pID;
            strcpy(new->pName, pName);
            new->pSize = pSize;
            if (this->pSize > 0) new->link = this;
            else {
                new->link = this->link;
                free(this);
            }
            prev->link = new;
            printf("Process: %s,\tpID: %d\t\t[Started]\n", pName, pID);
        }
    }
}

void stop(struct SLL *memory, struct SLL *que) {

    int pID;
    printf(">> Enter the process id: ");
    scanf("%d", &pID);

    if (pID < 0) {
        printf("No process found with ID %d\n", pID);
        return;
    }

    int index = -1, min = 0, i = 0;
    for (struct node *ptr = memory->head; ptr != NULL; ptr = ptr->link) {
        int id = ptr->pID;
        if (pID == id) {
            index = i;
            break;
        }
        i++;
    }

    if (index == -1) {
        int i = 0;
        for (struct node *ptr = que->head; ptr != NULL; ptr = ptr->link) {
        int id = ptr->pID;
            if (pID == id) {
                index = i;
                break;
            }
            i++;
        }

        if (index == -1) printf("No process found with ID %d\n", pID);
        else {
            struct node *n = SLL_deleteNode(que, index);
            printf("Process:%s,\tpID: %d\t\t[Dequeued]\n", n->pName, pID);
            free(n);
        }
    } else {
        struct node *this, *prev, *post;
        prev = SLL_getNode(memory, index-1);
        this = prev->link;
        post = this->link;

        this->pID = -1;
        printf("Process: %s,\tpID: %d\t\t[Stopped]\n", this->pName, pID);

        if (prev->pID == -1) {
            this->pSize += prev->pSize;
            prev = SLL_deleteNode(memory, index-1);
            free(prev);
            index--;
            prev = SLL_getNode(memory, index-1);
        }

        if (post->pID == -1) {
            this->pSize += post->pSize;
            this->link = post->link;
            free(post);
        }

        
        struct node *ptr = que->head;
        for (int i = 0; ptr != NULL; i++) {
            struct node *process = ptr;
            ptr = ptr->link;
            if (process->pSize <= this->pSize) {
                process = SLL_deleteNode(que, i);
                this->pSize -= process->pSize;

                if (this->pSize > 0) process->link = this;
                else {
                    process->link = this->link;
                    free(this);
                }

                i--;
                prev->link = process;
                prev = process;
                printf("Process: %s,\tpID: %d\t\t[Started]\n", process->pName, process->pID);
            }
        }
    }
}

void main() {
    struct SLL *memory = new_SLL();
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

    struct SLL *Queue = new_SLL();
    int input;

    printf("\n----Menu----\n  1. Create new process\n  2. View Process List\n");
    printf("  3. Stop a process\n  4. View QueueList\n  5. Exit\n");
    for (int id = 0; 1; id++) {
        printf(">> ");
        scanf("%d", &input);

        switch (input) {
            case 1: create(memory, Queue, id, maxSize); break;
            case 2: display(memory, "----Memory----\n"); break;
            case 3: stop(memory, Queue); break;
            case 4: display(Queue, "---Queued Process---\n"); break;
            case 5: printf("Exiting...\n"); return;
            default: printf("Invalid Input!!!\n");
        }
    }
}