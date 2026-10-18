#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode {
    int coeff;
    int exp;
    struct PolyNode* next;
} PolyNode;

// Insert a term keeping the polynomial sorted in descending order of exponents
void insertTerm(PolyNode** poly, int coeff, int exp) {
    if (coeff == 0) return; // Don't add 0-coefficient terms

    PolyNode* newNode = (PolyNode*)malloc(sizeof(PolyNode));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;

    // Insert at beginning or update head if same exponent
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

// Display polynomial in descending order of exponent
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
    PolyNode* p = NULL;

    printf("--- Polynomial Representation using Linked List ---\n\n");
    // Inserting terms in random order to verify sorting in descending exponents
    insertTerm(&p, 3, 2);
    insertTerm(&p, 5, 4);
    insertTerm(&p, -2, 1);
    insertTerm(&p, 7, 0);
    insertTerm(&p, 4, 3);
    insertTerm(&p, 2, 2); // Combines with 3x^2 to make 5x^2

    printf("Polynomial P(x): ");
    displayPolynomial(p);

    return 0;
}
