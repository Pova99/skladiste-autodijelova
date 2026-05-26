#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "Header.h"

static int parts_num = 0;

void create_parts(FILE* fp, PART* p) {

	int count = 0;

	rewind(fp);

	if (fread(&count, sizeof(int), 1, fp) != 1) {
		count = 0;
	}

	count++;
	rewind(fp);
	fwrite(&count, sizeof(int), 1, fp);

	fseek(fp, 0, SEEK_END);
	fwrite(p, sizeof(PART), 1, fp);
}

PART* load_parts(FILE* fp) {

	int count = 0;

	rewind(fp);

	if (fread(&count, sizeof(int), 1, fp) != 1) {

		return NULL;
	}

	if (count <= 0) {

		return NULL;
	}

	PART* p = calloc(count, sizeof(PART));

	if (!p) {

		perror("Calloc failed!");
		exit(EXIT_FAILURE);
	}

	size_t read = fread(p, sizeof(PART), count, fp);

	if (read != (size_t)count) {

		free(p);
		return NULL;
	}

	parts_num = count;

	return p;
}

void read_parts(PART* p) {
	
	if (p == NULL) {

		printf("Datoteka 'parts.bin' je prazna");
		return;
	}

	printf("\n");
	printf("Broj sveukupnih dijelova: %d\n", parts_num);

	for (int i = 0; i < parts_num; i++) {

		format_print_parts(p + i);
	}
	printf("\n");
}


void* find_parts(FILE* fp, PART* p) {

	if (p == NULL) {

		printf("Datoteka 'parts.bin' je prazna");
		return;
	}

	char find[CAT_LEN] = { 0 };

	rewind(fp);
	fread(&parts_num, sizeof(int), 1, fp);

	printf("Unesite kataloski broj: ");
	scanf("%31s", find);

	for (int i = 0; i < parts_num; i++) {

		if (!strcmp(find, (p + i)->catalog_number)) {

			return (p + i);
		}
	}

	return NULL;
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
			while (scanf("%d", &selection) != 1) while (getchar() != '\n');

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
					while (scanf("%d", &decs) != 1) while (getchar() != '\n');

					switch (decs) {

						case 0: {

							printf("Unesite novi kataloski broj: ");
							scanf("%31s", temp.catalog_number);

							break;
						}

						case 1: {

							printf("Kategorije:\n");
							printf("0 ENGINE, 1 BRAKES, 2 SUSPENSION, 3 ELECTRICAL, 4 BODY, 5 OTHER\n");
							printf("Unos kategorije: ");

							int cat = 0;
							while (scanf("%d", &cat) != 1) while (getchar() != '\n');
							temp.category = (PART_CATEGORY)cat;

							break;
						}

						case 2: {

							printf("Unesite novi naziv: ");
							scanf(" %63[^\n]", temp.name);

							break;
						}

						case 3: {

							printf("Unesite novog proizvodaca: ");
							scanf(" %63[^\n]", temp.manufacturer);

							break;
						}

						case 4: {

							printf("Unesite novu cijenu: ");
							while (scanf("%lf", &temp.price) != 1) while (getchar() != '\n');

							break;
						}

						case 5: {

							printf("Unesite novu kolicinu: ");
							while (scanf("%d", &temp.quantity) != 1) while (getchar() != '\n');

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

void delete_parts(FILE* fp, PART* delete_p, PART* p) {

	int new_num = 0;

	FILE* temp = fopen(TEMP_BIN, "wb+");
	if (!temp) {
		perror("Temp file!");
		exit(EXIT_FAILURE);
	}

	fwrite(&new_num, sizeof(int), 1, temp);

	for (int i = 0; i < parts_num; i++) {

		if (strcmp(delete_p->catalog_number, p[i].catalog_number) != 0) {

			fwrite(&p[i], sizeof(PART), 1, temp);
			new_num++;
		}
	}

	rewind(temp);
	fwrite(&new_num, sizeof(int), 1, temp);

	fclose(fp);
	fclose(temp);

	remove(DAT_BIN);
	rename(TEMP_BIN, DAT_BIN);

	printf("Kataloski broj '%s' je obrisan!\n\n", *delete_p);
}
