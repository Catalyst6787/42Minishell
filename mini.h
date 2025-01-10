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

typedef struct s_cmd
{
	int				id;
	char			**tab;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

// externs
void	child_process_for_externs(char *s, char **envp);
void	ft_free_split(char **tab);

// PARSING

char	*rem_char(char *s, int t);
char	*remove_useless_quotes(char *s);
char	*remove_lone_quotes(char *s);
char	*clean_input(char *s);
int		end_of_token(char *s);
char	*token_dup(char *s);
char	*quoted_token_dup(char *s);
char	**split_tokens(char *s);
int		count_tokens(char *s);
void	append_node(t_cmd **head, char **tab);
char	**sub_tab(char **tab, int from, int to);
void	group_tokens(t_cmd **head, char **tab);

// PARSING_UTILS

int		which_cmd(char *cmd);
int		is_special(char c);
int		is_separator(char *s);
int		next_separator(char **tab, int i);
int		isquote(char c);
int		get_last_char(char *s, char c);
int		next_char(char *s, char c);
int		count_chars(char *s, char c);
void	print_tab(char **tab);
void	free_tab(char **tab);
void	print_list(t_cmd *head);
void	free_list(t_cmd **head);


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

#endif