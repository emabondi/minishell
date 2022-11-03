/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:36:59 by atarsi            #+#    #+#             */
/*   Updated: 2022/11/03 15:08:28 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_forkamelo_tutto(t_mini *mini, char *path, char **cmd)
{
	int		ret;
	pid_t	pid;

	ret = 0;
	pid = fork();
	if (pid == 0)
		execve(path, cmd, mini->env);
	else
		waitpid(pid, &ret, 0);
	return (ret);
}

char	*ft_get_path(t_mini *mini)
{
	int		i;
	char	*path;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], "PATH=", 5) == 0)
			path = ft_strdup(ft_strchr(mini->env[i], '=') + 1);
		i++;
	}
	return (path);
}

int	ft_find_path(t_mini *mini, char **cmd)
{
	char	*path;
	char	**pos_path;
	char	*temp;
	int		i;

	path = ft_get_path(mini);
	pos_path = ft_split(path, ':');
	i = 0;
	while (pos_path[i])
	{
		temp = ft_strjoin(pos_path[i], "/");
		free (pos_path[i]);
		pos_path[i] = ft_strjoin(temp, cmd[0]);
		if (access(pos_path[i], R_OK) == 0)
			ft_forkamelo_tutto(mini, pos_path[i], cmd);
		i++;
		free (temp);
	}
	free (path);
	ft_free_matrix(pos_path);
	return (0);
}

int	ft_ext_cmd(t_mini *mini, char **cmd)
{
/*
	if (strchr())
		gestire ./
	else
*/	
	(void)mini;
	ft_find_path(mini, cmd);
	return (0);
}
