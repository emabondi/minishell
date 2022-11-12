/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolaiac <ccolaiac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:24:38 by ebondi            #+#    #+#             */
/*   Updated: 2022/11/11 16:03:36 by ccolaiac         ###   ########.fr       */
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
		if (ft_strchr(mini->env[i], '='))
			printf("%s\n", mini->env[i]);
		i++;
	}
}

void	builtin_pwd(t_mini *mini)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putendl_fd(pwd, 1);
		exit_status = 0;
		free(pwd);
		return ;
	}
	exit_status = 1;
	free(pwd);
	(void)mini;
}

void	builtin_export2(t_mini *mini, char **cmd)
{
	char	*key;

	if (ft_strchr(cmd[1], '=') && *(ft_strchr(cmd[1], '=') - 1) == '+')
	{
		key = ft_substr(cmd[1], 0, ft_strchr(cmd[1], '+') - cmd[1]);
		ft_export_two(mini, key, ft_strchr(cmd[1], '=') + 1, 1);
	}
	else if (ft_strchr(cmd[1], '='))
	{
		key = ft_substr(cmd[1], 0, ft_strchr(cmd[1], '=') - cmd[1]);
		ft_export_two(mini, key, ft_strchr(cmd[1], '=') + 1, 2);
	}
	else
	{
		key = ft_strdup(cmd[1]);
		ft_export_two(mini, key, NULL, 3);
	}
	free(key);
}

void	builtin_export(t_mini *mini, char **cmd)
{
	int	i;

	i = 0;
	if (!cmd[1])
	{
		ft_only_export(mini);
		return ;
	}
	if ((cmd[1][0] != '_' && !ft_isalpha(cmd[1][0])) || !ft_isalnum_mod(cmd))
	{
		ft_putstr_fd("minisburo: export: '", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd("': not a valid identifier", 2);
		exit_status = 1;
		return ;
	}

	builtin_export2(mini, cmd);
	exit_status = 0;
}
