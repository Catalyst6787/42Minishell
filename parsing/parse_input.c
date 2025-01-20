#include "../mini.h"

int	parse_input(char *line, t_cmd **groups)
{
	char *clean_line;
	char **tab;

	clean_line = clean_input(line);
	tab = split_tokens(clean_line);
	if (group_tokens(groups, tab)) // ces 4 lignes peuvent etre combine en un fn d'aide
		*groups = get_input_output(groups);
	clean_line = NULL;
	free(tab);
	tab = NULL;
	return(1);
}