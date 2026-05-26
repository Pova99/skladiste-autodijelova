#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Header.h"

int main(void) {

	FILE* fp = fopen(DAT_BIN, "rb+");

	if (fp == NULL) {

		int zero = 0;
		fp = fopen(DAT_BIN, "wb+");
		fwrite(&zero, sizeof(int), 1, fp);
	}

	int condition = 1;

	while (condition) {

		condition = menu(fp);
	}

	fclose(fp);

	printf("Zavrsetak programa!\n");

	return 0;
}