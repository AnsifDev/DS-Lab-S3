#include <stdio.h>

int keys[10]; //Hash Key Table
#define size 10 //Hash Key Table size

int hash(int key) {
	if (key == 0) return -1;

	int index = 0;
	for (int Num = key; Num != 0; Num /= size) index += Num%size;
	index %= size;

	index = (index<0)? -index: index;

	for (int i = 0; i < size; i++) {
		int newIndex = (index+i)%size;
		if (keys[newIndex] == 0 || keys[newIndex] == key)
			return (index+i)%size;
	}

	return -1;
}

int put(int key) {
	int index = hash(key);
	if (index < 0) return index;
	
	if (keys[index] != 0) printf("Hash Key already exists!!!\n");
	else {
		keys[index] = key;
		printf("Log: Generated index is %d\n", index);
	}
	return 0;
}

void inputKey() {
	int key;
	printf("Enter the key: ");
	scanf("%d", &key);

	int index = hash(key);
	if (index < 0) printf("Looks like hash table is full or key maybe 0!!!\n");
	else if (keys[index] != 0) printf("Hash Key already exists!!!\n");
	else {
		keys[index] = key;
		printf("Log: Generated index is %d\n", index);
	}
}

void searchKey() {
	int key;
	printf("Enter the key: ");
	scanf("%d", &key);

	int index = hash(key);
	if (keys[index] != 0) printf("The index is %d\n", index);
	else printf("Hash key not found!!!\n");
}

void main() {
	printf("Menu:\n    1. Value Input\n    2. Search Key\n");
	printf("    3. Exit\n");
	
	while(1) {
		int input;
		printf(">> ");
		scanf("%d", &input);
		
		switch(input) {
			case 1: inputKey(); break;
			case 2: searchKey(); break;
			case 3: printf("Exiting...\n"); return;
			default: printf("Invalid Input!!!\n"); continue;
		}

		printf("Keys:");
		for (int i = 0; i < size; i++) printf("\t%d", keys[i]);
		printf("\n");
	}
}
