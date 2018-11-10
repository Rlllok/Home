#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int id;
    char manufacturer[127];
    int year;
    char model[127];
    float price;
    int x_size;
    int y_size;
} SCAN_INFO;

//const int MaxFileName = 20;
//char cvs[MaxFileName] = "cvs.txt", db[MaxFileName] = "db.bin";

int creat_db(const char* cvs, const char* db);
int make_index(const char* db, const char* field_name);
