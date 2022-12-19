#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int pID, pSize;
    char pName[8];
    struct node *link;
};

struct SinglyLinkedList {
    struct node *head, *tail;
};

struct SinglyLinkedList* new_SinglyLinkedList() {
    return malloc(sizeof(struct SinglyLinkedList));
}

struct SinglyLinkedList_Iterator {
    struct node *ptr, **head;
};

struct SinglyLinkedList_Iterator* new_SinglyLinkedList_Iterator(struct SinglyLinkedList* list) {
    if (list == NULL) return NULL;
    struct SinglyLinkedList_Iterator* iter = malloc(sizeof(struct SinglyLinkedList_Iterator));
    iter->ptr = list->head;
    iter->head = &(list->head);
    return iter;
}

int SinglyLinkedList_Iterator_hasNextNode(struct SinglyLinkedList_Iterator* iter) {
    if (iter == NULL) return 0;
    return iter->ptr != NULL;
}

struct node* SinglyLinkedList_Iterator_nextNode(struct SinglyLinkedList_Iterator* iter) {
    if (iter == NULL) return NULL;
    struct node* temp = iter->ptr;
    if (temp != NULL) iter->ptr = temp->link;
    return temp;
}

void SinglyLinkedList_Iterator_reset(struct SinglyLinkedList_Iterator* iter) {
    if (iter == NULL) return;
    iter->ptr = *(iter->head);
}

struct node* SinglyLinkedList_getNode(struct SinglyLinkedList* list, int index) {
    if (list == NULL) return NULL;

    if (index < -2) return NULL;
    if (index == 0) return list->head;
    if (index == -1) return list->tail;
    
    struct node* ptr;
    struct SinglyLinkedList_Iterator* iter = new_SinglyLinkedList_Iterator(list);
    if (index == -2) {
        if (list->head->link != NULL) while (1) {
            ptr = SinglyLinkedList_Iterator_nextNode(iter);
            if (ptr->link->link == NULL) break;
        }
    } else {
        for (int i = 0; i <= index; i++) {
            if (SinglyLinkedList_Iterator_hasNextNode(iter)) ptr = SinglyLinkedList_Iterator_nextNode(iter);
            else {
                free(iter);
                return NULL;
            }
        }
    }

    free(iter);
    return ptr;
}

int SinglyLinkedList_insertNode(struct SinglyLinkedList* list, int index, struct node* temp) {
    if (list == NULL) return 1;

    if (index == 0 || index == -1 && list->head == NULL) {
        temp->link = list->head;
        list->head = temp;
        if (temp->link == NULL) list->tail = temp;
        return 0;
    }

    struct node* ptr;
    if (index == -1) ptr = SinglyLinkedList_getNode(list, -1);
    else if (index > 0) ptr = SinglyLinkedList_getNode(list, index-1); 
    else return 1;

    if (ptr == NULL) return 1;
    temp->link = ptr->link;
    ptr->link = temp;
    if (temp->link == NULL)  list->tail = temp;
    return 0;
}

struct node* SinglyLinkedList_deleteNode(struct SinglyLinkedList* list, int index) {
    if (list == NULL) return NULL;

    struct node* temp;
    if (index == 0) {
        temp = list->head;
        list->head = temp->link;
        if (list->head == NULL) list->tail = NULL;
    } else if (index > -2) {
        struct node* ptr = SinglyLinkedList_getNode(list, index-1);
        if (ptr == NULL) return NULL;
        temp = ptr->link;
        ptr->link = temp->link;
        if (ptr->link == NULL) list->tail = ptr;
    } else return NULL;

    return temp;
}

int SinglyLinkedList_insert(struct SinglyLinkedList* list, int index, int pID, int pSize, char pName[8]) {
    if (list == NULL) return 1;
    
    struct node* temp = malloc(sizeof(struct node));
    strcpy(temp->pName, pName);
    temp->pID = pID;
    temp->pSize = pSize;

    int returnCode = SinglyLinkedList_insertNode(list, index, temp);
    if (returnCode == 1) free(temp);
    return returnCode;
}

