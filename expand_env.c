/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:22:54 by ebondi            #+#    #+#             */
/*   Updated: 2022/12/01 16:55:27 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	confront_env_var(char *env_line, char *str)
{
	int	i;

	i = 0;
	while (env_line[i] && env_line[i] != '=')
	{
		if (env_line[i] - str[i] != 0)
			return (0);
		i++;
	}
	if (i != (int)ft_strlen(str))
		return (0);
	return (1);
}

char	*ft_get_env_var(t_mini *mini, char *str)
{
	int	i;

	i = 0;
	//while (*str != '$')
	//	str++;
	str++;
	while (mini->env[i])
	{
		if (confront_env_var(mini->env[i], str) &&\
			ft_strlen(mini->env[i]) > ft_strlen(str) + 1)
			return (ft_strchr(mini->env[i], '=') + 1);
		i++;
	}
	return (NULL);
}

char	*expand_env_var3(char *str, char *var)
{
	char		*final_str;
	int			i;
	int			j;
	int			len;

	len = ft_strlen(var);
	i = ft_strlen(str);
	final_str = malloc(sizeof(char) * (i - len + 1));
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			i += len;
		final_str[j] = str[i];
		i++;
		j++;
	}
	final_str[j] = '\0';
	free(var);
	free(str);
	return (final_str);
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
		return (expand_env_var3(str, var));
	return (str);
}

char	*expand_env_var(t_mini *mini, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			str = ft_whats_exit_status(str, i);
		else if (str[i] == '$' && ft_isalnum(str[i + 1]))
			str = expand_env_var2(mini, str, i);
		else if (str[i] == 34)
		{
			i++;
			while (str[i] && str[i] != 34)
			{
				if (str[i] == '$' && str[i + 1] == '?')
					str = ft_whats_exit_status(str, i);
				else if (str[i] == '$' && ft_isalnum(str[i + 1]))
					str = expand_env_var2(mini, str, i);
				i++;
			}
		}
		else if (str[i] == 39)
		{
			i++;
			while (str[i] && str[i] != 39)
				i++;
		}
		i++;
	}
	return (str);
}
