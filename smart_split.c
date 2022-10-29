/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:49:40 by ebondi            #+#    #+#             */
/*   Updated: 2022/10/29 17:21:21 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_rowcount2(char *str, int *i)
{
	if (str[*i] == '\"')
	{
		(*i) += 1;
		while (str[*i] != '\"' && str[*i])
			(*i)++;
	}
	if (str[*i] == '\'')
	{
		(*i) += 1;
		while (str[*i] != '\'' && str[*i])
			(*i)++;
	}
}

static int	ft_rowcount(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] != '\0')
			count += 1;
		while (str[i] != c && str[i] != '\0')
		{
			ft_rowcount2(str, &i);
			i++;
		}
	}
	return (count);
}

void	ft_rowlen2(char *str, int *i, char c)
{
	while (str[*i])
	{
		if (str[*i] == '\"')
		{
			(*i) += 1;
			while (str[*i] != '\"' && str[*i])
				(*i)++;
		}
		if (str[*i] == '\'')
		{
			(*i) += 1;
			while (str[*i] != '\'' && str[*i])
				(*i)++;
		}
		if (str[*i] == c)
			break ;
		(*i)++;
	}
}

static int	ft_rowlen(char *str, char c)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (str[i] == c)
	{
		i++;
		len++;
	}
	ft_rowlen2(str, &i, c);
	return (i - len);
}

char	**ft_smart_split(char *s, char c)
{
	char	**matrix;
	int		count;
	int		len;
	int		row;

	count = ft_rowcount(s, c);
	matrix = (char **) malloc (sizeof(char *) * (count + 1));
	matrix[count] = NULL;
	len = 0;
	row = 0;
	while (row < count)
	{
		len = ft_rowlen(s, c);
		matrix[row] = (char *) malloc (sizeof(char) * (len + 1));
		ft_strlcpy(matrix[row], s, len + 1);
		s += len + 1;
		row++;
	}
	return (matrix);
}
