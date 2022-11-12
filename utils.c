/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:05:21 by ebondi            #+#    #+#             */
/*   Updated: 2022/11/11 16:40:18 by ebondi           ###   ########.fr       */
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

int	ft_len_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		i++;
	}
	return (i);
}

int	ft_isalnum_mod(char **cmd)
{
	int i;

	i = 0;
	while (cmd[1][i])
	{
		if (cmd[1][i] == '=' || cmd[1][i] == '+')
			break ;
		return ((cmd[1][i] >= 'a' && cmd[1][i] <= 'z')
		|| (cmd[1][i] >= 'A' && cmd[1][i] <= 'Z')
		|| (cmd[1][i] >= '0' && cmd[1][i] <= '9') || (cmd[1][i] == '_'));
		i++;
	}
	return (0);
}