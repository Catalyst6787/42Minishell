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

// returns first word of string
char *first_word(char *s)
{
	char *first_word;
	char *space_pos;
	space_pos = ft_strchr(s, ' ');

	if (space_pos != NULL)
		first_word = ft_substr(s, 0, space_pos - s);
	else
		first_word = ft_strdup(s);
	return(first_word);
}

int	command_handler(char *input)
{
	int cmd;
	char *fw;

	fw = first_word(input);
	if (fw == NULL)
		return(printf("enter a command!\n"));
	cmd = which_cmd(fw);
	if (cmd == ECHO)
		printf("%s\n", input);
	else if (cmd == EXIT)
		return(printf("Goodbye!\n"), exit(1), 1);
	else
		printf("external function: %s\n", fw);
	free(fw);
	return(1);
}

int	append_token(char *token, t_cmd *tail)
{
	int i;
	char **newtab;

	i = 0;
	while(tail->tab && tail->tab[i])
		i++;
	newtab = malloc(sizeof(char) * i + 2);
	newtab[i + 1] = NULL;
	newtab[i] = token;
	i--;
	while(i)
	{
		newtab[i] = ft_strdup(tail->tab[i]);
		free(tail->tab[i]);
		i--;
	}
	free(tail->tab);
	tail->tab = newtab;
	return(1);
}


int	init_node(t_cmd **node, t_cmd *prev)
{
	*node = malloc(sizeof(t_cmd));
	if (!*node)
		return(0);
	(*node)->prev = prev;
	if (prev)
	{
		(*node)->prev->next = *node;
		(*node)->id = (*node)->prev->id + 1;
	}
	else
		(*node)->id = 0;
	(*node)->tab = NULL;
	(*node)->next = NULL;
	return(1);
}

int	tokenizator(char *input, t_cmd *head)
{
	int i;
	int group_has_elem;
	//int j;

	i = 0;
	group_has_elem = 0;
	//j = 0;
	char **tab;
	tab = ft_split(input, ' ');
	while(tab[i])
	{
		if ((ft_strlen(tab[i]) == 1 && is_special(tab[i][0])) && group_has_elem)
		{
			init_node(&head->next, head);
			head = head->next;
			group_has_elem = 0;
		}
		else
		{
			append_token(tab[i], head);
			group_has_elem = 1;
		}
		i++;
	}
	free(tab);
	return(1);
}


int	main(void)
{
	t_cmd	*head;
	char *input;

	head = NULL;
	init_node(&head, NULL);
	if (!head)
		return(0);
	input = readline(PROMPT);
	int i = 4;
	while(i)
	{
		tokenizator(input, head);
		// handle_cmd(head)
		add_history(input);
		free(input);
		//free_lst(head)
		//head = malloc(sizeof(t_cmd));
		//if (!head)
		//	return(0);
		input = readline(PROMPT);
		i--;
	}
	rl_clear_history();
	free(input);
	
	//input = first_word("get the first word");
	//printf("input: %s\n", input);
	//free(input);
	return (1);
}
