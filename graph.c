#include<stdio.h>

int stack[10];
int que[10];
int top = -1;
int f = 0;
int r = 0;
int n = 10;
int matrix[10][10];
int Nodes;

void push(int item) {
    if (top+1 >= n) {
        printf("Overflow Error\n");
        return;
    } else {
        top++;
        stack[top] = item;
    }
}

int pop() {
    if (top == -1) {
        printf("Underflow Error\n");
        return 0;
    } else {
        int item = stack[top];
        top--;
        return item;
    }
}

void insert(int item) {
    if (r-f >= n) {
        printf("Overflow Error\n");
        return;
    } else {
        que[r%n] = item;
        r++;
    }
}

int delete() {
    if (f==r) {
        printf("Underflow Error\n");
        return 0;
    } else {
        int item = que[f%n];
        f++;
        if (f >= n) {
            f = 0;
            r = r % n;
        }
        return item;
    }
}

void bfs() {
    int visited[] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	insert(0);
	while(f != r) {
		int i = delete();
        printf("%d, ", i);
		for (int j = 0; j < Nodes; j++) {
			if (matrix[i][j] == 1) {
				if (visited[j] != 1) {
					insert(j);
					visited[j] = 1;
				}
			}
		}
	}
}

void dfs() {
    int visited[] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	push(0);
	while(top != -1) {
		int i = pop();
        printf("%d, ", i);
		for (int j = 0; j < Nodes; j++) {
			if (matrix[i][j] == 1) {
				if (visited[j] != 1) {
					push(j);
					visited[j] = 1;
				}
			}
		}
	}
}

void main() {
    printf("Enter the number of nodes: ");
    scanf("%d", &Nodes);

    for(int i = 0; i < Nodes; i++)
    for(int j = 0; j < Nodes; j++) {
        printf("Enter the value[%d][%d]: ", i, j);
        scanf("%d", &matrix[i][j]);
    }

    printf("Matrix:\n");
    for(int i = 0; i < Nodes; i++){
        for(int j = 0; j < Nodes; j++) printf("%d    ", matrix[i][j]);
        printf("\n");
    }

    printf("BFS: ");
    bfs();
    printf("\nDFS: ");
    dfs();
    printf("\n");
}