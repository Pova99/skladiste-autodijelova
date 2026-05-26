#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

void swap_parts(PART* a, PART* b) {

	PART temp = *a;
	*a = *b;
	*b = temp;
}

void sort_by_catalog_number(PART p[], int n) {

	for (int i = 0; i < n - 1; i++) {

		int min = i;

		for (int j = i + 1; j < n; j++) {

			if (strcmp(p[j].catalog_number, p[min].catalog_number) < 0) {
				min = j;
			}
		}

		swap_parts(&p[i], &p[min]);
	}
}

void sort_by_name(PART p[], int n) {

	for (int i = 0; i < n - 1; i++) {

		int min = i;

		for (int j = i + 1; j < n; j++) {

			if (strcmp(p[j].name, p[min].name) < 0) {
				min = j;
			}
		}

		swap_parts(&p[i], &p[min]);
	}
}

void sort_by_manufacturer(PART p[], int n) {

	for (int i = 0; i < n - 1; i++) {

		int min = i;

		for (int j = i + 1; j < n; j++) {

			if (strcmp(p[j].manufacturer, p[min].manufacturer) < 0) {
				min = j;
			}
		}

		swap_parts(&p[i], &p[min]);
	}
}

void sort_by_price(PART p[], int n) {

	for (int i = 0; i < n - 1; i++) {

		int min = i;

		for (int j = i + 1; j < n; j++) {

			if (p[j].price < p[min].price) {
				min = j;
			}
		}

		swap_parts(&p[i], &p[min]);
	}
}

void sort_by_quantity(PART p[], int n) {

	for (int i = 0; i < n - 1; i++) {

		int min = i;

		for (int j = i + 1; j < n; j++) {

			if (p[j].quantity < p[min].quantity) {
				min = j;
			}
		}

		swap_parts(&p[i], &p[min]);
	}
}

void sort_by_category(PART p[], int n) {

	for (int i = 0; i < n - 1; i++) {

		int min = i;

		for (int j = i + 1; j < n; j++) {

			if (p[j].category < p[min].category) {
				min = j;
			}
		}

		swap_parts(&p[i], &p[min]);
	}
}