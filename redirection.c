/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:24:09 by atarsi            #+#    #+#             */
/*   Updated: 2022/11/23 19:39:34 by ebondi           ###   ########.fr       */
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

void	ft_redirection2(t_mini *mini, int start, int n)
{
	int		j;
	int		z;
	char	*sub;
	char	*new_cmd;

	j = start;
	z = 0;
	sub = ft_rd_arg(mini->cmds[n], &j, &z);
	new_cmd = ft_cut_sub(mini->cmds[n], start, j + z);
	if (mini->cmds[n][start] == '<' && (mini->cmds[n][start + 1] != '\0' && mini->cmds[n][start + 1] != '<'))
		ft_input_rd(sub);
	else if ((mini->cmds[n][start] == '<' && (mini->cmds[n][start + 1] != '\0' && mini->cmds[n][start + 1] == '<')))
	 	ft_heredoc(sub);
	else if (mini->cmds[n][start] == '>' && (mini->cmds[n][start + 1] != '\0' && mini->cmds[n][start + 1] != '>'))
		ft_output_rd(sub, 0);
	else if (mini->cmds[n][start] == '>' && (mini->cmds[n][start + 1] != '\0' && mini->cmds[n][start + 1] == '>'))
		ft_output_rd(sub, 1);
	free (sub);
	free (mini->cmds[n]);
	mini->cmds[n] = new_cmd;
}

int	ft_redirection(t_mini *mini, int n)
{
	int		i;

	i = 0;
	while (mini->cmds[n][i])
	{
		if (mini->cmds[n][i] == '\"')
		{
			i++;
			while (mini->cmds[n][i] != '\"')
				i++;
			i++;
		}
		if (mini->cmds[n][i] == '\'')
		{
			i++;
			while (mini->cmds[n][i] != '\'')
				i++;
			i++;
		}
		if (mini->cmds[n][i] == '<' || mini->cmds[n][i] == '>')
			ft_redirection2(mini, i, n);
		i++;
	}
	return (0);
}