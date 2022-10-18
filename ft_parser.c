/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:30:10 by atarsi            #+#    #+#             */
/*   Updated: 2022/10/18 20:09:40 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_parser(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '|')
		ft_putstr_fd("minisburo: syntax error\n", 0);
}	

void	ft_check_s_quotes(char *str)
{
	int	i;
	int	dq;
	int	q;

	i = 0;
	dq = 0;
	q = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '\"' && q % 2 == 0)
			dq++;
		if (str[i] == '\'' && dq % 2 == 0)
			q++;
		i++;
	}
	if (q % 2 != 0)
		ft_putstr_fd("minisburo: syntax error\n", 0);
}

void	ft_check_d_quotes(char *str)
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
	if (dq % 2 != 0)
		ft_putstr_fd("minisburo: syntax error\n", 0);
}
