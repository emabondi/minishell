/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:24:09 by atarsi            #+#    #+#             */
/*   Updated: 2022/11/29 10:37:21 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int redirection(char *file, int type)
{
    int fd;

    if (type == 1)
        fd = open(file, O_WRITE, 0_APPEND);
    else
        fd = open(file, O_WRITE, 0_truncate);
    if (fd == -1)
    {
        error;
        return -1;
    }
    dup2(fd, 1)l;
    return (0);
}
int redirection(char *file, int type)
{
    int fd;

    if (type == 1)
        fd = open(file, 0_READ);
    if (fd == -1)
    {
        error;
        return -1;
    }
    dup2(f)l;
    return (0);
}*/

static void	ft_heredocchiamo(char *sub, int *fd)
{
	char	*line;

	while (1)
	{
		write(1, ">", 1);
		line = get_next_line(0);
		if (ft_strncmp(sub, line, ft_strlen(sub)) == 0 \
			&& ft_strlen(sub) == ft_strlen(line) - 1)
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

char	*ft_rd_arg(char *cmd, int *j, int *z)
{
	char	*sub;

	while (cmd[*j] == '<' || cmd[*j] == '>' || cmd[*j] == ' ')
		(*j)++;
	if (cmd[*j] == '\"')
	{
		(*j)++;
		while (cmd[*z + *j] != '\"')
			(*z)++;
		sub = ft_substr(cmd, *j, (*z)++);
	}
	else if (cmd[*j] == '\'')
	{
		(*j)++;
		while (cmd[*z + *j] != '\'')
			(*z)++;
		sub = ft_substr(cmd, *j, (*z)++);
	}
	else
	{
		while (cmd[*z + *j] && cmd[*z + *j] != ' ' )
			(*z)++;
		sub = ft_substr(cmd, *j, *z);
	}
	return (sub);
}

char *ft_redirection2(char *cmd, int start)
{
	int		j;
	int		z;
	char	*sub;
	char	*new_cmd;

	j = start;
	z = 0;
	sub = ft_rd_arg(cmd, &j, &z);
	new_cmd = ft_cut_sub(cmd, start, j + z);
	if (cmd[start] == '<' && (cmd[start + 1] != '\0' && cmd[start + 1] != '<'))
		ft_input_rd(sub);
	else if ((cmd[start] == '<' && (cmd[start + 1] != '\0' && cmd[start + 1] == '<')))
	 	ft_heredoc(sub);
	else if (cmd[start] == '>' && (cmd[start + 1] != '\0' && cmd[start + 1] != '>'))
		ft_output_rd(sub, 0);
	else if (cmd[start] == '>' && (cmd[start + 1] != '\0' && cmd[start + 1] == '>'))
		ft_output_rd(sub, 1);
	free (sub);
	free (cmd);
	return (new_cmd);
}

char *ft_redirection(char *cmd)
{
	int		i;
	char	*new_cmd;

	i = 0;
	new_cmd = ft_strdup(cmd);
	while (new_cmd[i])
	{
		if (new_cmd[i] == '\"')
		{
			i++;
			while (new_cmd[i] != '\"')
				i++;
			i++;
		}
		if (new_cmd[i] == '\'')
		{
			i++;
			while (new_cmd[i] != '\'')
				i++;
			i++;
		}
		if (new_cmd[i] == '<' || new_cmd[i] == '>')
		{
			new_cmd = ft_redirection2(new_cmd, i);
			//ft_putstr_fd("\nnew_cmd:", 1);
			//ft_putstr_fd(new_cmd, 1);
		}
		else
			i++;
	}
	free (cmd);
//	ft_putstr_fd("\ncomando tagliato:", 1);
//	ft_putstr_fd(new_cmd, 1);
//	ft_putstr_fd("\n", 1);
	return (new_cmd);
}