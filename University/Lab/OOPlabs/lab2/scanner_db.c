/**********************************************************************************
* file: scanning.c
* purpose: entry point to the program, testing functions
*author: Novikov Alexander KV-72
*written: 03/11/2018
*last modified: 11/11/2018
***********************************************************************************/
#include "scanner.h"


int main()
{
    char cvs[55] = "scanner.cvs";
    char db[55] = "scanner.db";
    creat_db(cvs, db);
	printf_db(db);
    reindex(db);
	del_scanner(db, 0);
	add_scanner(db, "Dell;DellScan2;2012;999.99;210;297;");
	add_scanner(db, "Dell;DellScan2;2012;999.99;210;297;");
    printf_db(db);
	reindex(db);
	RECORD_SET *record_set = get_recs_by_index(db, "year");
    print_rec_set(record_set);
    free(record_set->recs);
    record_set = select1(db, "manufacturer", "HP");
	print_rec_set(record_set);
    free(record_set->recs);
    free(record_set);

    return 0;
}
