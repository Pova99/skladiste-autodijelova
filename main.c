#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Header.h"

int main(void) {

	int condition = 1;

	while (condition) {

		condition = menu();
	}

	printf("Zavrsetak programa!\n");

	return 0;
}