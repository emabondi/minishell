/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolaiac <ccolaiac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:51:46 by ccolaiac          #+#    #+#             */
/*   Updated: 2022/12/10 17:42:26 by ccolaiac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_only_export(t_mini *mini)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	mini->export = ft_export(mini);
	while (mini->export[i])
	{
		key = ft_substr(mini->export[i], 0, \
			ft_strchr(mini->export[i], '=') - mini->export[i]);
		if (ft_strchr(mini->export[i], '=') != NULL)
		{
			value = ft_strchr(mini->export[i], '=') + 1;
			printf("declare -x %s=\"%s\"\n", key, value);
		}
		else
			printf("declare -x %s\n", key);
		free (key);
		i++;
	}
	ft_free_matrix(mini->export);
}

void	ft_export_replace(char **env, char *key, char *value)
{
	int		i;
	char	*a;

	i = 0;
	if (!value)
		return ;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, ft_strlen(key)))
		{
			free(env[i]);
			a = ft_strjoin(key, "=");
			if (value)
				env[i] = ft_strjoin(a, value);
			else
				env[i] = ft_strdup(key);
			free(a);
			return ;
		}
		i++;
	}
}

void	ft_export_add(char **env, char *key, char *value)
{
	int		i;
	char	*a;

	i = 0;
	if (!value)
		return ;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, ft_strlen(key)))
		{
			a = ft_strjoin(env[i], value);
			free(env[i]);
			env[i] = a;
			return ;
		}
		i++;
	}
}

void	ft_export_insert(t_mini *mini, char **env, char *key, char *value)
{
	int		i;
	char	**new;
	char	*insert;

	i = 0;
	new = (char **)malloc(sizeof(char *) * (ft_len_matrix(env) + 2));
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	insert = ft_strjoin(key, "=");
	if (value)
		new[i] = ft_strjoin(insert, value);
	else
		new[i] = ft_strdup(key);
	free(insert);
	new[i + 1] = NULL;
	ft_free_matrix(mini->env);
	mini->env = new;
}

void	ft_export_two(t_mini *mini, char *key, char *value, int i)
{
	if (ft_get_env_value(mini->env, key) && (i == 3 || i == 2))
		ft_export_replace(mini->env, key, value);
	else if (ft_get_env_value(mini->env, key) && i == 1)
		ft_export_add(mini->env, key, value);
	else
		ft_export_insert(mini, mini->env, key, value);
}
