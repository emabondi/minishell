/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolaiac <ccolaiac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:34:17 by atarsi            #+#    #+#             */
/*   Updated: 2022/12/10 18:39:18 by ccolaiac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env_value(char **env, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, ft_strlen(str)))
			return (ft_strchr(env[i], '=') + 1);
		i++;
	}
	return (NULL);
}

char	**builtin_unset2(t_mini *mini, char **env, char *str)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = (char **)malloc(sizeof(char *) * ft_len_matrix(env));
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)))
		{
			new[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	new[j] = NULL;
	ft_free_matrix(env);
	return (new);
	(void)mini;
}

int	unset_valid(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (!ft_isascii(cmd[i]) || cmd[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

void	builtin_unset(t_mini *mini, char **cmd)
{
	int		i;

	i = 1;
	while (cmd[i])
	{
		if (!unset_valid(cmd[i]))
		{
			ft_putstr_fd("minisburo: unset: `", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("\': not a valid identifier\n", 2);
		}
		else if (ft_get_env_value(mini->env, cmd[i]) != NULL)
			mini->env = builtin_unset2(mini, mini->env, cmd[i]);
		i++;
	}
}
