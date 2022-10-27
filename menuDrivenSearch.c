//Ansif M Shamsu
//CSE-A, S3, 26

#include <stdio.h>

int arr[25], sorted[25], limit, key;

void bubbleSort() {
	for (int i = 0; i < limit; i++) sorted[i] = arr[i];

	for (int i = 0; i < limit-1; i++) for (int j = 0; j < limit-1-i; j++)
	if (sorted[j] > sorted[j+1]) {
		int temp = sorted[j];
		sorted[j] = sorted[j+1];
		sorted[j+1] = temp;
	}
}

int linearSearch(int key) {
	for (int i = 0; i < limit; i++) if (arr[i] == key) return i;

	return -1;
}

int binarySearch(int key) {
	int low = 0, high = limit-1;
	
	while (low<=high) {
		int mid = (low+high)/2;
		
		if (sorted[mid] > key) high = mid-1;
		else if (sorted[mid] < key) low = mid+1;
		else return mid;
	}
	
	return -1;
}

int getKey() {
	printf("Enter the key to be searched: ");
	scanf("%d", &key);
	return key;
}

int main() {
	printf("Enter the limit (Max is 25): ");
	scanf("%d", &limit);
	
	if (limit > 25) {
		printf("Error: Limit exceeds maximum!!!\n");
		return 1;
	}
	
	for (int i = 0; i < limit; i++) {
		printf("Enter the value for element[%d]: ", i);
		scanf("%d", &arr[i]);
	}
	
	bubbleSort();
	
	printf("\n\t     UnSorted     Sorted\n");
	for (int i = 0; i < limit; i++) printf("element[%d]\t%d\t    %d\t\n", i, arr[i], sorted[i]);
	
	int input = 0;
	
	printf("\n");
	printf("Menu:\n");
	printf("    1. Linear Search\n");
	printf("    2. Binary Search\n");
	printf("    3. Exit\n");
	
	printf("\nTip: Use option number to select it\n");

	while (1) {
		printf(">> ");
		scanf("%d", &input);
		
		int result= -2;

		if (input == 1) result = linearSearch(getKey());
		else if (input == 2) result = binarySearch(getKey());
		
		if (result == -2) printf("Error: Invalid choice!!!\n");
		else if (result < 0) printf("%d not found\n", key);
		else printf("%d is found at the location %d\n", key, result);
		printf("\n");
	}
}
