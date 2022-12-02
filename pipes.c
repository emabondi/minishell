/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:15:21 by ebondi            #+#    #+#             */
/*   Updated: 2022/12/02 12:48:12 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_last_pipe(t_mini *mini, char *cmd_i, int *pid, int *tmp)
{
	char	*cmd;
	char	**cmds;

	*pid = fork();
	if (*pid == 0)
	{
		cmd = ft_redirection(cmd_i);
		dup2(*tmp, 0);
		execute_commands(mini, cmd);
		exit (0);
	}
	else
	{
		if ((mini->cmds[1] == NULL && cmd_i[0] != '\0')\
			&& (ft_strncmp(cmd_i, "exit", 4) == 0 && \
			ft_strlen (cmd_i) == 4))
		{
			cmd = ft_redirection(cmd_i);
			cmds = ft_smart_split(cmd, ' ');
			cmds = ft_quotes(cmds);
			builtin_exit(mini, cmds);
			ft_free_matrix(cmds);
		}
		close (*tmp);
		while (waitpid(-1, NULL, WUNTRACED) != -1)
			;
		*tmp = dup(0);
	}
}

void	ft_every_pipe(t_mini *mini, char *cmd_i, int *pid, int *tmp)
{
	int		fd[2];
	char	*cmd;
	//char 	*gnl;
	//int		file;

	pipe(fd);
	*pid = fork();
	if (*pid == 0)
	{
		dup2(fd[1], 1);
		close (fd[1]);
		close (fd[0]);
		dup2(*tmp, 0);
		cmd = ft_redirection(cmd_i);
		execute_commands(mini, cmd);
		free(cmd);
		exit (0);
	}
	else
	{
		close(*tmp);
		close (fd[1]);
		*tmp = fd[0];
	}
}

int	ft_pipe(t_mini *mini)
{
	int		i;
	int		pid;
    int		tmp;
	int		std_in_out[2];

	pid = 0;
	tmp = dup(0);
	i = 0;
	while (mini->cmds[i])
	{
		std_in_out[0] = dup(0);
		std_in_out[1] = dup(1);
		if (mini->cmds[i + 1] == NULL)
			ft_last_pipe(mini, mini->cmds[i], &pid, &tmp);
		else if (mini->cmds[i + 1])
			ft_every_pipe(mini, mini->cmds[i], &pid, &tmp);
		dup2(std_in_out[1], 1);
		dup2(std_in_out[0], 0);
		i++;
	}
	close (tmp);
	return (1);
}