#include "mini.h"

int main(void)
{
	char *res;
	res = readline("dis moi tout > ");
	while(ft_strncmp(res, "exit", 4))
	{
		printf("%s\n", res);
		add_history(res);
		free(res);
		res = readline("dis moi tout > ");
	}
	rl_clear_history();
	free(res);
	return (0);
}