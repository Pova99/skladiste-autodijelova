#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Header.h"

int menu(void) {

	int num = 0;

	PART* parts = NULL;

	printf("=====================");
	printf("Odaberite jednu od ponudenih opcija:");
	printf("=====================\n");
	printf("\t\tOpcija 1: dodavanje dijelova!\n");
	printf("\t\tOpcija 2: pretrazivanje dijelova!\n");
	printf("\t\tOpcija 3: ucitavanje dijelova!\n");
	printf("\t\tOpcija 4: ispisivanje dijelova!\n");
	printf("\t\tOpcija 5: brisanje vozila ili dijelova!\n");
	printf("\t\tOpcija 6: izlaz iz programa!\n");
	printf("============================================================================\n");

	int selection = 0;

	if (scanf("%d", &selection) != 1) while (getchar() != '\n');

	switch (selection) {

	case 1: add_parts(); break;
	case 2: parts = load(&num); search_parts(parts, num); break;
	case 3:; break;
	case 4:; break;
	case 5:; break;
	case 6: exit_program(); break;

	}
}

int exit_program() {

	return 0;
}