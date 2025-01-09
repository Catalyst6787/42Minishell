#include "mini.h"

// remove char at s[i], frees original s and returns updated string
char	*rem_char(char *s, int t)
{
	int i;
	int j;
	char *nstr;
	nstr = malloc(sizeof(char) * ft_strlen(s));
	nstr[ft_strlen(s) - 1] = '\0';
	i = 0;
	j = 0;
	while(s[j])
	{
		if (j != t)
		{
			nstr[i] = s[j];
			i++;
			j++;
		}
		else
			j++;

	}
	free(s);
	return(nstr);
}

char	*remove_useless_quotes(char *s)
{
	int i;

	i = 0;
	while(s[i] && s[i + 1])
	{
		if ((s[i] == '\'' && s[i + 1] == '\'') || (s[i] == '\"' && s[i + 1] == '\"'))
		{
			// rem two useless quotes
			s = rem_char(s, i); // returns string with s[i] removed (frees og)
			s = rem_char(s, i);
			i = 0;
		}
		i++;
	}
	return(s);
}

char	*remove_lone_quotes(char *s)
{
	if ((count_chars(s, '\'') % 2) != 0)
		s = rem_char(s, get_last_char(s, '\''));
	if ((count_chars(s, '\"') % 2) != 0)
		s = rem_char(s, get_last_char(s, '\"'));
	return(s);
}

char	*clean_input(char *s)
{
	// expand $
	s = remove_lone_quotes(s); // this makes statements such as echo " quotes:' " impossible
	s = remove_useless_quotes(s); 
	// split by space except quoted
	// replace wildcard
	// remove quotes
	return(s);
}

int	end_of_token(char *s)
{
	if (isquote(s[0]))
		return(next_char(s, s[0]));
	else
		return(next_char(s, ' '));
}

char	*token_dup(char *s)
{
	int i;
	int t;
	char *dup;

	i = 0;
	t = 0;
	t = end_of_token(s);
	dup = malloc(sizeof(char) * t + 1);
	dup[t] = '\0';
	while(i < t)
	{
		dup[i] = s[i];
		i++;
	}
	return(dup);
}

char	*quoted_token_dup(char *s)
{
	int i;
	int t;

	i = 0;
	t = 0;
	char *dup;
	t = end_of_token(s);
	dup = malloc(sizeof(char) * t);
	dup[t - 1] = '\0';
	while(i < t - 1)
	{
		dup[i] = s[i + 1];
		i++;
	}
	return(dup);
}

char	**split_tokens(char *s)
{
	int		i;
	int		j;
	int		nbr_of_tokens;
	char	**tab;

	i = 0;
	j = 0;
	nbr_of_tokens = count_tokens(s);
	tab = malloc(sizeof(char *) * nbr_of_tokens + 1);
	tab[nbr_of_tokens] = NULL;
	while(s[i])
	{
		if (s[i] == ' ')
			i++;
		else if (isquote(s[i]))
		{
			tab[j] = quoted_token_dup(s + i);
			i = end_of_token(s + i) + i + 1;
			j++;
		}
		else
		{
			tab[j] = token_dup(s + i);
			i = end_of_token(s + i) + i;
			j++;
		}
	}
	return(tab);
}

int	count_tokens(char *s)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while(s[i])
	{
		if (s[i] == ' ')
			i++;
		else if (isquote(s[i]))
		{
			i = end_of_token(s + i) + i + 1;
			c++;
		}
		else
		{
			i = end_of_token(s + i) + i;
			c++;
		}
	}
	return (c);
}