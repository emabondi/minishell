/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolaiac <ccolaiac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:24:09 by atarsi            #+#    #+#             */
/*   Updated: 2022/12/10 18:00:27 by ccolaiac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_heredocchiamo(char *sub, int *fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(sub, line, ft_strlen(sub)) == 0 \
			&& ft_strlen(sub) == ft_strlen(line))
		{
			free (line);
			exit (0);
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
}

void	ft_heredoc(char *sub)
{
	int	fd[2];
	int	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		ft_heredocchiamo(sub, fd);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		wait(NULL);
	}
}

int	ft_output_rd(char *str, int type)
{
	int	fd;

	if (type == 1)
		fd = open(str, O_CREAT | O_WRONLY | O_APPEND, 0664);
	else
		fd = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd == -1)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	ft_input_rd(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY, S_IRWXU);
	if (fd == -1)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	dup2(fd, 0);
	close(fd);
	return (0);
}

char	*ft_cut_sub(char *src, int start, int start2)
{
	char	*head;
	char	*tail;
	char	*new_cmd;

	head = (char *) malloc (sizeof(char) * (start + 1));
	ft_strlcpy(head, src, start);
	tail = ft_strdup(src + start2);
	if (start == 0)
	{
		free(head);
		return (tail);
	}
	new_cmd = ft_strjoin(head, tail);
	free(head);
	free(tail);
	return (new_cmd);
}
