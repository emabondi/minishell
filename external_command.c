/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:36:59 by atarsi            #+#    #+#             */
/*   Updated: 2022/10/31 18:20:51 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			printf("%s\n", "EXECVE");
		i++;
		//if (access())	
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
