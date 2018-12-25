#pragma once
/************************************************************************
*file: scanner.h
*purpose: declarations for functions, types, constants
*author: Novikov Alexander KV-72
*written: 03/11/2018
*last modified: 11/11/2018
************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int id;
	char manufacturer[127];
	int year;
	char model[127];
	float price;
	int x_size;
	int y_size;
} SCAN_INFO;

typedef struct {
	int rec_nmb;
	SCAN_INFO *recs;
} RECORD_SET;

int creat_db(const char* cvs, const char* db);//uses information from *.cvs file to create *.db file
int make_index(const char* db, const char* field_name);//create index file after non-decreasing sorting
RECORD_SET* get_recs_by_index(const char *db, char *index_field);//using malloc for RECORD_SET.recs and RECORD_SET pointer
void reindex(const char *db);//create index file for all structur's fields
void del_scanner(const char *db, int id);//remove structure by id
void add_scanner(const char *db, const char *scanner_str);//adds structure to the end
void printf_db(const char *db);//creats *.txt file with information from *.db file
RECORD_SET* select1(const char *db, const char *field, const char *value);//using realloc for RECORD_SET.recs and malloc for RECORD_SET pointer
void print_rec_set(RECORD_SET *rs);//prints RECORS_SET structure to console
