#pragma once

#define CAT_LEN 32
#define NAME_LEN 64
#define MANU_LEN 64
#define DAT_BIN "parts.bin"
#define TEMP_BIN "temp.bin"
#define DECS_LEN 5

static char* filename = "parts.bin";

typedef enum {
    ENGINE,
    BRAKES,
    SUSPENSION,
    ELECTRICAL,
    BODY,
    OTHER
} PART_CATEGORY;

typedef struct {
    char catalog_number[CAT_LEN];
    char name[NAME_LEN];
    char manufacturer[MANU_LEN];
    double price;
    int quantity;
    PART_CATEGORY category;
} PART;

/* menu */
int menu(FILE*);

/* cruid */
void create_parts(FILE*, PART*);
PART* load_parts(FILE*);
void read_parts(PART*);
void* find_parts(FILE*, PART*);
void update_parts(FILE*, PART*);
void delete_parts(FILE*, PART*, PART*);

/* functions_misc */
PART* enter_parts_info();
void format_print_parts(PART*);
int confirm_selection();
void* secure_load_parts(FILE*, PART*);
void read_parts_sorted(PART p[], int, int);

/* sort_&_search */
void swap_parts(PART*, PART*);
void sort_by_catalog_number(PART p[], int);
void sort_by_name(PART p[], int);
void sort_by_manufacturer(PART p[], int);
void sort_by_price(PART p[], int);
void sort_by_quantity(PART p[], int);
void sort_by_category(PART p[], int);
