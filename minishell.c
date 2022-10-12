/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:05:28 by ebondi            #+#    #+#             */
/*   Updated: 2022/10/12 21:48:08 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sig_handler(int signal)
{
	ft_putendl_fd("sono stornzo1", 0);
	if (signal == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		exit_status = 1;
	}
	else if (signal == SIGQUIT){
		exit(1);
		ft_putendl_fd("sono stornzo", 1);
		}
	return ;
}

void init_signals(int startorend)
{
	struct termios			tty_attrs_new;
	static struct termios	tty_attrs_old;

	(void) startorend;
	if (startorend == 0)
	{
		tcgetattr(STDIN_FILENO, &tty_attrs_old);
		tty_attrs_new = tty_attrs_old;
		tty_attrs_new.c_lflag &= ~(ECHOCTL);
		tcsetattr(STDIN_FILENO, TCSANOW, &tty_attrs_new);
		signal(SIGQUIT, sig_handler);
		signal(SIGINT, sig_handler);
	}
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &tty_attrs_old);
}

void	init(t_mini *mini)
{
	mini->exit = 0;
	init_signals(0);
}

int	main(void)
{
	t_mini		mini;

	init(&mini);
	while (mini.exit == 0)
	{
		get_command(&mini);
	}
	init_signals(1);
	return (exit_status);
}
