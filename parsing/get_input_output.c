#include "../mini.h"

t_cmd *get_input_output(t_cmd **head, t_env *env)
{
	t_cmd	*tail;
	t_cmd	*next;
	t_cmd	*last;

	tail = *head;
	next = tail;
	tail->input = 0;
	while (tail)
	{
		next = tail->next;
		if (which_cmd(tail->tab[0]) == PIPE)
		{
			if (tail->prev && tail->next)
			{
				tail->prev->output = 1;
				tail->next->input = 0;
				node_remove(tail);
				tail = NULL;
			}
			else
				return(printf("Error in get_input_output, Cannot use a pipe without input and ouptut."), NULL);
		}
		else if (which_cmd(tail->tab[0]) == RED_INPUT)
		{
			if (tail->next && tail->next->next) // Maybe check if tail->next->tab is a valid file / no tab[1]
			{
				tail->next->next->input = open(tail->next->tab[0], O_RDONLY);
				if ((tail->next->next->input) == -1)
					return(printf("Error in get_input_output, file '%s' doesnt exist\n", tail->next->tab[0]), tail->next->next->input = 0, NULL);
				next = tail->next->next;
				node_remove(tail->next);
				node_remove(tail);
				tail = NULL;
			}
			else if (tail->next && tail->prev)
			{
				tail->prev->input = open(tail->next->tab[0], O_RDONLY);
				if ((tail->prev->input) == -1)
					return(printf("Error in get_input_output, file '%s' doesnt exist\n", tail->next->tab[0]), tail->prev->input = 0, NULL);
				next = tail->next->next;
				node_remove(tail->next);
				node_remove(tail);
				tail = NULL;
			}
			else
				return(printf("Error in get_input_output, Cannot use a < without input and output."), NULL);
		}
		else if (which_cmd(tail->tab[0]) == RED_OUTPUT)
		{
			if (tail->next && tail->prev) // Maybe check if tail->next->tab is a valid file / no tab[1]
			{
				tail->prev->output = open(tail->next->tab[0], O_WRONLY | O_CREAT | O_TRUNC, 0666);
				next = tail->next->next;
				node_remove(tail->next);
				node_remove(tail);
				tail = NULL;
			}
			else if (tail->next && tail->next->next)
			{
				tail->next->next->output = open(tail->next->tab[0], O_WRONLY | O_CREAT | O_TRUNC, 0666);
				next = tail->next->next;
				node_remove(tail->next);
				node_remove(tail);
				tail = NULL;
			}
			else
				return(printf("Error in get_input_output, Cannot use a > without input and output.\n"), NULL);
		}
		else if (which_cmd(tail->tab[0]) == RED_INPUT_DEL)
		{
			if (tail->next && tail->prev)
			{
				int sigint_received = 0;
				append_node_before(&tail->prev, heredoc(tail->next->tab[0], env, &sigint_received), head);
				if (sigint_received == 1)
					return(free_list(head), NULL);
				last = tail->prev;
				tail->prev->input = 0;
				next = tail->next->next;
				node_remove(tail->next);
				node_remove(tail);
				tail = NULL;
			}
			else if (tail->next && tail->next->next)
			{
				int sigint_received = 0;
				append_node_before(&tail, heredoc(tail->next->tab[0], env, &sigint_received), head);
				if (sigint_received == 1)
					return(free_list(head), NULL);
				last = tail->next->next;
				tail->next->next->input = 0;
				next = tail->next->next;
				node_remove(tail->next);
				node_remove(tail);
				tail = NULL;
			}
			else
				return(printf("Error in get_input_output, Cannot use a << without input and output.\n"), NULL);
		}
		else if (which_cmd(tail->tab[0]) == RED_OUTPUT_APPEND)
		{
			if (tail->next && tail->prev) // Maybe check if tail->next->tab is a valid file / no tab[1]
			{
				tail->prev->output = open(tail->next->tab[0], O_WRONLY | O_CREAT | O_APPEND, 0666);
				next = tail->next->next;
				node_remove(tail->next);
				node_remove(tail);
				tail = NULL;
			}
			else if (tail->next && tail->next->next)
			{
				tail->next->next->output = open(tail->next->tab[0], O_WRONLY | O_CREAT | O_APPEND, 0666);
				next = tail->next->next;
				node_remove(tail->next);
				node_remove(tail);
				tail = NULL;
			}
			else
				return(printf("Error in get_input_output, Cannot use a >> without input and output."), NULL);
		}
		if (tail)
			last = tail;
		tail = next;
	}
	//(void)last;
	//last->output = 1;
	while(last && last->prev)
		last = last->prev;
	//return(*head);
	return(last);
}
