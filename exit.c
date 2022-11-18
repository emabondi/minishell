/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:33:50 by ebondi            #+#    #+#             */
/*   Updated: 2022/11/18 19:22:16 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	builtin_exit2(t_mini *mini, char **cmd)
{
	if (!str_is_digit(cmd[1]))
	{
		ft_putendl_fd("exit", 1);
		ft_putstr_fd("minisburo: exit: ", 2);
		ft_putstr_fd(cmd[1] , 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_status = 255;
		mini->exit = 1;
		return ;
	}
	else
	{
		ft_putendl_fd("exit", 1);
		ft_putstr_fd("minisburo: exit: too many arguments\n", 2);
		exit_status = 1;
		return ;
	}
}

void	builtin_exit(t_mini *mini, char **cmd)
{
	int	x;

	if (cmd[1] == NULL)
	{
		ft_putendl_fd("exit", 1);
		mini->exit = 1;
		return ;
	}
	else if (str_is_digit(cmd[1]) && cmd[2] == NULL)
	{
		x = ft_atoi(cmd[1]);
		if (x > 255)
			exit_status = (x % 256);
		else
			exit_status = x;
		ft_putendl_fd("exit", 1);
		mini->exit = 1;
		return ;
	}
	else
		builtin_exit2(mini, cmd);
}
