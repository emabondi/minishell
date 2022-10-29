/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:36:59 by atarsi            #+#    #+#             */
/*   Updated: 2022/10/29 18:23:44 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	ft_find_path(t_mini *mini, char **cmd)
{
	char	*paths;
	char	**pos_path;
	int		i;

	paths = ft_get_env_var(mini, "PATH");
	pos_path = ft_smart_split(paths, ":");
	i = 0;
	while (!ft_isspace(cmd[0][i])
		i++;
	printf("%s", cmd[0]);
	i = 0;
	// while (pos_path[i] != NULL)
	// {
		
	// 	if (access())	
	// }
	return (0);
}

int	ft_ext_cmd(char **cmd, t_mini *mini)
{
	// if (strchr())
	// //gestire ./
	// else
		ft_find_path(mini, cmd);
	
	return (0);
}
