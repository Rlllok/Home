#include "scanner.h"

int creat_db(const char* cvs, const char* db)
{
    if (cvs == NULL || db == NULL)
        return 0;

    FILE *cvsfile = fopen(cvs, "r");
    FILE *dbfile  = fopen(db, "w + b");

    if (cvsfile == NULL || dbfile == NULL)
        return 0;

    char buff[255];
    char buffElements[6][255];
    int id = 0;
    int scanCount = 0;
    SCAN_INFO scaninfo;

    while (fscanf(cvsfile, "%s", buff) == 1)
        scanCount++;
    fwrite(&scanCount, sizeof(scanCount), 1, dbfile);
    rewind(cvsfile);

    while (fscanf(cvsfile, "%s", buff) == 1) {
        int k = 0;
        int l = 0;
        for (int i = 0; buff[i]; i++) {
            if (buff[i] == ';') {
               buffElements[k][l] = '\0';
               l = 0;
               k++;
            } else {
                buffElements[k][l] = buff[i];
                l++;
            }
        }

        scaninfo.id = id;
        id++;
        strcpy(scaninfo.manufacturer, buffElements[0]);
        scaninfo.year = atoi(buffElements[2]);
        strcpy(scaninfo.model, buffElements[1]);
        scaninfo.price = atof(buffElements[3]);
        scaninfo.x_size = atoi(buffElements[4]);
        scaninfo.y_size = atoi(buffElements[5]);

        fwrite(&scaninfo, sizeof(scaninfo), 1, dbfile);
    }



    fclose(cvsfile);
    fclose(dbfile);

    return 1;
}

int make_index(const char* db, const char* field_name)
{
    if (db == NULL || field_name == NULL)
        return 0;

    int fieldTypeFlag = 0; // 1 - char, 2 - int, 3 - float
    if (strcmp(field_name, "manufacturer") == 0 || strcmp(field_name, "model") == 0)
        fieldTypeFlag = 1;
    else if (strcmp(field_name, "year") == 0 || strcmp(field_name, "x_size") == 0 || strcmp(field_name, "y_size") == 0)
        fieldTypeFlag = 2;
    else if (strcmp(field_name, "price") == 0)
        fieldTypeFlag = 3;
    else return 0;

    FILE *dbfile = fopen(db, "rb");
    int scanNum = 0;
    fread(&scanNum, sizeof(scanNum), 1, dbfile);
    int *intFields = NULL;
    if (fieldTypeFlag == 2)
        intFields = (int*)malloc(scanNum * sizeof(int));
    float *floatFields = NULL;
    if (fieldTypeFlag == 3)
        floatFields = (float*)malloc(scanNum * sizeof(float));
    char **charFields = NULL;
    if (fieldTypeFlag == 1) {
        charFields = (char**)malloc(scanNum * sizeof(char*));
        for (int i = 0; i < scanNum; i++)
            charFields[i] = (char*)malloc(127 * sizeof(char));
    }
    int *indexes = (int*)malloc(scanNum * sizeof(int));
    for (int i = 0; i < scanNum; i++)
        indexes[i] = i;

    SCAN_INFO buffScanInfo;
    int k = 0;
    while (fread(&buffScanInfo, sizeof(buffScanInfo), 1, dbfile)) {
        if (strcmp(field_name, "manufacturer") == 0) {
            strcpy(charFields[k], buffScanInfo.manufacturer);
        } else if (strcmp(field_name, "year") == 0) {
            intFields[k] = buffScanInfo.year;
        } else if (strcmp(field_name, "model") == 0) {
            strcpy(charFields[k], buffScanInfo.model);
        } else if (strcmp(field_name, "price") == 0) {
            floatFields[k] = buffScanInfo.price;
        } else if (strcmp(field_name, "x_size") == 0) {
            intFields[k] = buffScanInfo.x_size;
        } else if (strcmp(field_name, "y_size") == 0) {
            intFields[k] = buffScanInfo.y_size;
        }
        k++;
    }

    k = 0;

    if (fieldTypeFlag == 1) {
        char tmp[127];
        int indexTmp = 0;

        for (int i = 0; i < scanNum; i++) {
            for (int j = i + 1; j < scanNum; j++) {
                if (strcmp(charFields[i], charFields[j]) > 0) {
                    strcpy(tmp, charFields[i]);
                    strcpy(charFields[i], charFields[j]);
                    strcpy(charFields[j], tmp);

                    indexTmp = indexes[i];
                    indexes[i] = indexes[j];
                    indexes[j] = indexTmp;
                }
            }
        }
        free(charFields);
    } else if (fieldTypeFlag == 2) {
        int tmp = 0;

        for (int i = 0; i < scanNum; i++) {
            for (int j = i + 1; j < scanNum; j++) {
                if (intFields[i] > intFields[j]) {
                    tmp = intFields[i];
                    intFields[i] = intFields[j];
                    intFields[j] = tmp;

                    tmp = indexes[i];
                    indexes[i] = indexes[j];
                    indexes[j] = tmp;
                }
            }
        }
        free(intFields);
    } else if (fieldTypeFlag == 3) {
        float fltTmp = 0;
        int indexTmp = 0;

        for (int i = 0; i < scanNum; i++) {
            for (int j = i + 1; j < scanNum; j++) {
                if (floatFields[i] > floatFields[j]) {
                    fltTmp = floatFields[i];
                    floatFields[i] = floatFields[j];
                    floatFields[j] = fltTmp;

                    indexTmp = indexes[i];
                    indexes[i] = indexes[j];
                    indexes[j] = indexTmp;
                }
            }
        }
        free(floatFields);
    }

    char idxname[127];
    strcpy(idxname, field_name);
    strcat(idxname, ".idx");

    FILE *idxfile = fopen(idxname, "w + b");
    for(int i = 0; i < scanNum; i++)
        fwrite(&indexes[i], sizeof(indexes[i]), 1, idxfile);
    free(indexes);
    rewind(idxfile);

    fclose(idxfile);
    fclose(dbfile);

    return 1;
}

