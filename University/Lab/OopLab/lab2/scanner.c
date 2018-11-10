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
        scaninfo.year = atoi(buffElements[1]);
        strcpy(scaninfo.model, buffElements[2]);
        scaninfo.price = atof(buffElements[3]);
        scaninfo.x_size = atoi(buffElements[4]);
        scaninfo.y_size = atoi(buffElements[5]);

        fwrite(&scaninfo, sizeof(scaninfo), 1, dbfile);
    }



    fclose(cvsfile);
    fclose(dbfile);
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
        for (int i = 0; i < 0; i++)
            charFields[i] = (char*)malloc(127 * sizeof(char));
    }
    int *indexes = (int*)malloc(scanNum * sizeof(int));

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

    for (int i = 0; i < scanNum; i++)
        printf("%g\n", floatFields[i]);


    free(indexes);

    fclose(dbfile);

    return 1;
}

