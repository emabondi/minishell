/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolaiac <ccolaiac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:35:08 by atarsi            #+#    #+#             */
/*   Updated: 2022/12/09 14:54:31 by ccolaiac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_count(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

void	quotes_copy2(char *cmd, int	*i, int	*j, char *new)
{
	char	c;

	c = cmd[*i];
	(*i)++;
	while (cmd[*i] != c)
	{
		new[*j] = cmd[*i];
		(*i)++;
		(*j)++;
	}
	(*i)++;
}

char	*quotes_copy(char *cmd)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = (char *) malloc (sizeof(char) * ft_strlen(cmd) + 1);
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			quotes_copy2(cmd, &i, &j, new);
		else
		{
			new[j] = cmd[i];
			i++;
			j++;
		}
	}
	new[j] = '\0';
	free(cmd);
	return (new);
}

char	**ft_quotes(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (quotes_count(cmd[i]))
			cmd[i] = quotes_copy(cmd[i]);
		i++;
	}
	return (cmd);
}