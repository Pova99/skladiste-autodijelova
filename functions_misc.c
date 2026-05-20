#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "Header.h"

PART* enter_parts_info() {

	PART* p = (PART*)calloc(1, sizeof(PART));

	printf("Unesite kataloski broj: ");
	scanf("%32s", p->catalog_number);

	printf("Unesite naziv: ");
	scanf(" %[^\n]", p->name);

	printf("Unesite proizvodaca: ");
	scanf(" %[^\n]", p->manufacturer);

	printf("Unesite cijenu: ");
	scanf("%lf", &p->price);

	printf("Unesite kolicinu: ");
	scanf("%d", &p->quantity);

	printf("Kategorije:\n");
	printf("0 ENGINE, 1 BRAKES, 2 SUSPENSION, 3 ELECTRICAL, 4 BODY, 5 OTHER\n");
	printf("Unos kategorije: ");

	int cat = 0;
	scanf("%d", &cat);
	p->category = (PART_CATEGORY)cat;

	return p;
}

void print_engine_parts(FILE* fp, PART* p) {

	rewind(fp);

	printf("\n\t\t=== ENGINE PARTS ===\n");

	while (fread(p, sizeof(PART), 1, fp) == 1) {

		if (p->category == ENGINE) {

			printf("Catalog: %s\n", p->catalog_number);
			printf("Name: %s\n", p->name);
			printf("Manufacturer: %s\n", p->manufacturer);
			printf("Price: %.2f\n", p->price);
			printf("Quantity: %d\n", p->quantity);
			printf("----------------------\n");
		}
	}
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

FILE* get_all_data(FILE* fp, int* num) {

	if (fp == NULL) {

		perror("Datoteka ne postoji!");
		return;
	}
	else {

		rewind(fp);
		fread(num, sizeof(int), 1, fp);

		PART* p = (PART*)calloc(*num, sizeof(PART));

		if (p == NULL) {

			free(p);
			perror("Zauzimanje memorije!");
			exit(EXIT_FAILURE);
		}
		else {

			fread(p, sizeof(PART), *num, fp);
			return p;
		}
	}
}
