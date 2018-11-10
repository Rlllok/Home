#include "argz.h"


int main ()
{
	const char *string = "SHELL/bin/bash:usr=monty:PWD=/bin/monty:LANG=en_US.UTF-8";
    char *argz = NULL;
	size_t  argz_len = 0;
    int buff = 0;
    printf("Initial string:\n");
    printf("%s\n\n\n", string);

    //argz_create_sep test
    printf("1.1) If STR = NULL: %i\n", argz_create_sep(NULL, 58, &argz, &argz_len));
    printf("1.2) If STR = !NULL: \n\n\t");
    argz_create_sep(string, 58, &argz, &argz_len);
    argz_print(argz, argz_len);

    //argz_count test
    buff = argz_count(argz, argz_len);
    printf("2) Number of elemenst: %i\n", buff);

    //argz_add test
    printf("3.1) If STR or ARGZ = NULL: %i\n", argz_add(NULL, &argz_len, NULL));
    printf("3.2) If STR = !NULL: %i\n\n\t", argz_add(&argz, &argz_len, "MontyLaptop"));
    argz_print(argz, argz_len);

    //argz_delete test
    argz_delete(&argz, &argz_len, "usr=monty");
    printf("4) Argz after deleting \"usr=monty\": \n\n\t");
    argz_print(argz, argz_len);

    //argz_insert test
    printf("5.1) If NULL: %i", argz_insert(NULL, NULL, NULL, NULL));
    printf("5.2) ARGZ after adding \"entry\": \n\n\t");
    argz_insert(&argz, &argz_len, "SHELL/bin/bash", "MONTY");
    argz_print(argz, argz_len);

    //argz_next test
    printf("6.1) If entry = NULL: %s\n", argz_next(argz, argz_len, NULL));
    printf("6.2) If entry \"PWD=/bin/monty\": %s\n\n\t", argz_next(argz, argz_len, "PWD=/bin/monty"));

    //argz_replace test
    printf("7.1) If NULL: %i\n", argz_replace(NULL, NULL, NULL, NULL));
    printf("7.2) Argz after replacing str with \"with\": \n");
    argz_replace(&argz, &argz_len, "PWD=/bin/monty", "KERNEL");
    argz_print(argz, argz_len);

	return 0;
}
