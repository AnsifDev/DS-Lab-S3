#include "SinglyLinkedList.h"

void main() {
    struct SLL *poly1, *poly2;

    poly1 = new_SLL();
    poly2 = new_SLL();

    int poly1_order, poly2_order;
    printf("Enter the order of the polynomial1: ");
    scanf("%d", &poly1_order);

    for (int i = poly1_order; i >= 0; i--) {
        int coeff;
        printf("Coeffient of x^%d: ", i);
        scanf("%d", &coeff);

        SLL_insert(poly1, 0, coeff);
    }

    printf("Enter the order of the polynomial2: ");
    scanf("%d", &poly2_order);

    for (int i = poly2_order; i >= 0; i--) {
        int coeff;
        printf("Coeffient of x^%d: ", i);
        scanf("%d", &coeff);

        SLL_insert(poly2, 0, coeff);
    }

    struct SLL *product = new_SLL();
    struct node *ptr1 = poly1->head;
    for (int i = 0; i <= poly1_order; i++) {
        struct node *ptr2 = poly2->head;
        for (int j = 0; j <= poly2_order; j++) {
            int coeff = ptr1->value * ptr2->value;
            int prevCoeff;
            if (SLL_get(product, i+j, &prevCoeff) == 1)
                SLL_insert(product, -1, coeff);
            else SLL_set(product, i+j, prevCoeff+coeff);
            ptr2 = ptr2->link;
        }
        ptr1 = ptr1->link;
    }

    printf("Product: ");
    int product_order = ((poly1_order>poly2_order) ? poly1_order : poly2_order) + 1;
    for (int i = product_order; i >=0; i--) {
        int coeff;
        SLL_get(product, i, &coeff);
        if (coeff == 0) continue;
        if (coeff != 1) printf("%d", coeff);
        if (i > 1) printf("x^%d+", i);
        else if (i == 1) printf("x+");
        else if (coeff == 1) printf("%d", coeff);
    }
    printf("\n");
}