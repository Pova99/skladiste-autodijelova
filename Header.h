#pragma once

#define CAT_LEN 32
#define NAME_LEN 64
#define MANU_LEN 64
#define DAT_BIN "parts.bin"
#define TEMP_BIN "temp.bin"
#define DECS_LEN 5

static char* filename = "parts.bin";

typedef enum {
    CATALOG_NUMBER,
    NAME,
    MANUFACTURER,
    PRICE,
    QUANTITY,
    CATEGORY
} DECISION;

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

int menu(FILE*);
void create_parts(FILE*, PART*, int*);
void read_parts(FILE*, PART*);
void update_parts(FILE*, const char*, PART*);
void delete_parts(FILE*, const char*, PART*);
PART* find_part(FILE*, const char*, PART*);

PART* enter_parts_info();
void print_engine_parts(FILE*, PART*);
void format_print_parts(PART*);
PART* get_all_data(FILE* fp, int*);
int confirm_selection();
