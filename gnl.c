#include "minishell.h"

char	*get_next_line_helper(char *a, int i)
{
	char	*new_a;

	new_a = malloc(i + 1);
	if (!new_a)
		return (NULL);
	i = 0;
	while (a[i])
	{
		new_a[i] = a[i];
		i++;
	}
	new_a[i] = '\0';
	return (new_a);
}

char	*get_next_line(int fd)
{
	char	a[999999];
	char	buffer[1];
	int		i;

	if (fd < 0)
		return (NULL);
	i = 0;
	a[i] = 0;
	while (read(fd, buffer, 1) == 1)
	{
		a[i] = buffer[0];
		a[i + 1] = '\0';
		if (a[i] == '\n')
			break ;
		i++;
	}
	if (!a[0])
		return (NULL);
	return (get_next_line_helper(a, i));
}