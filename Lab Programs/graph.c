#include<stdio.h>

int graph[10][10], maxNodes, que[10], f=0, r=0, stack[10], Top = -1;

int push(int value) {
    if (Top+1 >= 10) return 1;
    stack[++Top] = value;
    return 0;
}

int pop(int *value) {
    if (Top < 0) return 1;
    *value = stack[Top--];
    return 0;
}


int insert(int value) {
	if (f-r > 9) return 1;
	else que[f++%10] = value;
    return 0;
}

int delete(int *value) {
	if (r < f) *value = que[r++];
	else return 1;
	if (r > 9) {
		r %= 10;
		f %= 10;
	}
    return 0;
}

void bfs() {
    int visted[] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    insert(graph[0][0]);
    while (1) {
        int node;
        if (delete(&node)) return;
        printf("%d\n", node);
        for (int i = 0; i < maxNodes; i++) {
            int nNode = graph[node][i];
            if (nNode == 0) continue;
            if (visted[i] == 0) {
                insert(i);
                visted[i] = 1;
            }
        }
    }
}

void dfs() {
    int visted[] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    push(graph[0][0]);
    while (1) {
        int node;
        if (pop(&node)) return;
        printf("%d\n", node);
        for (int i = 0; i < maxNodes; i++) {
            int nNode = graph[node][i];
            if (nNode == 0) continue;
            if (visted[i] == 0) {
                push(i);
                visted[i] = 1;
            }
        }
    }
}

void main() {
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