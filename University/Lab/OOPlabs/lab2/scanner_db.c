#include "scanner.h"



int main()
{
    char cvs[55] = "scanner.cvs";
    char db[55] = "scanner.db";

    creat_db(cvs, db);
    make_index(db, "price");

    //FILE *f = fopen(db, "rb");
   // SCAN_INFO scaninfo;
  //  fread(&scaninfo, sizeof(scaninfo), 1, f);


//    printf("%i %s %i %s %f %i %i \n", scaninfo.id, scaninfo.manufacturer, scaninfo.year, scaninfo.mode, scaninfo.price, scaninfo.x_size, scaninfo.y_size);
    return 0;
}
