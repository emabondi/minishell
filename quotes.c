/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:35:08 by atarsi            #+#    #+#             */
/*   Updated: 2022/11/10 15:35:40 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_delete_quotes(char	*cmd, char quote)
{
	int		i;
	int		k;
	char	*new;

	i = 0;
	while (cmd[i])
	{
		new = malloc(sizeof(char) * ft_strlen(cmd) - 1);
		k = 0;
		while (cmd[i])
		{
			if (cmd[i] != quote)
			{
				new[k] = cmd[i];
				k++;
			}
			i++;
		}
		new[k] = 0;
	}
	free(cmd);
	return (new);
}

char	*ft_quotes2(char *cmd, int *flag, char quote, int b)
{
	if (*flag == b)
		*flag = 0;
	else
		*flag = b;
	return (ft_delete_quotes(cmd, quote));
}

char	**ft_quotes(char **cmd)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	flag = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '\'' && flag != 2)
			{
				cmd[i] = ft_quotes2(cmd[i], &flag, '\'', 1);
			}
			else if (cmd[i][j] == '\"' && flag != 1)
			{
				cmd[i] = ft_quotes2(cmd[i], &flag, '\"', 2);
			}
			j++;
		}
		i++;
	}
	return (cmd);
}