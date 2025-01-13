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

typedef struct s_env
{
	char			*name;
	char			*value;
	int				export;
	struct s_env	*next;
}	t_env;

// externs
void	child_process_for_externs(char **tab, char **envp);
void	ft_free_split(char **tab);

// EXECUTION

int	redirect_operator(t_cmd *node, char **envp, t_env *env);

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

// envp
void	add_env_node(t_env **env, char *name, char *value, int export);
void	init_envp(t_env **env, char **envp);
t_env	*get_in_envp(t_env *env, char *key, int size_key);
void	change_value_in_envp(t_env *env, char *key, int size_key, char *new_value);
void	delete_export_node(t_env **env, char *key, int size_key);

// builtins
void	ft_echo(char **av);
void	ft_env(t_env *env);
void	ft_pwd(void);
void	ft_cd(char **av, t_env *env);
void	ft_export(char **av, t_env *env);
void	ft_unset(char **av, t_env *env);

// utils
int		ft_strcmp(char *s1, char *s2);

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

# define PIPE 10
# define RED_INPUT 11
# define RED_OUTPUT 12
# define RED_INPUT_DEL 13
# define RED_OUTPUT_APPEND 14

# define AND 15
# define OR 16
# define PAR_OPEN 17
# define PAR_CLOSE 18


#endif