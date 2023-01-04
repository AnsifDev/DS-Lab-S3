#include<stdio.h>

int graph[10][10], que[10], f=0, r=0, stack[10];

void insert() {
	int value;
	printf("Enter the value: ");
	scanf("%d", &value);
	if (f-r > 9) printf("Error: Queue overflow!!!\n");
	else que[f++%10] = value;
}

void delete() {
	if (r < f) printf("Value removed is %d\n", que[r++]);
	else printf("Error: Queue underflow!!!\n");
	if (r > 9) {
		r %= 10;
		f %= 10;
	}
}

int bfs() {

}

void main() {
    int maxNodes;
    printf("Enter the number of nodes (Maximum: 10): ");
    scanf("%d", &maxNodes);

    if (maxNodes > 10 || maxNodes < 1) {
        printf("Error: Invalid number of nodes!!!\n");
        return;
    }

    for (int i = 0; i < maxNodes; i++)
    for (int j = 0; j < maxNodes; j++) graph[i][j] = 0;

    for (int i = 0; i < maxNodes; i++) {
        printf("Enter the adjacent node ids of node %d: ", i);
        
        while (1) {
            int input;
            scanf("%d", &input);
            if (input < 0) break;
            if (input < maxNodes) graph[i][input] = 1;
            else printf("%d is an invalid node id!\n", input);
        }
    }

    for (int i = 0; i < maxNodes; i++) {
        for (int j = 0; j < maxNodes; j++)  printf("%d\t", graph[i][j]);
        printf("\n");
    }

    printf("Menu:\n  1. BFS\n  2. DFS\n  3. Exit\n");
    while (1) {
        int input;
        printf(">> ");
        scanf("%d", &input);

        switch (input) {
            case 1: bfs(); break;
            case 2: dfs(); break;
            case 3: printf("Exiting...\n"); return;
            default: printf("Error: Invalid input!!!\n");
        }
    }
}