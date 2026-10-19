#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Person* Position;

typedef struct _Person {
    char ime[30];
    char prezime[30];
    int godina;
    Position next;
} Person;

int insertBegin(char* ime, char* prezime, int godina, Position p);
int insertAfter(Position p, Position newPerson);
int ispis(Position p);
int insertEnd(char* ime, char* prezime, int godina, Position p);
int findLastName(char* lastN, Position p);
int deletePerson(char* lastN, Position p);

int main() {
    Person Head = { .ime = "", .prezime = {0}, .godina = 0, .next = NULL };
    Position p = &Head;


    insertBegin("Pero", "Peric", 1990, p);
    insertBegin("Ana", "Anic", 2000, p);

    insertEnd("Marko", "Maric", 1985, p);


    printf("lista prije brisanja:\n");
    ispis(p);

    if (findLastName("Peric", p))
        printf("\nosoba Peric je pronadena\n");
    else
        printf("\nosoba Peric nije pronadena\n");

    deletePerson("Anic", p);

    printf("\nlista nakon brisanja:\n");
    ispis(p);

    return 0;
}

int insertBegin(char* ime, char* prezime, int godina, Position p) {
    Position newPerson = NULL;
    newPerson = (Position)malloc(sizeof(Person));

    if (newPerson == NULL)
        return 0;

    newPerson->godina = godina;
    strcpy(newPerson->ime, ime);
    strcpy(newPerson->prezime, prezime);
    newPerson->next = NULL;
    insertAfter(p, newPerson);
    return 1;
}

int insertAfter(Position p, Position newPerson) {
    newPerson->next = p->next;
    p->next = newPerson;
    return 1;
}

int ispis(Position p) {
    Position q = NULL;
    for (q = p->next; q != NULL; q = q->next) {
        printf("%s %s %d\n", q->ime, q->prezime, q->godina);
    }
    return 1;
}

int insertEnd(char* ime, char* prezime, int godina, Position p) {
    Position newPerson = NULL;
    newPerson = (Position)malloc(sizeof(Person));

    if (newPerson == NULL)
        return 0;

    newPerson->godina = godina;
    strcpy(newPerson->ime, ime);
    strcpy(newPerson->prezime, prezime);
    newPerson->next = NULL;

    // prolazak do zadnjeg elementa
    while (p->next != NULL) {
        p = p->next;
    }
    insertAfter(p, newPerson);
    return 1;
}

int findLastName(char* lastN, Position p) {
    Position q = NULL;
    for (q = p->next; q != NULL; q = q->next) {
        if (strcmp(q->prezime, lastN) == 0)
            return 1;
    }
    return 0;
}

int deletePerson(char* lastN, Position p) {
    Position curr = NULL;
    Position prev = p;
    curr = prev->next;
    while (curr != NULL) {
        if (strcmp(curr->prezime, lastN) == 0) {
            prev->next = curr->next;
            free(curr);

            return 1;
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
    return 0;
}