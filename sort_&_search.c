#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

int binary_search_catalog_number(PART p[], int parts_num, char* find) {

	int ll = 0;
	int ul = parts_num - 1;
	int mid = -1;

	while (ll <= ul) {

		mid = (ll + ul) / 2;

		int cmp = strcmp(p[mid].catalog_number, find);

		if (cmp == 0) return mid;

		else if (cmp > 0) ul = mid - 1;

		else ll = mid + 1;
	}
	
	return -1;
}

void search_name(PART p[], int parts_num, char* find) {

	printf("\n");

	for (int i = 0; i < parts_num; i++) {

		if (strstr(p[i].name, find) != NULL) {
			
			format_print_parts(&p[i]);
		}
	}
	printf("\n");
}

void search_manufacturer(PART p[], int parts_num, char* find) {

	printf("\n");

	for (int i = 0; i < parts_num; i++) {

		if (strstr(p[i].manufacturer, find) != NULL) {

			format_print_parts(&p[i]);
		}
	}
	printf("\n");
}

void search_category(PART p[], int parts_num, char* find) {

	printf("\n");

	for (int i = 0; i < parts_num; i++) {

		const char* cat_str = category_to_string(p[i].category);

		if (strstr(cat_str, find) != NULL) {

			format_print_parts(&p[i]);
		}
	}
}