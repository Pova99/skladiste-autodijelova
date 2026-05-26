#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "Header.h"
#include <ctype.h>

PART* enter_parts_info() {

	PART* p = (PART*)calloc(1, sizeof(PART));

	printf("Unesite kataloski broj: ");
	scanf("%31s[^\n]", p->catalog_number);

	printf("Unesite naziv: ");
	scanf(" %63[^\n]", p->name);

	printf("Unesite proizvodaca: ");
	scanf(" %63[^\n]", p->manufacturer);

	printf("Unesite cijenu: ");
	while (scanf("%lf", &p->price) != 1) while (getchar() != '\n');

	printf("Unesite kolicinu: ");
	while (scanf("%d", &p->quantity) != 1) while (getchar() != '\n');

	printf("Kategorije:\n");
	printf("0 ENGINE, 1 BRAKES, 2 SUSPENSION, 3 ELECTRICAL, 4 BODY, 5 OTHER\n");
	printf("Unos kategorije: ");

	int cat = 0;
	while (scanf("%d", &cat) != 1) while (getchar() != '\n');
	p->category = (PART_CATEGORY)cat;

	return p;
}

void format_print_parts(PART* p) {

	printf("%-20s | ", p->catalog_number);

	switch (p->category) {
	case ENGINE:
		printf("ENGINE");
		break;

	case BRAKES:
		printf("BRAKES");
		break;

	case SUSPENSION:
		printf("SUSPENSION");
		break;

	case ELECTRICAL:
		printf("ELECTRICAL");
		break;

	case BODY:
		printf("BODY");
		break;

	default:
		printf("OTHER");
		break;
	}

	printf(" | %-20s | %-15s | %-8.2f | %-5d\n", p->name,
		p->manufacturer, p->price, p->quantity);
}

int confirm_selection() {

	char decision[DECS_LEN] = { '\0' };

	printf("Jeste li sigurni da zelite nastaviti dalje? (y/n): ");
	scanf("%3s", decision);

	for (int i = 0; decision[i]; i++) {
		decision[i] = (char)tolower((unsigned char)decision[i]);
	}

	if (strcmp(decision, "n") == 0 || strcmp(decision, "no") == 0) {
		return 0;
	}

	return 1;
}

void* secure_load_parts(FILE* fp, PART* p) {

	if (p != NULL) {

		free(p);
		p = NULL;
	}

	p = load_parts(fp);

	if (p == NULL) {

		printf("Datoteka 'parts.bin' je prazna!");
		return;
	}

	return p;
}