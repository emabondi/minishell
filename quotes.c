/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:35:08 by atarsi            #+#    #+#             */
/*   Updated: 2022/12/05 16:59:40 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//char	*ft_delete_quotes(char	*cmd, char quote)
//{
//	int		i;
//	int		k;
//	char	*new;

//	i = 0;
//	while (cmd[i])
//	{
//		new = malloc(sizeof(char) * ft_strlen(cmd) - 1);
//		k = 0;
//		while (cmd[i])
//		{
//			if (cmd[i] != quote)
//			{
//				new[k] = cmd[i];
//				k++;
//			}
//			i++;
//		}
//		new[k] = 0;
//	}
//	free(cmd);
//	return (new);
//}

//char	*ft_quotes2(char *cmd, int *flag, char quote, int b)
//{
//	if (*flag == b)
//		*flag = 0;
//	else
//		*flag = b;
//	return (ft_delete_quotes(cmd, quote));
//}

//char	**ft_quotes(char **cmd)
//{
//	int		i;
//	int		j;
//	int		flag;

//	i = 0;
//	flag = 0;
//	while (cmd[i])
//	{
//		j = 0;
//		while (cmd[i][j])
//		{
//			if (cmd[i][j] == '\'' && flag != 2)
//			{
//				cmd[i] = ft_quotes2(cmd[i], &flag, '\'', 1);
//			}
//			else if (cmd[i][j] == '\"' && flag != 1)
//			{
//				cmd[i] = ft_quotes2(cmd[i], &flag, '\"', 2);
//			}
//			j++;
//		}
//		i++;
//	}
//	return (cmd);
//}

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