void display (struct SinglyLinkedList *list, char* str) {
    printf("%s", str);
    struct SinglyLinkedList_Iterator *iter = new_SinglyLinkedList_Iterator(list);
    printf("SL No.\tName\tID\tSize\n");
    SinglyLinkedList_Iterator_reset(iter);
    for (int i = 0; SinglyLinkedList_Iterator_hasNextNode(iter); i++) {
        struct node *n = SinglyLinkedList_Iterator_nextNode(iter);
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

void create(struct SinglyLinkedList *memory, struct SinglyLinkedList *que, int pID, int maxSize) {
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
        struct SinglyLinkedList_Iterator *iter = new_SinglyLinkedList_Iterator(memory);
        int index = -1, min = maxSize+10;
        for (int i = 0; SinglyLinkedList_Iterator_hasNextNode(iter); i++) {
            struct node *n = SinglyLinkedList_Iterator_nextNode(iter);
            //printf("Log:\tBlock Size: %d\tProcess Size: %d\tCurrent Min: %d\tCurrent Index: %d\n", size, pSize, min, index);
            if (n->pID == -1 && n->pSize >= pSize && min > n->pSize) {
                min = n->pSize;
                index = i;
            }
        }

        if (index == -1) {
            printf("Process: %s,\tpID: %d\t\t[Queued]\n", pName, pID);
            SinglyLinkedList_insert(que, -1, pID, pSize, pName);
        } else {
            struct node *prev = SinglyLinkedList_getNode(memory, index-1);
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
        free(iter);
    }
}

void stop(struct SinglyLinkedList *memory, struct SinglyLinkedList *que) {
    struct SinglyLinkedList_Iterator *iter = new_SinglyLinkedList_Iterator(memory);
    struct SinglyLinkedList_Iterator *iter1 = new_SinglyLinkedList_Iterator(que);

    int pID;
    printf(">> Enter the process id: ");
    scanf("%d", &pID);

    if (pID < 0) {
        printf("No process found with ID %d\n", pID);
        return;
    }

    int index = -1, min = 0;
    for (int i = 0; SinglyLinkedList_Iterator_hasNextNode(iter); i++) {
        int id = SinglyLinkedList_Iterator_nextNode(iter)->pID;
        if (pID == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        for (int i = 0; SinglyLinkedList_Iterator_hasNextNode(iter1); i++) {
            int id = SinglyLinkedList_Iterator_nextNode(iter1)->pID;
            if (pID == id) {
                index = i;
                break;
            }
        }

        if (index == -1) printf("No process found with ID %d\n", pID);
        else {
            struct node *n = SinglyLinkedList_deleteNode(que, index);
            printf("Process:%s,\tpID: %d\t\t[Dequeued]\n", n->pName, pID);
            free(n);
        }
    } else {
        struct node *this, *prev, *post;
        prev = SinglyLinkedList_getNode(memory, index-1);
        this = prev->link;
        post = this->link;

        this->pID = -1;
        printf("Process: %s,\tpID: %d\t\t[Stopped]\n", this->pName, pID);

        if (prev->pID == -1) {
            this->pSize += prev->pSize;
            prev = SinglyLinkedList_deleteNode(memory, index-1);
            free(prev);
            index--;
            prev = SinglyLinkedList_getNode(memory, index-1);
        }

        if (post->pID == -1) {
            this->pSize += post->pSize;
            this->link = post->link;
            free(post);
        }

        SinglyLinkedList_Iterator_reset(iter1);
        for(int i = 0; SinglyLinkedList_Iterator_hasNextNode(iter1); i++) {
            struct node *process = SinglyLinkedList_Iterator_nextNode(iter1);
            if (process->pSize <= this->pSize) {
                process = SinglyLinkedList_deleteNode(que, i);
                this->pSize -= process->pSize;

                if (this->pSize > 0) process->link = this;
                else {
                    process->link = this->link;
                    free(this);
                }

                prev->link = process;
                prev = process;
                i--;
                printf("Process: %s,\tpID: %d\t\t[Started]\n", process->pName, process->pID);
            }
        }
    }
}

void main() {
    struct SinglyLinkedList *memory = new_SinglyLinkedList();
    struct SinglyLinkedList_Iterator *iter = new_SinglyLinkedList_Iterator(memory);
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
            SinglyLinkedList_insert(memory, -1, -1, size, "Free");
            SinglyLinkedList_insert(memory, -1, -2, 10, "Data");
        } else {
            printf("Terminating: Expected size greater than zero!!!\n");
            return;
        }
    }
    SinglyLinkedList_insert(memory, 0, -2, 10, "Data");

    display(memory, "---Current State of Memory---\n");

    struct SinglyLinkedList *Queue = new_SinglyLinkedList();
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