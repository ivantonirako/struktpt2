#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct StackNode {
    double value;
    struct StackNode* next;
} StackNode;

typedef StackNode* Position;

FILE* openFile(const char* filename, const char* mode);
int push(Position head, double value);
double pop(Position head);
int printStack(Position head);
double evaluatePostfix(const char* filename);

int main() {
    double result = evaluatePostfix("postfix.txt");
    printf("Konacni rezultat: %.2lf\n", result);
    return 0;
}

FILE* openFile(const char* filename, const char* mode) {
    FILE* file = fopen(filename, mode);
    if (file == NULL) {
        printf("Greska: nije moguce otvoriti datoteku '%s'\n", filename);
        exit(EXIT_FAILURE);
    }
    return file;
}

int push(Position head, double value) {
    Position newNode = (Position)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("Greska: neuspjela alokacija memorije.\n");
        return -1;
    }

    newNode->value = value;
    newNode->next = head->next;
    head->next = newNode;
    return 0;
}

double pop(Position head) {
    Position temp = head->next;
    if (temp == NULL) {
        printf("Greska: stog je prazan.\n");
        return 0;
    }

    double poppedValue = temp->value;
    head->next = temp->next;
    free(temp);
    return poppedValue;
}

int printStack(Position head) {
    Position temp = head->next;
    while (temp != NULL) {
        printf("%.2lf ", temp->value);
        temp = temp->next;
    }
    printf("\n");
    return 0;
}

double evaluatePostfix(const char* filename) {
    FILE* file = openFile(filename, "r");

    StackNode head;
    head.next = NULL;

    char token[1024];

    // Cita brojeve i operatore iz datoteke
    while (fscanf(file, "%s", token) == 1) {

        // Prepoznaje broj i stavlja ga na stog
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&head, atof(token));
        }
        // Obraduje matematicke operatore
        else {
            double operand2 = pop(&head);
            double operand1 = pop(&head);
            double result = 0;

            switch (token[0]) {
            case '+': result = operand1 + operand2; break;
            case '-': result = operand1 - operand2; break;
            case '*': result = operand1 * operand2; break;
            case '/':
                if (operand2 == 0) {
                    printf("Greska: dijeljenje s nulom.\n");
                    fclose(file);
                    return 0;
                }
                result = operand1 / operand2;
                break;
            default:
                printf("Greska: nepoznat operator '%s'\n", token);
                fclose(file);
                return 0;
            }
            // Sprema rezultat operacije na stog
            push(&head, result);
        }
    }

    fclose(file);

    double finalResult = pop(&head);
    return finalResult;
}