RECORD_SET* get_recs_by_index(const char *db, char *index_field)
{
    if(db == NULL || index_field == NULL)
        return 0;

    FILE *dbfile = fopen(db, "rb");
    int scanNum = 0;
    fread(&scanNum, sizeof(scanNum), 1, dbfile);
    char idxname[127];
    strcpy(idxname, index_field);
    strcat(idxname, ".idx");
    FILE *idxfile = fopen(idxname, "rb");
    int *indexes = (int*)malloc(scanNum * sizeof(int));
    for (int i = 0; i < scanNum; i++)
        fread(&indexes[i], sizeof(indexes[i]), 1, idxfile);
    RECORD_SET *record_set = (RECORD_SET*)malloc(sizeof(RECORD_SET));
    record_set->rec_nmb = scanNum;
    record_set->recs = (SCAN_INFO*)malloc(scanNum * sizeof(SCAN_INFO));

    for (int i = 0; i < scanNum; i++)
        for (int j = 0; j < scanNum; j++)
            if (indexes[j] == i)
                fread(&record_set->recs[j], sizeof(SCAN_INFO), 1, dbfile);

    fclose(dbfile);
    fclose(idxfile);
    free(indexes);
    return record_set;
}

void reindex(const char *db)
{
    if (db == NULL)
        return;

    make_index(db, "manufacturer");
    make_index(db, "year");
    make_index(db, "model");
    make_index(db, "price");
    make_index(db, "x_size");
    make_index(db, "y_size");
}

void del_scanner(const char *db, int id)
{
    if (db == NULL)
        return;

    FILE *dbfile = fopen(db, "rb");
    int scanNum = 0;
    fread(&scanNum, sizeof(scanNum), 1, dbfile);
    FILE *buffFile = fopen("buff.db", "wb");
    fwrite(&scanNum, sizeof(scanNum), 1, buffFile);

    SCAN_INFO buffScanInfo;

    while (fread(&buffScanInfo, sizeof(buffScanInfo), 1, dbfile))
        if (buffScanInfo.id != id)
            fwrite(&buffScanInfo, sizeof(buffScanInfo), 1, buffFile);

    remove(db);
    rename("buff.db", db);

    fclose(buffFile);

    reindex(db);
}
void add_scanner(const char *db, const char *scanner_str)
{
    if (db == NULL || scanner_str == NULL)
        return;

    FILE *dbfile = fopen(db, "r b");
    int scanNum = 0;
    fread(&scanNum, sizeof(scanNum), 1, dbfile);
    fclose(dbfile);
    dbfile = fopen(db, "ab");
    SCAN_INFO buffScanInfo;
    char buffElements[6][255];
    int k = 0;
    int l = 0;
    for (int i = 0; scanner_str[i]; i++) {
        if (scanner_str[i] == ';') {
           buffElements[k][l] = '\0';
           l = 0;
           k++;
        } else {
            buffElements[k][l] = scanner_str[i];
            l++;
        }
    }

    buffScanInfo.id = scanNum;
    strcpy(buffScanInfo.manufacturer, buffElements[0]);
    buffScanInfo.year = atoi(buffElements[2]);
    strcpy(buffScanInfo.model, buffElements[1]);
    buffScanInfo.price = atof(buffElements[3]);
    buffScanInfo.x_size = atoi(buffElements[4]);
    buffScanInfo.y_size = atoi(buffElements[5]);

    fwrite(&buffScanInfo, sizeof(buffScanInfo), 1, dbfile);

    fclose(dbfile);
}

