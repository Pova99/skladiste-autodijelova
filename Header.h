#pragma once

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
    char catalog_number[32];
    char name[64];
    char manufacturer[64];
    double price;
    int quantity;
    PART_CATEGORY category;
} PART;

int menu(FILE*);
void create_parts(FILE*, PART*);
void read_parts(FILE*);
void update_parts(FILE*, const char*);
void delete_parts(FILE*, const char*);
void find_part(FILE*, const char*, PART*);

PART* enter_parts_info();