#include<stdio.h>

int arr[10], copy[10], n;

void selectionSort() {
	for (int i = 0; i < n-1; i++) {
		int min = i;
		for (int j = i+1; j < n; j++) if (copy[min] > copy[j]) min = j;
		if (min != i) {
			int temp = copy[i];
			copy[i] = copy[min];
			copy[min] = temp;
		}
	}
}

void insertionSort() {
	for (int i = 0; i < n-1; i++) {
		for (int j = i+1; copy[j-1] > copy[j] && j >= 0; j--) {
			int temp = copy[j-1];
			copy[j-1] = copy[j];
			copy[j] = temp;
		}
	}
}

void main() {
	printf("Enter the limit (Max is 10): ");
	scanf("%d", &n);
	
	if (n > 10) {
		printf("Error: max limit exceeds 10!!!\n");
		return;
	}
	
	for (int i = 0; i < n; i++) {
		printf("Enter the Element[%d]: ", i);
		scanf("%d", &arr[i]);
	}
	
	int inp = 0;
	printf("Menu:\n    1. Insertion Sort\n    2. Selection Sort\n    3. Exit\n");
	while(1) {
		printf(">> ");
		scanf("%d", &inp);
		
		for (int i = 0; i < n; i++) copy[i] = arr[i];
		
		switch(inp) {
			case 1: insertionSort(); break;
			case 2: selectionSort(); break;
			case 3: printf("Exiting...\n"); return;
			default: printf("Invalid option!!!\n"); continue;
		}
		for (int i = 0; i < n; i++) printf("Element[%d]: %d\n", i, copy[i]);
	}
}
