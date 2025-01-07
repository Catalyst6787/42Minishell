#ifndef MINI_H
# define MINI_H

// libft
# include "libft/libft.h"

// libc
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

// readline
# include <readline/readline.h>
# include <readline/history.h>

// processus
# include <sys/wait.h>

// externs
void	child_process_for_externs(char *s, char **envp);
void	ft_free_split(char **tab);


# define PROMPT " > "

// define commands

# define ECHO 0
# define CD 1
# define PWD 2
# define EXPORT 3
# define UNSET 4
# define ENV 5
# define EXIT 6
# define EXTERNAL 7

typedef struct s_cmd
{
	int				id;
	char			**tab;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

int	which_cmd(char *cmd);
int	is_special(char c);


#endif