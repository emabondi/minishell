/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:05:28 by ebondi            #+#    #+#             */
/*   Updated: 2022/10/11 19:33:31 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	(void)signal;
	return ;
}

void	init(t_mini *mini)
{
	mini->exit = 0;
}

int	main(void)
{
	t_mini		mini;

	init(&mini);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (mini.exit == 0)
	{
		get_command(&mini);
	}
	return (0);
}
