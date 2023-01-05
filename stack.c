#include <stdio.h>

int Top = -1, stack[25];

void push() {
    //Checking for overflow
    if (Top+1 >= 5) {
        printf("Error: Stack overflow!!!\n");
        return;
    }

    int value;

    //Value input
    printf("Enter the value to be pushed: ");
    scanf("%d", &value);

    /*

    ++Top means add one to Top and then use it.
    Technically it can rewrite as:
        Top = Top + 1;
        stack[Top] = value;
    I just simplified it

    */
    stack[++Top] = value;
}

void pop() {
    //Checking for underflow
    if (Top < 0) {
        printf("Error: Stack underflow!!!\n");
        return;
    }

    /*

    Top-- means use it first and the substract one from it.
    Technically it can rewrite as:
        value = stack[Top];
        Top = Top - 1;

    */
    int value = stack[Top--];
    printf("The value poped is %d\n", value);
}

void display() {
    for (int i = 0; i <= Top; i++) {
        printf("%d\n", stack[i]);
    }
}

int main() {
    int input = 0;

    //Menu to show for the first time
    printf("Menu:\n");
    printf("    1.Push\n");
    printf("    2.Pop\n");
    printf("    3.Display\n");
    printf("    4.Exit\n");
    printf("\nUse option number to select it\n");

    //while (1) makes it infinite loop
    while (1) {
        //Just for accepting the option input
        printf(">> ");
        scanf("%d", &input);

        //Action according to the input. Also can done with if else statements!
        switch (input) {
            case 1: push(); break;
            case 2: pop(); break;
            case 3: display(); break;
            case 4: return 0; //4th option is exit, so returning from main function technically stops the program
            default: printf("Error: Invalid selection!!!\n");
        }
    }
    
}