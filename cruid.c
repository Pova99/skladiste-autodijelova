#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

void read_parts(FILE* fp, PART* p) {
	
	if (p == NULL) {

		printf("Datoteka 'parts.bin' je prazna!");
		return;
	}

	int selection = -1;
	char decision[DECS_LEN] = { '\0' };

	printf("Odaberite nacin prikaza:\n");
	printf("\tOpacija 1: Sortirano po kataloskim brojevima.\n");
	printf("\tOpacija 2: Sortirano po kategorijama.\n");
	printf("\tOpacija 3: Sortirano po nazivu.\n");
	printf("\tOpacija 4: Sortirano po proizvodacu.\n");
	printf("\tOpacija 5: Sortirano po cijeni.\n");
	printf("\tOpacija 6: Sortirano po kolicini.\n");
	printf("\tOpacija 7: Ispisi odmah bez sortiranja.\n");

	do {

		printf("Odabir (0 za povratak): ");

		if (scanf("%d", &selection) != 1) {

			while (getchar() != '\n');
			selection = -1;
		}

		if (selection == 0) return;

		if (selection < 1 || selection > 7) printf("Pogresan unos!\n");

	} while (selection < 1 || selection > 7);

	printf("\n");
	printf("Broj sveukupnih dijelova: %d\n", parts_num);
	read_parts_sorted(p, parts_num, selection);
	printf("\n");


	do {

		printf("Zelite li sortirani sadrzaj zapisati u '%s'? (y/n): ", DAT_BIN);
		scanf("%3s", decision);
		printf("\n");

		for (int i = 0; decision[i]; i++) {
			decision[i] = (char)tolower((unsigned char)decision[i]);
		}

		if (strcmp(decision, "n") == 0 || strcmp(decision, "no") == 0) {

			return;
		}

		else if (strcmp(decision, "y") == 0 || strcmp(decision, "yes") == 0) {

			save_parts(fp, p, parts_num);
			return;
		}

		else {

			printf("Pogresan unos!\n");
		}

	} while (strcmp(decision, "n") || strcmp(decision, "no") || strcmp(decision, "y") || strcmp(decision, "yes"));
}


void find_parts(FILE* fp, PART* p) {

	if (p == NULL) {

		printf("Datoteka 'parts.bin' je prazna!");
		return;
	}

	char find[CAT_LEN] = { '\0' };
	int selection = -1;

	rewind(fp);
	fread(&parts_num, sizeof(int), 1, fp);

	printf("Odaberite nacin pretrazivanja:\n");
	printf("\tOpacija 1: Pretrazivanje po kataloskim brojevima.\n");
	printf("\tOpacija 2: Pretrazivanje po kategorijama.\n");
	printf("\tOpacija 3: Pretrazivanje po nazivu.\n");
	printf("\tOpacija 4: Pretrazivanje po proizvodacu.\n");

	do {

		printf("Odabir (0 za povratak): ");

		if (scanf("%d", &selection) != 1) {

			while (getchar() != '\n');
			selection = -1;
		}

		if (selection == 0) return;

		if (selection < 1 || selection > 6) printf("Pogresan unos!\n");

	} while (selection < 1 || selection > 6);

	printf("Pretrazite: ");
	scanf("%63s", find);

	search_sorted(p, parts_num, selection, find);
}

void* find_parts_to_delete(FILE* fp, PART* p) {

	if (p == NULL) {

		printf("Datoteka 'parts.bin' je prazna!");
		return;
	}

	char find[CAT_LEN] = { '\0' };

	rewind(fp);
	fread(&parts_num, sizeof(int), 1, fp);

	printf("Unesite kataloski broj: ");
	scanf("%31s", find);

	sort_by_catalog_number(p, parts_num);
	int index = binary_search_catalog_number(p, parts_num, find);

	if (index != -1) {

		return (p + index);
	}

	return NULL;
}

void update_parts(FILE* fp, PART* p) {

	if (fp == NULL) {

		perror("Datoteka ne postoji!");
		return;
	}

	rewind(fp);

	char id[CAT_LEN] = { '\0' };

	printf("Unesite kataloski broj (0 za povratak): ");
	scanf("%31s", id);

	if (id == 0) return;

	int num = 0;
	fread(&num, sizeof(int), 1, fp);

	while (fread(p, sizeof(PART), 1, fp)) {

		if (strcmp(p->catalog_number, id) == 0) {

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
					printf("0 KATALOSKI BROJ, 1 KATEGORIJA, 2 NAZIV, 3 PROIZVODAC, 4 CIJENA, 5 KOLICINA\n");
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

	printf("Kataloski broj '%s' je obrisan!\n\n", delete_p->catalog_number);
}
