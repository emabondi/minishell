/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:30:10 by atarsi            #+#    #+#             */
/*   Updated: 2022/10/27 08:32:04 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_pipe(char *str, t_mini *mini)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '|')
	{
		free(str);
		ft_putstr_fd("minisburo: syntax error\n", 0);
		mini->exit = 1;
		exit_status = 258;
		return (0);
	}
	return (1);
}	

int	ft_check_quotes(char *str, t_mini *mini)
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
		ft_putstr_fd("minisburo: syntax error\n", 0);
		mini->exit = 1;
		exit_status = 258;
		return (0);
	}
	return (1);
}
