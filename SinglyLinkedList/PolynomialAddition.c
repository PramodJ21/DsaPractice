#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode {
    int coeff;
    int exp;
    struct PolyNode* next;
} PolyNode;

void insertTerm(PolyNode** poly, int coeff, int exp) {
    if (coeff == 0) return;
    PolyNode* newNode = (PolyNode*)malloc(sizeof(PolyNode));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;

    if (*poly == NULL || (*poly)->exp < exp) {
        newNode->next = *poly;
        *poly = newNode;
        return;
    }

    if ((*poly)->exp == exp) {
        (*poly)->coeff += coeff;
        free(newNode);
        return;
    }

    PolyNode* curr = *poly;
    while (curr->next != NULL && curr->next->exp > exp) {
        curr = curr->next;
    }

    if (curr->next != NULL && curr->next->exp == exp) {
        curr->next->coeff += coeff;
        free(newNode);
    } else {
        newNode->next = curr->next;
        curr->next = newNode;
    }
}

// Add two polynomials p1 and p2, returning a new polynomial list
PolyNode* addPolynomials(PolyNode* p1, PolyNode* p2) {
    PolyNode* result = NULL;
    PolyNode* ptr1 = p1;
    PolyNode* ptr2 = p2;

    while (ptr1 != NULL && ptr2 != NULL) {
        if (ptr1->exp > ptr2->exp) {
            insertTerm(&result, ptr1->coeff, ptr1->exp);
            ptr1 = ptr1->next;
        } else if (ptr2->exp > ptr1->exp) {
            insertTerm(&result, ptr2->coeff, ptr2->exp);
            ptr2 = ptr2->next;
        } else {
            // Equal exponents: combine coefficients
            int sumCoeff = ptr1->coeff + ptr2->coeff;
            if (sumCoeff != 0) {
                insertTerm(&result, sumCoeff, ptr1->exp);
            }
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    }

    // Add remaining terms from p1
    while (ptr1 != NULL) {
        insertTerm(&result, ptr1->coeff, ptr1->exp);
        ptr1 = ptr1->next;
    }

    // Add remaining terms from p2
    while (ptr2 != NULL) {
        insertTerm(&result, ptr2->coeff, ptr2->exp);
        ptr2 = ptr2->next;
    }

    return result;
}

void displayPolynomial(PolyNode* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }

    PolyNode* curr = poly;
    int isFirst = 1;

    while (curr != NULL) {
        if (!isFirst && curr->coeff > 0) {
            printf(" + ");
        } else if (curr->coeff < 0) {
            printf(" - ");
        }

        int absCoeff = (curr->coeff < 0) ? -curr->coeff : curr->coeff;

        if (curr->exp == 0) {
            printf("%d", absCoeff);
        } else if (curr->exp == 1) {
            if (absCoeff == 1) printf("x");
            else printf("%dx", absCoeff);
        } else {
            if (absCoeff == 1) printf("x^%d", curr->exp);
            else printf("%dx^%d", absCoeff, curr->exp);
        }

        curr = curr->next;
        isFirst = 0;
    }
    printf("\n");
}

int main() {
    PolyNode* p1 = NULL;
    PolyNode* p2 = NULL;

    // P1: 5x^4 + 3x^2 + 7
    insertTerm(&p1, 5, 4);
    insertTerm(&p1, 3, 2);
    insertTerm(&p1, 7, 0);

    // P2: 6x^3 - 3x^2 + 2x + 1
    insertTerm(&p2, 6, 3);
    insertTerm(&p2, -3, 2);
    insertTerm(&p2, 2, 1);
    insertTerm(&p2, 1, 0);

    printf("Polynomial 1: ");
    displayPolynomial(p1);

    printf("Polynomial 2: ");
    displayPolynomial(p2);

    PolyNode* sum = addPolynomials(p1, p2);

    printf("\nResultant Sum (P1 + P2): ");
    displayPolynomial(sum);

    return 0;
}
