#include <stdio.h>

int arr[10];

int resolve(int index) {
	return index+1;
}

int hash(int key) {
	int index = 0;
	for (int Num = key; Num > 0; Num /= 10) index += Num%10;
	index %= 10;
	int cIndex = index;
	while (arr[cIndex] != 0) {
		if (arr[cIndex] == key) return -2;
		cIndex = resolve(cIndex)%10;
		if (cIndex == index) return -1;
	}
	return cIndex;
}

void searchKey() {
	
}

void inputKey() {
	int key;
	printf("Enter the key: ");
	scanf("%d", &key);
	
	int index = hash(key);
	if (index > -1) {
		arr[index] = key;
		printf("Log: Generated index is %d\n", index);
	} else if (index == -2) {
		printf("Key already exists!!!\n");
	} else if (index == -1) {
		printf("Looks like hash table is full!!!\n");
		return;
	} else {
		printf("Uncaught exception!!!\n");
		return;
	}
	printf("Log: Array:");
	for (int i = 0; i < 10; i++) printf("\t%d", arr[i]);
	printf("\n");
}

void main() {
	printf("Menu:\n    1. Key Input\n    2. Search Key\n    3. Exit\n");
	
	while(1) {
		int input;
		printf(">> ");
		scanf("%d", &input);
		
		switch(input) {
			case 1: inputKey(); break;
			case 2: searchKey(); break;
			case 3: printf("Exiting...\n"); return;
			default: printf("Invalid Input!!!\n");
		}
	}
}
