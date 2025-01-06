#include "mini.h"


int main(void)
{
	char *res;
	res = readline("ecrit ta commande bb> ");
	printf("%s", res);
	free(res);
	return (0);
}