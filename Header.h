#pragma once

static char* filename = "cars.bin";

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

int menu();
