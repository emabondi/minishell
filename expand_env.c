/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:22:54 by ebondi            #+#    #+#             */
/*   Updated: 2022/10/14 20:05:40 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v'\
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

char	*ft_get_env_var(t_mini *mini, char *str)
{
	int	i;

	i = 0;
	str++;
	while (mini->env[i])
	{
		if (!ft_strncmp(mini->env[i], str, ft_strlen(str)))
			return (ft_strchr(mini->env[i], '=') + 1);
		i++;
	}
	return (NULL);
}

void	expand_env_var2(t_mini *mini, char *str, int i)
{
	int		j;
	char	*var;
	char	*expanded_var;
	char 	*new;

	j = 0;
	while (!ft_isspace(str[i + j]) && str[i + j] /*&& !ft_iscommand(str[i])*/)
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
		printf("%s\n", var);
		free(new);
		//free(str);
		str = var;
	}
	else
		free(var);
	return ;
}

char	*expand_env_var(t_mini *mini, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			expand_env_var2(mini, str, i);
		i++;
	}
	return (str);
}
