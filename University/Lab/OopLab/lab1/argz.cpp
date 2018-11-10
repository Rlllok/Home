/************************************************************************

*file: argz.c

*synopsis: The argz functions use malloc/realloc to allocate/grow argz vectors, and so any argz

* vector creating using these functions may be freed by using free; conversely, any argz

* function that may grow a string expects that string to have been allocated using malloc

* (those argz functions that only examine their arguments or modify them in place will work

* on any sort of memory). All argz functions that do memory allocation have a return type

* of error_t, and return 0 for success, and ENOMEM if an allocation error occurs.

* These functions are declared in the include file "argz.h".

*related files: none

*author: Novikov Alexand KV-72

*written: 08/10/2018

*last modified: 09/10/2018

************************************************************************/
#include "argz.h"


error_t argz_create_sep(const char *string, int sep, char **argz, size_t *argz_len)
{
	if (!string) {
		return ERROR;
    }

	*argz_len = strlen(string) + 1;
	*argz = (char*) malloc(*argz_len);

	int i = 0;
	while (*string) {
		if (*string != sep)
			 (*argz)[i] = *string;
		else
			(*argz)[i] = '\0';
		i++;
        string++;
	}
	(*argz)[i] = '\0';

	return OK;
}

size_t argz_count(const char *argz, size_t argz_len)
{
	int count = 0;
	for(int i = 0; i < argz_len; i++) {
		if (!argz[i])
			count++;
	}

	return count;
}

error_t argz_add(char **argz, size_t *argz_len, const char *str)
{
    if (!argz || !str || !argz_len)
        return ERROR;

	*argz = (char*) realloc(*argz, *argz_len + strlen(str) + 1);

	int i = *argz_len;
    *argz_len += (strlen(str) + 1);
	for (int j = 0; j < strlen(str); j++) {
		(*argz)[i] = str[j];
		i++;
	}
	(*argz)[i] = '\0';

	return OK;
}

void argz_delete(char **argz, size_t *argz_len, const char *entry)
{
	char *strbuff = *argz;

	int i = 0;
	//look entry position, if argz have no entry - return
	while (strcmp(strbuff, entry)) {
		if (i >= *argz_len)
			return;

        i += strlen(strbuff) + 1;
		strbuff += strlen(strbuff) + 1;
	}

	//deleting entry by moving argz elements
	for (int j = i; j < (*argz_len) - strlen(entry); j++) {
		(*argz)[j] = (*argz)[j + strlen(entry) + 1];
	}

	*argz_len -= (strlen(entry) + 1);
	*argz = (char*) realloc(*argz, *argz_len);
}

error_t argz_insert(char **argz, size_t *argz_len,const char *before, const char *entry)
{
    if(!argz || !before || !entry || !argz_len)
        return ERROR;

	char *strbuff = *argz;

	int i = 0;
	while (strcmp(strbuff, before)) {
		if (i >= *argz_len)
			return ERROR;

		i += strlen(strbuff) + 1;
		strbuff += strlen(strbuff) + 1;
	}

  *argz_len += strlen(entry) + 1;
	*argz = (char*) realloc(*argz, *argz_len);

	for (int j = i, k = 0; j < ((*argz_len) - strlen(entry) - 1); j++, k++) {
		(*argz)[(*argz_len) - 1 - k] = (*argz)[(*argz_len) - strlen(entry) - 2 - k];
	}

	for (int j = i, k = 0; j < (i + strlen(entry)); j++, k++) {
		(*argz)[j] = entry[k];
	}
	(*argz)[i + strlen(entry)] = '\0';

	return OK;
}

char* argz_next(char *argz, size_t argz_len, const char *entry)
{
   if (!entry){
       return argz;
   }

   int i = 0;
   while (strcmp(argz, entry)) {
       if (i >= argz_len)
           return NULL;

       i += strlen(argz) + 1;
       argz += strlen(argz) + 1;
   }

   if(i + strlen(argz) + 1 < argz_len) {
        return argz + strlen(argz) + 1;
   }

   return NULL;
}

error_t argz_replace(char **argz, size_t *argz_len, const char *str, const char *with)
{
    if (!argz || !argz_len || !str || !with)
        return ERROR;
    char *strbuff = *argz;

    int i = 0;
    while (strcmp(str, strbuff)) {
        if (i >= *argz_len)
            return ERROR;

        i += strlen(strbuff) + 1;
        strbuff += strlen(strbuff) + 1;
    }

    strbuff = (char*) malloc((*argz_len) + strlen(with));

    // writing argz to strbuff using with
    for (int j = 0; j < i; j++)
        strbuff[j] = (*argz)[j];
    for (int j = i; j < strlen(with) + i; j++)
        strbuff[j] = with[j - i];
    strbuff[i + strlen(with)] = '\0';
    for (int j = i + strlen(str) + 1; j < *argz_len; j++)
        strbuff[j - strlen(str) + strlen(with) + 1] = (*argz)[j];

    *argz_len += (strlen(with) - strlen(str));
    *argz = (char*) realloc(*argz, *argz_len);

    for (int j = 0; j < *argz_len; j++)
        (*argz)[j] = strbuff[j];

    free(strbuff);

    return OK;
}



void argz_print(const char *argz, size_t argz_len)
{
    for (int i = 0; i < argz_len; i++)
        printf("%c", argz[i]);
    printf("\n");
}
