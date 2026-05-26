#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Header.h"

int menu(FILE* fp) {

	printf("==============");
	printf("Odaberite jednu od ponudenih opcija:");
	printf("==============\n");
	printf("\t\tOpcija 1: dodavanje dijelova!\n");
	printf("\t\tOpcija 2: pretrazivanje dijelova!\n");
	printf("\t\tOpcija 3: uredivanje dijelova!\n");
	printf("\t\tOpcija 4: ispisivanje svih dijelova!\n");
	printf("\t\tOpcija 5: brisanje dijelova!\n");
	printf("\t\tOpcija 6: izlaz iz programa!\n");
	printf("================================================================\n");

	static PART* p = NULL;
	static PART* found_part = NULL;

	int selection = 0;
	printf("Odabir: ");
	while (scanf("%d", &selection) != 1) while (getchar() != '\n');
	if (!confirm_selection()) return 1;

	switch (selection) {

		case 1: {

			int num_create = 0;

			printf("Koliko dijelova zelite dodati: ");
			while (scanf("%d", &num_create) != 1) while (getchar() != '\n');

			for (int i = 0; i < num_create; i++) {

				printf("-------UNOS %d#-------\n", i + 1);

				PART* p = enter_parts_info();
				create_parts(fp, p);
				free(p);
			}

			break;
		}
		  
		case 2: {

			p = (PART*)secure_load_parts(fp, p);
			found_part = (PART*)find_parts(fp, p);

			if (found_part == NULL) printf("Kataloski broj nije pronaden!\n");

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
			break;
		}

		case 6: return 0;
	}

	return 1;
}
