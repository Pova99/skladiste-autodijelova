#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Header.h"

int menu(FILE* fp) {

	printf("==============");
	printf(" Odaberite jednu od ponudenih opcija: ");
	printf("==============\n\n");
	printf("\t\tOpcija 1: Dodavanje dijelova!\n");
	printf("\t\tOpcija 2: Pretrazivanje dijelova!\n");
	printf("\t\tOpcija 3: Uredivanje dijelova!\n");
	printf("\t\tOpcija 4: Ispisivanje svih dijelova!\n");
	printf("\t\tOpcija 5: Brisanje dijelova!\n");
	printf("\t\tOpcija 6: Izlaz iz programa!\n\n");
	printf("==================================================================\n");

	static PART* p = NULL;
	static PART* found_part = NULL;

	int selection = 0;
	printf("Odabir: ");
	while (scanf("%d", &selection) != 1) while (getchar() != '\n');

	switch (selection) {

		case 1: {

			int num_create = 0;

			printf("Koliko dijelova zelite dodati (0 za povratak): ");
			while (scanf("%d", &num_create) != 1) while (getchar() != '\n');

			if (num_create == 0) break;

			for (int i = 0; i < num_create; i++) {

				printf("-------UNOS %d#-------\n", i + 1);

				PART* p = enter_parts_info();
				create_parts(fp, p);
				free(p);
				printf("\n");
			}

			break;
		}
		  
		case 2: {

			p = (PART*)secure_load_parts(fp, p);
			find_parts(fp, p);

			break;
		}

		case 3: {

			p = (PART*)secure_load_parts(fp, p);
			update_parts(fp, p);

			break;
		}

		case 4: {

			p = (PART*)secure_load_parts(fp, p);
			read_parts(fp, p);

			break;
		}

		case 5: {

			p = (PART*)secure_load_parts(fp, p);
			found_part = (PART*)find_parts_to_delete(fp, p);

			if (found_part == NULL) {

				printf("Kataloski broj nije pronaden!\n\n");
				break;
			}

			if (!confirm_selection()) return 1;

			delete_parts(fp, found_part, p);

			fopen(DAT_BIN, "rb+");
			p = (PART*)secure_load_parts(fp, p);

			break;
		}

		case 6: if (!confirm_selection()) return 1; return 0;

		default: printf("Krivi unos!\n");
	}

	return 1;
}
