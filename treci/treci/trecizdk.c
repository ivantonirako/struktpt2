
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

int insertAfterLastName(char* ime, char* prezime, int godina, char* lastN, Position p);
int insertBeforeLastName(char* ime, char* prezime, int godina, char* lastN, Position p);
int sortList(Position p);
int writeFile(char* filename, Position p);
int readFile(char* filename, Position p);

int main() {
    Person Head = { .ime = "", .prezime = {0}, .godina = 0, .next = NULL };
    Position p = &Head;

    insertBegin("Pero", "Peric", 1990, p);
    insertBegin("Ana", "Anic", 2000, p);
    insertEnd("Marko", "Maric", 1985, p);

    printf("Lista prije brisanja:\n");
    ispis(p);

    if (findLastName("Peric", p))
        printf("\nosoba Peric je pronadena\n");
    else
        printf("\nosoba Peric nije pronadena\n");

    deletePerson("Anic", p);

    printf("\nLista nakon brisanja:\n");
    ispis(p);

    insertAfterLastName("Luka", "Lukic", 2002, "Peric", p);

    insertBeforeLastName("Iva", "Ivic", 2001, "Maric", p);

    printf("\nLista nakon dodavanja:\n");
    ispis(p);

    sortList(p);

    printf("\nSortirana lista:\n");
    ispis(p);

    writeFile("osobe.txt", p);

    Position temp;

    while (p->next != NULL) {
        temp = p->next;
        p->next = temp->next;
        free(temp);
    }

    readFile("osobe.txt", p);

    printf("\nLista procitana iz datoteke:\n");
    ispis(p);

    while (p->next != NULL) {
        temp = p->next;
        p->next = temp->next;
        free(temp);
    }

    return 0;
}


int insertBegin(char* ime, char* prezime, int godina, Position p) {
    Position newPerson = (Position)malloc(sizeof(Person));

    if (newPerson == NULL)
        return 0;

    strcpy(newPerson->ime, ime);
    strcpy(newPerson->prezime, prezime);
    newPerson->godina = godina;

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
    Position newPerson = (Position)malloc(sizeof(Person));

    if (newPerson == NULL)
        return 0;

    strcpy(newPerson->ime, ime);
    strcpy(newPerson->prezime, prezime);
    newPerson->godina = godina;
    newPerson->next = NULL;

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
    Position curr = p->next;
    Position prev = p;

    while (curr != NULL) {
        if (strcmp(curr->prezime, lastN) == 0) {
            prev->next = curr->next;
            free(curr);
            return 1;
        }

        prev = curr;
        curr = curr->next;
    }

    return 0;
}

int insertAfterLastName(char* ime, char* prezime, int godina, char* lastN, Position p) {
    Position newPerson = NULL;

    while (p->next != NULL && strcmp(p->next->prezime, lastN) != 0) {
        p = p->next;
    }

    if (p->next == NULL)
        return 0;

    newPerson = (Position)malloc(sizeof(Person));

    if (newPerson == NULL)
        return 0;

    strcpy(newPerson->ime, ime);
    strcpy(newPerson->prezime, prezime);
    newPerson->godina = godina;

    newPerson->next = p->next->next;
    p->next->next = newPerson;

    return 1;
}

int insertBeforeLastName(char* ime, char* prezime, int godina, char* lastN, Position p) {
    Position newPerson = NULL;

    while (p->next != NULL && strcmp(p->next->prezime, lastN) != 0) {
        p = p->next;
    }

    if (p->next == NULL)
        return 0;

    newPerson = (Position)malloc(sizeof(Person));

    if (newPerson == NULL)
        return 0;

    strcpy(newPerson->ime, ime);
    strcpy(newPerson->prezime, prezime);
    newPerson->godina = godina;

    newPerson->next = p->next;
    p->next = newPerson;

    return 1;
}

int sortList(Position p) {
    Position prev;
    Position curr;
    Position temp;
    int zamjena;

    do {
        zamjena = 0;
        prev = p;
        curr = p->next;

        while (curr != NULL && curr->next != NULL) {
            if (strcmp(curr->prezime, curr->next->prezime) > 0) {
                temp = curr->next;

                curr->next = temp->next;
                temp->next = curr;
                prev->next = temp;

                zamjena = 1;
                prev = temp;
            }
            else {
                prev = curr;
                curr = curr->next;
            }
        }
    } while (zamjena);

    return 1;
}

int writeFile(char* filename, Position p) {
    FILE* fp = fopen(filename, "w");
    Position q;

    if (fp == NULL)
        return 0;

    for (q = p->next; q != NULL; q = q->next) {
        fprintf(fp, "%s %s %d\n", q->ime, q->prezime, q->godina);
    }

    fclose(fp);
    return 1;
}

int readFile(char* filename, Position p) {
    FILE* fp = fopen(filename, "r");
    Position newPerson;

    if (fp == NULL)
        return 0;

    while (1) {
        newPerson = (Position)malloc(sizeof(Person));

        if (newPerson == NULL) {
            fclose(fp);
            return 0;
        }

        if (fscanf(fp, "%29s %29s %d",
            newPerson->ime,
            newPerson->prezime,
            &newPerson->godina) != 3) {
            free(newPerson);
            break;
        }

        newPerson->next = NULL;

        while (p->next != NULL) {
            p = p->next;
        }

        insertAfter(p, newPerson);
    }

    fclose(fp);
    return 1;
}
