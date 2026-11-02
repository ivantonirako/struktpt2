
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Poly* Position;

typedef struct Poly {
    int coef;
    int pow;
    Position next;
} polynom;

int insertAfter(Position p, Position newPoly);
int insertSorted(int coef, int pow, Position p);
int readFile(char* filename, Position p1, Position p2);
int addPoly(Position p1, Position p2, Position result);
int multiplyPoly(Position p1, Position p2, Position result);
int printPoly(Position p);
int deletePoly(Position p);

int main() {
    polynom HeadF = { .coef = 0, .pow = 0, .next = NULL };
    polynom HeadS = { .coef = 0, .pow = 0, .next = NULL };
    polynom HeadAdd = { .coef = 0, .pow = 0, .next = NULL };
    polynom HeadMultiply = { .coef = 0, .pow = 0, .next = NULL };

    Position p1 = &HeadF;
    Position p2 = &HeadS;
    Position resultAdd = &HeadAdd;
    Position resultMultiply = &HeadMultiply;

    readFile("polinomi.txt", p1, p2);

    printf("Prvi polinom:\n");
    printPoly(p1);

    printf("\nDrugi polinom:\n");
    printPoly(p2);

    addPoly(p1, p2, resultAdd);

    printf("\nZbroj polinoma:\n");
    printPoly(resultAdd);

    multiplyPoly(p1, p2, resultMultiply);

    printf("\nUmnozak polinoma:\n");
    printPoly(resultMultiply);

    deletePoly(p1);
    deletePoly(p2);
    deletePoly(resultAdd);
    deletePoly(resultMultiply);

    return 0;
}

int insertAfter(Position p, Position newPoly) {
    newPoly->next = p->next;
    p->next = newPoly;

    return 1;
}

int insertSorted(int coef, int pow, Position p) {
    Position newPoly = NULL;

    while (p->next != NULL && p->next->pow > pow) {
        p = p->next;
    }

    if (p->next != NULL && p->next->pow == pow) {
        p->next->coef += coef;
        return 1;
    }

    newPoly = (Position)malloc(sizeof(polynom));

    if (newPoly == NULL)
        return 0;

    newPoly->coef = coef;
    newPoly->pow = pow;
    newPoly->next = NULL;

    insertAfter(p, newPoly);

    return 1;
}

int readFile(char* filename, Position p1, Position p2) {
    FILE* fp = fopen(filename, "r");
    int coef, pow;
    int i = 0;

    if (fp == NULL)
        return 0;

    while (fscanf(fp, "%d %d", &coef, &pow) == 2) {
        if (i == 0) {
            insertSorted(coef, pow, p1);
        }
        else {
            insertSorted(coef, pow, p2);
        }

        if (fgetc(fp) == '\n')
            i = 1;
    }

    fclose(fp);
    return 1;
}

int addPoly(Position p1, Position p2, Position result) {
    Position q;

    for (q = p1->next; q != NULL; q = q->next) {
        insertSorted(q->coef, q->pow, result);
    }

    for (q = p2->next; q != NULL; q = q->next) {
        insertSorted(q->coef, q->pow, result);
    }

    return 1;
}

int multiplyPoly(Position p1, Position p2, Position result) {
    Position q, r;

    for (q = p1->next; q != NULL; q = q->next) {
        for (r = p2->next; r != NULL; r = r->next) {
            insertSorted(q->coef * r->coef,
                q->pow + r->pow, result);
        }
    }

    return 1;
}

int printPoly(Position p) {
    Position q;

    for (q = p->next; q != NULL; q = q->next) {
        printf("%dx^%d", q->coef, q->pow);

        if (q->next != NULL)
            printf(" + ");
    }

    printf("\n");

    return 1;
}

int deletePoly(Position p) {
    Position temp;

    while (p->next != NULL) {
        temp = p->next;
        p->next = temp->next;
        free(temp);
    }

    return 1;
}
