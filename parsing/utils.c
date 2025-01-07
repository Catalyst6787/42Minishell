#include "mini.h"

int which_cmd(char *cmd)
{
	if (!strcmp(cmd, "echo"))
		return(ECHO);
	else if (!strcmp(cmd, "cd"))
		return(CD);
	else if (!strcmp(cmd, "pwd"))
		return(PWD);
	else if (!strcmp(cmd, "export"))
		return(EXPORT);
	else if (!strcmp(cmd, "unset"))
		return(UNSET);
	else if (!strcmp(cmd, "env"))
		return(ENV);
	else if (!strcmp(cmd, "exit"))
		return(EXIT);
	else
		return(EXTERNAL);
	
}

int	is_special(char c)
{
	if (c == '<' || c == '>')
		return (1);
	else if (c == '|')
		return (1);
	else if (c == '$')
		return (1);
	else if (c == '\'' || c == '\"')
		return (1);
	else
		return (0);
}