void printf_db(const char *db)
{
    if (db == NULL)
        return;

    FILE *dbfile = fopen(db, "rb");
    int scanNum = 0;
    fread(&scanNum, sizeof(scanNum), 1, dbfile);
    FILE *txtfile = fopen("scanInfo.txt", "w");
    fprintf(txtfile, "Number of scanners: %i\n\n", scanNum);
    SCAN_INFO buffScanInfo;

    while (fread(&buffScanInfo, sizeof(buffScanInfo), 1, dbfile)) {
        fprintf(txtfile, "%i ", buffScanInfo.id);
        fprintf(txtfile, "%s ", buffScanInfo.manufacturer);
        fprintf(txtfile, "%i ", buffScanInfo.year);
        fprintf(txtfile, "%s ", buffScanInfo.model);
        fprintf(txtfile, "%f ", buffScanInfo.price);
        fprintf(txtfile, "%i ", buffScanInfo.x_size);
        fprintf(txtfile, "%i \n", buffScanInfo.y_size);
    }

    fclose(dbfile);
    fclose(txtfile);
}

RECORD_SET* select1(const char *db, const char *field, const char *value)
{
    if (db == NULL || field == NULL || value == NULL)
        return NULL;

    FILE *dbfile = fopen(db, "rb");
    int scanNum = 0;
    fread(&scanNum, sizeof(scanNum), 1, dbfile);
    SCAN_INFO buffScanInfo;
    RECORD_SET *record_set = (RECORD_SET*)malloc(sizeof(RECORD_SET));
    record_set->rec_nmb = 0;
    record_set->recs = NULL;

    while (fread(&buffScanInfo, sizeof(buffScanInfo), 1, dbfile)) {
        if (strcmp(field, "manufacturer") == 0 && strcmp(buffScanInfo.manufacturer, value) == 0) {
            record_set->rec_nmb++;
            record_set->recs = (SCAN_INFO*)realloc(record_set->recs, record_set->rec_nmb * sizeof(SCAN_INFO));
            record_set->recs[record_set->rec_nmb - 1] = buffScanInfo;
        } else if (strcmp(field, "year") == 0 && buffScanInfo.year == atoi(value)) {
            record_set->rec_nmb++;
            record_set->recs = (SCAN_INFO*)realloc(record_set->recs, record_set->rec_nmb * sizeof(SCAN_INFO));
            record_set->recs[record_set->rec_nmb - 1] = buffScanInfo;
        } else if (strcmp(field, "model") == 0 && strcmp(buffScanInfo.model, value) == 0) {
            record_set->rec_nmb++;
            record_set->recs = (SCAN_INFO*)realloc(record_set->recs, record_set->rec_nmb * sizeof(SCAN_INFO));
            record_set->recs[record_set->rec_nmb - 1] = buffScanInfo;
        } else if (strcmp(field, "price") == 0 && buffScanInfo.price == atof(value)) {
            record_set->rec_nmb++;
            record_set->recs = (SCAN_INFO*)realloc(record_set->recs, record_set->rec_nmb * sizeof(SCAN_INFO));
            record_set->recs[record_set->rec_nmb - 1] = buffScanInfo;
        } else if (strcmp(field, "x_size") == 0 && buffScanInfo.x_size == atoi(value)) {
            record_set->rec_nmb++;
            record_set->recs = (SCAN_INFO*)realloc(record_set->recs, record_set->rec_nmb * sizeof(SCAN_INFO));
            record_set->recs[record_set->rec_nmb - 1] = buffScanInfo;
        } else if (strcmp(field, "y_size") == 0 && buffScanInfo.y_size == atoi(value)) {
            record_set->rec_nmb++;
            record_set->recs = (SCAN_INFO*)realloc(record_set->recs, record_set->rec_nmb * sizeof(SCAN_INFO));
            record_set->recs[record_set->rec_nmb - 1] = buffScanInfo;
        }
    }

    fclose(dbfile);

    return record_set;
}

void print_rec_set(RECORD_SET *rs)
{
    if (rs == NULL)
        return;

    printf("\nNumbers of scanners: %i\n", rs->rec_nmb);
    for (int i = 0; i < rs->rec_nmb; i++) {
        printf("%i ", rs->recs[i].id);
        printf("%s ", rs->recs[i].manufacturer);
        printf("%i ", rs->recs[i].year);
        printf("%s ", rs->recs[i].model);
        printf("%f ", rs->recs[i].price);
        printf("%i ", rs->recs[i].x_size);
        printf("%i \n", rs->recs[i].y_size);
    }
    printf("\n");
}
