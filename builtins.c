/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:24:38 by ebondi            #+#    #+#             */
/*   Updated: 2022/10/29 17:05:06 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(t_mini *mini)
{
	// ft_putendl_fd("exit", 1);
	mini->exit = 1;
	return ;
}

void	builtin_env(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->env[i])
	{
		if(ft_strchr(mini->env[i], '='))
			printf("%s\n", mini->env[i]);
		i++;
	}
}

void	ft_only_export(t_mini *mini)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	mini->export = ft_export(mini);
	while (mini->env[i])
	{
		key = ft_substr(mini->env[i], 0, ft_strchr(mini->env[i], '=') - mini->env[i]);
		if (ft_strchr(mini->env[i], '=') != NULL)
		{
			value = ft_strchr(mini->env[i], '=') + 1;
			printf("declare -x %s=\"%s\"\n", key, value);
		}
		else
			printf("declare -x %s\n", key);
		free(key); 
		i++;
	}
	ft_free_matrix(mini->export);
}

void	builtin_export(t_mini *mini, char **cmd)
{
	if (!cmd[1])
	{
		ft_only_export(mini);
		return ;
	}
	
}
