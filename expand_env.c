/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:22:54 by ebondi            #+#    #+#             */
/*   Updated: 2022/11/02 18:29:32 by atarsi           ###   ########.fr       */
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
	int	len_str;

	i = 0;
	while (*str != '$')
		str++;
	str++;
	len_str = ft_strlen(str);
	if (len_str == 1)
		return (NULL);
	while (mini->env[i])
	{
		if (confront_env_var(mini->env[i], str))
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
	printf("expanded:%s\n", expanded_var);
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
		if (str[i] == '$' && ft_isalnum(str[i + 1]))
			str = expand_env_var2(mini, str, i);
		else if (str[i] == 34)
		{
			i++;
			while (str[i] && str[i] != 34)
			{
				if (str[i] == '$' && ft_isalnum(str[i + 1]))
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
