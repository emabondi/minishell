/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:24:38 by ebondi            #+#    #+#             */
/*   Updated: 2022/12/02 16:33:56 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	builtin_export2(t_mini *mini, char *cmd)
{
	char	*key;

	if (ft_strchr(cmd, '=') && *(ft_strchr(cmd, '=') - 1) == '+')
	{
		key = ft_substr(cmd, 0, ft_strchr(cmd, '+') - cmd);
		ft_export_two(mini, key, ft_strchr(cmd, '=') + 1, 1);
	}
	else if (ft_strchr(cmd, '='))
	{
		key = ft_substr(cmd, 0, ft_strchr(cmd, '=') - cmd);
		ft_export_two(mini, key, ft_strchr(cmd, '=') + 1, 2);
	}
	else
	{
		key = ft_strdup(cmd);
		ft_export_two(mini, key, NULL, 3);
	}
	free(key);
}

void	builtin_export(t_mini *mini, char **cmd)
{
	int	i;

	i = 1;
	if (!cmd[1])
	{
		ft_only_export(mini);
		return ;
	}
	while(cmd[i])
	{
		if ((cmd[i][0] != '_' && !ft_isalpha(cmd[i][0])) || ft_isalnum_mod(cmd))
		{
			ft_putstr_fd("minisburo: export: '", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			exit_status = 1;
			return ;
		}
		builtin_export2(mini, cmd[i]);
		i++;
	}
	exit_status = 0;
}
