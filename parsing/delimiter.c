#include "../mini.h"

char	*get_full_file(int fd)
{
	int	totlen;
	int	i = 0;
	int	j = 0;
	char *buf = NULL;
	char *tmp = NULL;
	char *full_file = get_next_line(fd);
	if (!full_file)
		return(NULL);
	while(buf)
	{
		totlen = ft_strlen(buf) + ft_strlen(full_file);
		tmp = malloc(sizeof(char) * (totlen + 1));
		tmp[totlen] = '\0';
		while(full_file[i])
			tmp[i] = full_file[i++];
		while(buf[j])
		{
			tmp[i++] = buf[j++];
		}
		free(full_file);
		free(buf);
		buf = NULL;
		full_file = tmp;
		buf = get_next_line(fd);
	}
	return(full_file);
}


int	delimiter(int fd, char *del)
{
	int i;
	int j;
	i = 0;
	j = 0;
	char *full_file = get_full_file(fd);
	while(full_file[i])
	{
		if (full_file[i] == del[0])
		{
			while(full_file[i])
		}
	}
}