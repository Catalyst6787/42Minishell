#ifndef MINI_H
# define MINI_H

// libft
# include "libft/libft.h"

# include <stdio.h>

// readline
# include <readline/readline.h>
# include <readline/history.h>

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



#endif