#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Header.h"

int menu(FILE* fp) {

	int num = 0;
	PART* p = NULL;

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

	int selection = 0;

	if (scanf("%d", &selection) != 1) while (getchar() != '\n');

	switch (selection) {

	case 1: {

		PART* p = enter_parts_info();
		create_parts(fp, p, &num);
		if (p != NULL) {

			free(p);
		}
		break;
	}
		  
	case 2: {
		
		char search[CAT_LEN] = { 0 };

		printf("Pretrazivanje: ");
		scanf("%31s", search);

		p = get_all_data(fp, &num);

		int found = find_part(fp, search, p);

		if (!found) {

			printf("Kataloski broj '%s' ne postoji u bazi podataka!", search);
		}
	}

	case 3: ; break;
	case 4: {
	
		read_parts(fp, p);
		break;
	}
	case 5:; break;
	case 6: return 0;

	}
}
