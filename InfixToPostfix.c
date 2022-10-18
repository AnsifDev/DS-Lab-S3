//Ansif M Shamsu
//CSE-A, S3, 26

#include<stdio.h>
#include<string.h>

char stack[50];
int Top = -1;

void push(char value) {
	if (Top+1 >= 50) return;
	
	stack[++Top] = value;
}

char pop() {
	if (Top < 0) return '\0';
	
	return stack[Top--];
}

int getPrecedence(char value) {
	switch (value) {
		case '+': 
		case '-': return 0; break;
		case '*': 
		case '/': return 1; break;
		case '^': return 2; break;
		case '(': return -1; break;
		default: return -2;
	}
}

void main() {
	char InputStr[50], OutputStr[50];
	
	printf("Enter the infix expression: ");
	scanf("%s", InputStr);
	
	int sLen = strlen(InputStr);
	InputStr[sLen++] = ')';
	push('(');
	int outLen = 0;
	
	for(int i = 0; i < sLen; i++) {
		char symbol = InputStr[i];
		int cPrecedence = getPrecedence(symbol);
		int prevPrecedence = getPrecedence(stack[Top]);
		
		//printf("Log: %d, %d, %c, %c\n", cPrecedence, prevPrecedence, symbol, stack[Top]);
		
		if (symbol == ')') for (char s = pop(); s != '('; s = pop()) OutputStr[outLen++] = s;
		else {
			if (cPrecedence == -2) OutputStr[outLen++] = symbol;
			else if (cPrecedence == -1) push(symbol);
			else {
				if (cPrecedence <= prevPrecedence) OutputStr[outLen++] = pop();
				push(symbol);
			}
		}
	}
	OutputStr[outLen] = '\0';
	
	printf("Output: %s\n", OutputStr);
}
