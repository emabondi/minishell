/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolaiac <ccolaiac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:21:49 by ebondi            #+#    #+#             */
/*   Updated: 2022/12/10 18:37:09 by ccolaiac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_whats_exit_status(char *str, int i)
{
	char	*finalstr;
	char	*new;
	char	*num;

	finalstr = ft_substr(str, 0, i);
	num = ft_itoa(g_exit_status);
	new = ft_strjoin(finalstr, num);
	free (finalstr);
	free (num);
	finalstr = ft_strjoin(new, (str + i + 2));
	free (new);
	free(str);
	return (finalstr);
}

void	expand_env_var_helper(t_mini *mini, char *str, int i)
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
