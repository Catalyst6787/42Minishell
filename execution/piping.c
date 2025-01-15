#include "../mini.h"

void	create_pipes(t_cmd *head)
{
	t_cmd	*tail;
	int	current_pipe[2];

	tail = head;
	while(tail)
	{
		if (tail->output == 1 && tail->next && tail->next->input == 0)
		{
			pipe(current_pipe);
			tail->output = current_pipe[1];
			tail->next->input = current_pipe[0];
		}
		tail = tail->next;
	}
}

void	close_fd(t_cmd *head)
{
	t_cmd *tail;
	
	tail = head;
	while(tail)
	{
		if (tail->input != 0)
			close(tail->input);
		if (tail->output != 1)
			close(tail->output);
		tail = tail->next;
	}
}