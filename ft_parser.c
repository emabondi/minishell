/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:30:10 by atarsi            #+#    #+#             */
/*   Updated: 2022/12/01 20:15:01 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_pipe2(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
		{
			i++;
			while (ft_isspace(str[i]))
				i++;
			if (str[i] == '|')
				return (0);
		}
		i++;
	}
	return (1);
}

int	ft_check_pipe(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '|' || !ft_check_pipe2(str))
	{
		free(str);
		ft_putstr_fd("minisburo: syntax error near unexpected token `|'\n", 2);
		exit_status = 258;
		return (0);
	}
	return (1);
}	

int	ft_check_quotes(char *str)
{
	int	i;
	int	dq;
	int	q;

	i = 0;
	dq = 0;
	q = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && dq % 2 == 0)
			q++;
		if (str[i] == '\"' && q % 2 == 0)
			dq++;
		i++;
	}
	if (dq % 2 != 0 || q % 2 != 0)
	{
		free(str);
		if (dq % 2 != 0)
			ft_putstr_fd("minisburo: syntax error \
				near unexpected token `\"'\n", 2);
		else
			ft_putstr_fd("minisburo: syntax error \
				near unexpected token `\''\n", 2);
		exit_status = 258;
		return (0);
	}
	return (1);
}
