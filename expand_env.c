/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:22:54 by ebondi            #+#    #+#             */
/*   Updated: 2022/10/14 16:41:07 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == " " || c == "\t" || c == "\n" || c == "\v" || c == "\f" || c == "\r")
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

char	*expand_env_var(char *str)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == "$")
			while(!ft_isspace(str[i]))
	}
	return str;
}