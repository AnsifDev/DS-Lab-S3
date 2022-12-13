#include <stdio.h>
#include <stdlib.h>

struct node {
	int value;
	struct node *link;
};

struct LinkedList {
	struct node *head;
};

struct Iterator {
	struct node *ptr, **head;
};

struct LinkedList *new_LinkedList() {
	return malloc(sizeof(struct LinkedList));
}

struct Iterator *new_Iterator(struct LinkedList *list) {
	if (list == NULL) return NULL;
	
	struct Iterator *iter = malloc(sizeof(struct LinkedList));
	iter->ptr = list->head;
	iter->head = &(list->head);
	
	return iter;
}

int insertAtFirst(struct LinkedList *list, int value) {
	if (list == NULL) return 1;
	
	struct node *temp = malloc(sizeof(struct node));
	temp->value = value;
	temp->link = list->head;
	list->head = temp;
	
	return 0;
}

void resetIter(struct Iterator *iter) {
	if (iter == NULL) return;
	iter->ptr = *(iter->head);
}

int hasNextNode(struct Iterator *iter) {
	if (iter == NULL) return 0;
	return (iter->ptr != NULL);
}

struct node *nextNode(struct Iterator *iter) {
	if (iter == NULL) return NULL;
	
	struct node *temp = iter->ptr;
	if (temp != NULL) iter->ptr = temp->link;
	
	return temp;
}

int equals(struct LinkedList *list1, struct LinkedList *list2) {
	if (list1 == NULL || list2 == NULL) return 0;
	
	struct Iterator *iter1, *iter2;
	iter1 = new_Iterator(list1);
	iter2 = new_Iterator(list2);
	
	while (hasNextNode(iter1) && hasNextNode(iter2)) {
		int value1 = nextNode(iter1)->value;
		int value2 = nextNode(iter2)->value;
		
		if (value1 != value2) return 0;
	}
	
	if (hasNextNode(iter1)) return 0;
	if (hasNextNode(iter2)) return 0;
	return 1;
}

void main() {
	struct LinkedList *list1, *list2;
	list1 = new_LinkedList();
	list2 = new_LinkedList();
	
	struct Iterator *iter = new_Iterator(list1);
	
	int eCount = 0;
	printf("Enter the max elements count: ");
	scanf("%d", &eCount);
	
	for (int i = 0; i < eCount; i++) {
		int value;
		printf("Enter the Element[%d]: ", i);
		scanf("%d", &value);
		
		insertAtFirst(list1, value);
	}
	
	resetIter(iter);
	while(hasNextNode(iter)) {
		int value = nextNode(iter)->value;
		insertAtFirst(list2, value);
	}
	
	if (equals(list1, list2)) printf("List is palindrome\n");
	else printf("List is not palindrome\n");
}
