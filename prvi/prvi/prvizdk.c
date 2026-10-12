#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
	char name[30];
	char surname[30];
	int bodovi;
} Stud;

int main() {

	int brojac = 0;
	char buffer[100];
	int i = 0;
	int max_bodovi = 0;

	// otvaranje datoteke
	FILE* fp = fopen("popis.txt", "r");
	if (fp == NULL) {
		printf("greska");
		return -1;
	}

	// brojanje redaka u datoteci
	while (fgets(buffer, 100, fp) != NULL) {
		brojac++;
	}

	// vracanje na pocetak datoteke umisto zatvaranja i otvaranja datoteke
	rewind(fp);

	// dinamicka alokacija memorije za studente
	Stud* studenti = NULL;
	studenti = (Stud*)malloc(sizeof(Stud) * brojac);

	if (studenti == NULL) {
		fclose(fp);
		return -1;
	}

	// unos studenata iz datoteke
	while (i < brojac) {
		fscanf(fp, "%s %s %d",
			studenti[i].name,
			studenti[i].surname,
			&studenti[i].bodovi);

		// pronalazak najveceg broja bodova
		if (studenti[i].bodovi > max_bodovi) {
			max_bodovi = studenti[i].bodovi;
		}

		i++;
	}

	// ispis apsolutnih i relativnih bodova
	for (i = 0; i < brojac; i++) {
		printf("%s %s %d %.2f\n",
			studenti[i].name,
			studenti[i].surname,
			studenti[i].bodovi,
			(float)studenti[i].bodovi / max_bodovi * 100);
	}

	// zatvaranje datoteke i oslobadanje memorije
	fclose(fp);
	free(studenti);

	return 0;
}