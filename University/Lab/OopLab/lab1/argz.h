/************************************************************************

*file: argz.h

*purpose: declarations for argz functions, types, constants

*author: Novikov Alexandr KV-72

*written: 08/10/2018

*last modified: 09/10/2018

*************************************************************************/
#pragma once
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
namespace my
{
    typedef enum {OK, ERROR} error_t;
}

using my::OK;
using my::ERROR;
using my::error_t;

//copy string to agrz and replace char sep with \0
error_t argz_create_sep(const char *string, int sep, char **argz, size_t *argz_ltn);
//count argz's elements
size_t argz_count(const char *argz, size_t argz_len);
//add str to the end of argz
error_t argz_add(char **argz, size_t *argz_len, const char *str);
//delete argz's element
void argz_delete(char **argz, size_t *argz_len, const char *entry);
//add new elemet "entry" before element "before"
error_t argz_insert(char **argz, size_t *argz_len, const char *before, const char *entry);
//move though the argz's elements. If argz have no "entry", this function will return 0
//if "entry" = 0 - return pointer to the first element
char* argz_next(char *argz, size_t argz_len, const char *entry);
//replace element "str" with "with"
error_t argz_replace(char **argz, size_t *argz_len, const char *str, const char *with);
//print argz
void argz_print(const char *argz, size_t argz_len);
