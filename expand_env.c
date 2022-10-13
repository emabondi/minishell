/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:22:54 by ebondi            #+#    #+#             */
/*   Updated: 2022/10/13 21:09:13 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	return str;
}