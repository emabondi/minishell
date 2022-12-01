/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:13:38 by ebondi            #+#    #+#             */
/*   Updated: 2022/12/01 20:13:38 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_error(char *str, int token)
{
	free(str);
	ft_putstr_fd("minisburo: syntax error near unexpected token `", 2);
	write (2, &token, 1);
	ft_putstr_fd("'\n", 2);
	exit_status = 258;
	return (0);
}

int	ft_check_redi2(char *str, int *i, int type)
{
	if (str[*i + 1] != '\0' && str[*i] == type && str[*i + 1] == type)
		(*i) += 2;
	else if (str[*i] == type)
		(*i) += 1;
	else
		return (ft_parse_error(str, type));
	while (str[*i] == ' ')
		(*i)++;
	if (str[*i] == '\0' || !ft_isalnum(str[*i]))
		return (ft_parse_error(str, type));
	return (1);
}

int	ft_check_redi(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			if (!ft_check_redi2(str, &i, '<'))
				return (0);
		}
		else if (str[i] == '>')
		{
			if (!ft_check_redi2(str, &i, '>'))
				return (0);
		}
		i++;
	}
	return (1);
}