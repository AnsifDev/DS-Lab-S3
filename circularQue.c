#include<stdio.h>
#include<string.h>

int que[10], f=0, r=-1;

void insert() {
	int value;
	printf("Enter the value: ");
	scanf("%d", &value);
	if (f%10 == r || r == -1 && f > 9) printf("Error: Queue overflow!!!\n");
	else que[f++%10] = value;
}

void delete() {
	if (r+1 < f) printf("Value removed is %d\n", que[++r]);
	else printf("Error: Queue underflow!!!\n");
	if (r >= 10) {
		r %= 10;
		f %= 10;
	}
}

void main() {
	int input = 0;
	
	printf("\n");
	printf("Menu:\n");
	printf("    1. Insert\n");
	printf("    2. Delete\n");
	printf("    3. Exit\n");
	
	printf("\nTip: Use option number to select it\n");
	
	while (1) {
		printf(">> ");
		scanf("%d", &input);
		
		switch(input) {
			case 1: insert(); break;
			case 2: delete(); break;
			case 3: return;
			default: printf("Error: Invalid option selected\n");
		}
		for (int i = r+1; i < f; i++) printf("%d\t", que[i%10]);
		if (r+1 < f) printf("\n");
		printf("\n");
	}
}
