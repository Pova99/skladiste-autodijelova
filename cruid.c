#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "Header.h"

void create_parts(FILE* fp, PART* p) {

	if (fp == NULL) {

		perror("Datoteka ne postoji!");
		return;
	}

	fseek(fp, 0, SEEK_END);
	fwrite(p, sizeof(PART), 1, fp);
}

void read_parts(FILE* fp) {
	
	if (fp == NULL) {

		perror("Datoteka ne postoji!");
		return;
	}

	rewind(fp);

	PART p = { 0 };
	while (fread(&p, sizeof(PART), 1, fp)) {

		printf("%-20s | ", p.catalog_number);

		switch (p.category) {
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

		printf(" | %-20s | %-15s | %-8.2f | %-5d\n", p.name,
			p.manufacturer, p.price, p.quantity);
	}
	printf("\n");
}

void find_part(FILE* fp, const char* id, PART* result) {

	rewind(fp);

	PART p = { 0 };

	while (fread(&p, sizeof(PART), 1, fp)) {

		if (strcmp(p.catalog_number, id) == 0) {
			
			*result = p;
			return 1;
		}
	}

	return 0;
}

void update_parts(FILE* fp, const char* catalog_number) {
	
	if (fp == NULL) {

		perror("Datoteka ne postoji!");
		return;
	}

	rewind(fp);

	PART p = { 0 };
	while (fread(&p, sizeof(PART), 1, fp)) {

		if (strcmp(p.catalog_number, catalog_number) == 0) {

			fseek(fp, -1, SEEK_CUR);

			printf("Unesi novu cijenu: \n");
			if (scanf("%lf %d", &p.price) != 1) while (getchar() != '\n');

			printf("Unesi novu kolicinu: \n");
			if (scanf("%lf %d", &p.quantity) != 1) while (getchar() != '\n');

			fwrite(&p, sizeof(PART), 1, fp);
			return;
		}
	}
}

void delete_parts(FILE* fp, const char* catalog_number) {

	FILE* temp = fopen("temp.dat", "wb");
	rewind(fp);

	PART p = { 0 };

	while (fread(&p, sizeof(PART), 1, fp)) {

		if (strcmp(p.catalog_number, catalog_number) != 0) {

			fwrite(&p, sizeof(PART), 1, temp);
		}
	}

	fclose(fp);
	fclose(temp);

	remove("parts.dat");
	rename("temp.dat", "parts.dat");
}