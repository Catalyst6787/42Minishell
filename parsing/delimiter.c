#include "../mini.h"

static char	*get_full_file(int fd)
{
	int first = 1;
	char *buf = "";
	char *tmp = NULL;
	char *full_file = get_next_line(fd);
	if (!full_file)
		return(NULL);
	while(buf || first)
	{
		tmp = ft_strjoin(full_file, buf);
		free(full_file);
		if (!first)
			free(buf);
		first = 0;
		buf = NULL;
		full_file = tmp;
		buf = get_next_line(fd);
	}
	return(full_file);
}

// return copy of string until delimiter
static char	*get_until_string(const char *string, const char *delimiter)
{
	int	i;

	i = 0;
	if (!string)
		return(NULL);
	if (!delimiter || !delimiter[0])
		return(ft_strdup(string));
	while(string[i])
	{
		if (!ft_strncmp((string + i), delimiter, ft_strlen(delimiter)))
		{
			if (i == 0)
				return (NULL);
			return (ft_substr(string, 0, i));
		}
		i++; 
	}
	return(ft_strdup(string));
}

// returnd new fd to tmpfile containing string until delimiter. Closes original fd.
int	delimiter(int fd, char *del)
{
	int new_fd;
	char *full_file = get_full_file(fd);
	char *until_string = get_until_string(fd, del);
	
	new_fd = open(".", __O_TMPFILE, O_RDWR);
	write(new_fd, until_string, ft_strlen(until_string));
	free(full_file);
	free(until_string);
	close(fd);
	return(new_fd);
}


// int	main(int ac, char **av)
// {
// 	int fd;
// 	if (ac != 3)
// 		return(printf("Usage: ./a.out file\n"), 1);
// 	fd = open(av[1], O_RDONLY);
// 	if (fd < 0)
// 		return(printf("Error opening file\n"), 1);
// 	char *full_file = get_full_file(fd);
// 	if (ft_strlen(full_file))
// 	{
// 		//printf("%s\n", full_file);
// 		char *until_del = get_until_string(full_file, av[2]);
// 		printf("%s", until_del);
// 		free(until_del);
// 	}
// 	free(full_file);
// 	close(fd);
// 	return(0);
// }