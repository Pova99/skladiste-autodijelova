#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "Header.h"

void create_parts(FILE* fp, PART* p, int* num) {

	if (fp == NULL) {

		perror("Datoteka ne postoji!");
		return;
	}

	fread(&num, sizeof(int), 1, fp);
	rewind(fp);
	num++;
	fwrite(&num, sizeof(int), 1, fp);
	fseek(fp, 0, SEEK_END);
	fwrite(p, sizeof(PART), 1, fp);
}

void read_parts(FILE* fp, PART* p) {
	
	if (fp == NULL) {

		perror("Datoteka ne postoji!");
		return;
	}

	rewind(fp);

	while (fread(p, sizeof(PART), 1, fp)) {

		format_print_parts(p);
	}
	printf("\n");
}

PART* find_part(FILE* fp, const char* id, PART* p) {

	rewind(fp);

	while (fread(p, sizeof(PART), 1, fp)) {

		if (strcmp(p->catalog_number, id) == 0) {
			
			format_print_parts(p);
			return 1;
		}
	}

	return 0;
}

void update_parts(FILE* fp, const char* catalog_number, PART* p) {
	
	if (fp == NULL) {

		perror("Datoteka ne postoji!");
		return;
	}

	rewind(fp);

	while (fread(p, sizeof(PART), 1, fp)) {

		if (strcmp(p->catalog_number, catalog_number) == 0) {

			fseek(fp, -1, SEEK_CUR);

			printf("Unesi novu cijenu: \n");
			if (scanf("%lf", &p->price) != 1) while (getchar() != '\n');

			printf("Unesi novu kolicinu: \n");
			if (scanf("%d", &p->quantity) != 1) while (getchar() != '\n');

			fwrite(&p, sizeof(PART), 1, fp);
			return;
		}
	}
}

void delete_parts(FILE* fp, const char* catalog_number, int* num, PART* p) {

	FILE* temp = fopen(TEMP_BIN, "wb");

	rewind(fp);

	while (fread(p, sizeof(PART), 1, fp)) {

		if (strcmp(p->catalog_number, catalog_number) != 0) {

			fwrite(p, sizeof(PART), 1, temp);
		}
	}

	fclose(fp);
	fclose(temp);

	remove(DAT_BIN);
	rename(TEMP_BIN, DAT_BIN);
}
