/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:22:54 by ebondi            #+#    #+#             */
/*   Updated: 2022/10/15 19:40:43 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

char	*ft_get_env_var(t_mini *mini, char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 1)
		return (NULL);
	str++;
	while (mini->env[i])
	{
		if (!ft_strncmp(mini->env[i], str, ft_strlen(str)))
			return (ft_strchr(mini->env[i], '=') + 1);
		i++;
	}
	return (NULL);
}

char	*expand_env_var2(t_mini *mini, char *str, int i)
{
	int		j;
	char	*var;
	char	*expanded_var;
	char	*new;

	j = 1;
	while (str[i + j] && !ft_isspace(str[i + j]) && ft_isalnum(str[i + j]))
		j++;
	var = ft_substr(str + i, 0, j);
	expanded_var = ft_get_env_var(mini, var);
	if (expanded_var != NULL)
	{
		free(var);
		var = ft_substr(str, 0, i);
		new = ft_strjoin(var, expanded_var);
		free(var);
		var = ft_strjoin(new, str +(i + j));
		free(new);
		free(str);
		return (var);
	}
	else
		free(var);
	return (str);
}

char	*expand_env_var(t_mini *mini, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			str = expand_env_var2(mini, str, i);
		else if (str[i++] == 39)
			while (str[i] && str[i] != 39)
				i++;
		i++;
	}
	return (str);
}
