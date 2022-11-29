#include <stdio.h>

int keys[10], values[10]; //Hash Key Table
#define size 10 //Hash Key Table size

/*
	hash() is the function which converts key and returns as index.
		if index returned is negative, it means hashing unavailable
			This is caused because of two reasons,
			1. If key given is 0. Key cannot be zero, that is an invalid key
			2. If Hash Table is full
		if index returned is non negative, then returned value is the hashed index
		if values[index] != 0, it means key and value is already in the hash table.

	Key-Value pair storage:
		int put(int key, int value):
			Puts the value to a location correspoding to its key
			Returns 0 if task completed sucessfully
			
			!!!KEY AND VALUE MUST NOT BE 0!!!
		int get(int key):
			Returns the value coresponding to the key given
			If returned value is 0, it means value not found. It occurs if
			1. Key given is 0
			2. Key is not in the hash table
		int delete(int key):
			Removes the value coresponding to the key given
			Returns 0 if task completed sucessfully
*/

int hash(int key) {
	if (key == 0) return -1;

	int index = 0;
	for (int Num = key; Num != 0; Num /= size) index += Num%size;
	index %= size;

	index = index<0?index*-1:index;

	int cIndex = index;
	while (values[cIndex] != 0) {
		if (keys[cIndex] == key) return cIndex;
		cIndex = (cIndex+1)%size;
		if (cIndex == index) return -1;
	}

	return cIndex;
}

int put(int key, int value) {
	int index = hash(key);
	if (index < 0) return index;
	
	keys[index] = key;
	values[index] = value;
	printf("Log: Generated index is %d\n", index);
	return 0;
}

int get(int key) {
	int index = hash(key);
	if (index < 0) return 0;
	return values[index];
}

int delete(int key) {
	int index = hash(key);
	if (index < 0 || values[index] == 0) return 1;
	values[index] = 0;
	return 0;
}

void searchKey() {
	int key;
	printf("Enter the key: ");
	scanf("%d", &key);

	int value = get(key);
	if (value != 0) printf("The value is %d\n", value);
	else printf("Hash key not found!!!\n");
}

void inputKey() {
	int key, value;
	printf("Enter the key: ");
	scanf("%d", &key);
	printf("Enter the value: ");
	scanf("%d", &value);
	
	int returnCode = put(key, value);
	if (returnCode != 0) printf("Looks like hash table is full or key maybe 0!!!\n");
}

void removeKey() {
	int key;
	printf("Enter the key: ");
	scanf("%d", &key);

	int returnCode = delete(key);
	if (returnCode == 0) printf("Hash key removed\n");
	else printf("Hash key not found!!!\n");
}

void main() {
	printf("Menu:\n    1. Value Input\n    2. Get Value\n");
	printf("    3. Remove Key\n    4. Exit\n");
	
	while(1) {
		int input;
		printf(">> ");
		scanf("%d", &input);
		
		switch(input) {
			case 1: inputKey(); break;
			case 2: searchKey(); break;
			case 3: removeKey(); break;
			case 4: printf("Exiting...\n"); return;
			default: printf("Invalid Input!!!\n"); continue;
		}

		printf("Keys:");
		for (int i = 0; i < size; i++) printf("\t%d", keys[i]);
		printf("\nValues:");
		for (int i = 0; i < size; i++) printf("\t%d", values[i]);
		printf("\n");
	}
}
