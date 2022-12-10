/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:21:49 by ebondi            #+#    #+#             */
/*   Updated: 2022/12/10 21:12:40 by ebondi           ###   ########.fr       */
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

void	expand_env_var_helper(char *str, int *i)
{
	if (str[*i] == 39)
	{
		(*i)++;
		while (str[*i] && str[*i] != 39)
			(*i)++;
		(*i)++;
	}
	else
		(*i)++;
}
