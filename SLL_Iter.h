#include <stdio.h>
#include <stdlib.h>
#include "singlyFns3.h"

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
    if (iter == NULL) printf("NullPointerException: Parameter passed as Iter is NULL\n\t@ function SLL_Iter_hasNextNode(Iter): int\n");
    
    return iter->ptr != NULL;
}

struct node* SLL_Iter_nextNode(struct SLL_Iter* iter) {
    if (iter == NULL) printf("NullPointerException: Parameter passed as Iter is NULL\n\t@ function SLL_Iter_nextNode(Iter): node\n");
    
    struct node* temp = iter->ptr;
    if (temp != NULL) iter->ptr = temp->link;
    return temp;
}

void SLL_Iter_reset(struct SLL_Iter* iter) {
    if (iter == NULL) printf("NullPointerException: Parameter passed as Iter is NULL\n\t@ function SLL_Iter_reset(Iter): void\n");
    
    iter->ptr = *(iter->head);
}
    if (list == NULL) printf("NullPointerException: Parameter passed as SLL is NULL\n\t@ function SLL_clear(SLL): void\n");
    
    while (list->head != NULL) {
        struct node* ptr = list->head;
        list->head = ptr->link;
        free(ptr);
    }
}