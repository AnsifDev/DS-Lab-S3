#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *link;
};

struct LinkedList {
    struct node *head;
};

struct LinkedList* new_LinkedList() {
    return malloc(sizeof(struct LinkedList));
}

struct Iterator {
    struct node *ptr, **head;
};

struct Iterator* new_Iterator(struct LinkedList* list) {
    if (list == NULL) return NULL;
    struct Iterator* iter = malloc(sizeof(struct Iterator));
    iter->ptr = list->head;
    iter->head = &(list->head);
    return iter;
}

int hasNextNode(struct Iterator* iter) {
    if (iter == NULL) return 0;
    return iter->ptr != NULL;
}

struct node* nextNode(struct Iterator* iter) {
    if (iter == NULL) return NULL;
    struct node* temp = iter->ptr;
    if (temp != NULL) iter->ptr = temp->link;
    return temp;
}

struct node* getNode(struct LinkedList* list, int index) {
    if (list == NULL) return NULL;

    if (index == 0) return list->head;
    
    struct node* ptr;
    struct Iterator* iter = new_Iterator(list);
    if (index == -1) while(hasNextNode(iter)) ptr = nextNode(iter);
    else if (index == -2) {
        if (list->head->link != NULL) while (1) {
            ptr = nextNode(iter);
            if (ptr->link->link == NULL) break;
        }
    } else {
        for (int i = 0; i <= index; i++) {
            if (hasNextNode(iter)) ptr = nextNode(iter);
            else {
                free(iter);
                return NULL;
            }
        }
    }

    free(iter);
    return ptr;
}

void insertAtFirst(struct LinkedList* list, int value) {
    struct node* temp = malloc(sizeof(struct node));
    temp->value = value;
    temp->link = list->head;
    list->head = temp;
}

int get(struct LinkedList* list, int index, int* value) {
    if (list == NULL) return 1;

    struct node* ptr = getNode(list, index);
    if (ptr == NULL) return 1;

    *value = ptr->value;
    return 0;
}

void clearLinkedList(struct LinkedList* list) {
    if (list == NULL) return;

    while (list->head != NULL) {
        struct node* ptr = list->head;
        list->head = ptr->link;
        free(ptr);
    }
}

int indexOf(struct LinkedList* list, int value) {
    if (list == NULL) return -1;
    struct Iterator* iter = new_Iterator(list);

    int index = -1;
    for(int i = 0; hasNextNode(iter); i++) {
        if (nextNode(iter)->value == value) {
            index = i;
            break;
        }
    }

    free(iter);
    return index;
}

void main() {
    struct LinkedList* list1 = new_LinkedList();
    struct LinkedList* elements = new_LinkedList();
    struct LinkedList* counts = new_LinkedList();

    int n;
    printf("Enter the element count: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        printf("Enter the element[%d]: ", i);
        int Num;
        scanf("%d", &Num);

        insertAtFirst(list1, Num);
    }

    struct Iterator* iter = new_Iterator(list1);
    while(hasNextNode(iter)) {
        int value = nextNode(iter)->value;

        int index = indexOf(elements, value);
        if (index == -1) {
            insertAtFirst(elements, value);
            insertAtFirst(counts, 0);
        } else getNode(counts, index)->value += 1;
    }

    int maxCountIndex = 0, maxCount;
    get(counts, 0, &maxCount);
    struct Iterator* cIter = new_Iterator(counts);
    for (int i = 0; hasNextNode(cIter); i++) {
        int count = nextNode(cIter)->value;
        if (maxCount < count) {
            maxCount = count;
            maxCountIndex = i;
        }
    }

    int maxCountElement;
    get(elements, maxCountIndex, &maxCountElement);
    printf("Max repeated element is %d\n", maxCountElement);

    clearLinkedList(list1);
    clearLinkedList(elements);
    clearLinkedList(counts);

    free(list1);
    free(elements);
    free(counts);
    free(iter);
    free(cIter);
}