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

	rewind(fp);

	if (fread(num, sizeof(int), 1, fp) != 1) {

		*num = 0;
	}

	(*num)++;
	rewind(fp);
	fwrite(num, sizeof(int), 1, fp);
	fseek(fp, 0, SEEK_END);
	fwrite(p, sizeof(PART), 1, fp);
}

void read_parts(FILE* fp, PART* p) {
	
	if (fp == NULL) {

		perror("Datoteka ne postoji!");
		return;
	}


	rewind(fp);

	int num = 0;
	fread(&num, sizeof(int), 1, fp);

	printf("\n");
	while (fread(p, sizeof(PART), 1, fp)) {

		format_print_parts(p);
	}
	printf("\n");

}

PART* find_part(FILE* fp, const char* id, PART* p) {

	rewind(fp);

	int num = 0;
	fread(&num, sizeof(int), 1, fp);

	while (fread(p, sizeof(PART), 1, fp)) {

		if (strcmp(p->catalog_number, id) == 0) {
			
			printf("\n");
			format_print_parts(p);
			printf("\n");
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

	int num = 0;
	fread(&num, sizeof(int), 1, fp);

	while (fread(p, sizeof(PART), 1, fp)) {

		if (strcmp(p->catalog_number, catalog_number) == 0) {

			printf("\tOpcija 0: izmjena svih podataka!\n");
			printf("\tOpcija 1: izmjena odredenog podatka!\n");

			int selection = 0;
			printf("Odabir: ");
			if (scanf("%d", &selection) != 1) while (getchar() != '\n');

			PART temp = *p;

			switch (selection) {

			case 0: {

				PART* new_part = enter_parts_info();
				temp = *new_part;
				free(new_part);

				break;
			}
			case 1: {

				printf("Izmjena podatka:\n");
				printf("0 KATALOSKI BROJ, 1 NAZIV, 2 PROIZVODAC, 3 CIJENA, 4 KOLICINA, 5 KATEGORIJA\n");
				printf("Odabir: ");
				int decs = 0;
				if (scanf("%d", &decs) != 1) while (getchar() != '\n');

				switch (decs) {

				case 0: {

					printf("Unesite novi kataloski broj: ");
					scanf("%31s", temp.catalog_number);

					break;
				}

				case 1: {

					printf("Unesite novi naziv: ");
					scanf(" %63[^\n]", temp.name);

					break;
				}

				case 2: {

					printf("Unesite novog proizvodaca: ");
					scanf(" %63[^\n]", temp.manufacturer);

					break;
				}

				case 3: {

					printf("Unesite novu cijenu: ");
					if (scanf("%lf", &temp.price) != 1) while (getchar() != '\n');

					break;
				}

				case 4: {

					printf("Unesite novu kolicinu: ");
					if (scanf("%d", &temp.quantity) != 1) while (getchar() != '\n');

					break;
				}

				case 5: {

					printf("Kategorije:\n");
					printf("0 ENGINE, 1 BRAKES, 2 SUSPENSION, 3 ELECTRICAL, 4 BODY, 5 OTHER\n");
					printf("Unos kategorije: ");

					int cat = 0;
					if (scanf("%d", &cat) != 1) while (getchar() != '\n');
					temp.category = (PART_CATEGORY)cat;

					break;
				}
					break;
				}
				
			}

			default: printf("Pogresan unos!\n"); break;

			}

			fseek(fp, -(long)sizeof(PART), SEEK_CUR);
			fwrite(&temp, sizeof(PART), 1, fp);
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
