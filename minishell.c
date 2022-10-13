/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:05:28 by ebondi            #+#    #+#             */
/*   Updated: 2022/10/13 19:52:21 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		exit_status = 1;
	}
	else if (signal == SIGQUIT){
		exit_status = 127;
		//exit(1);
	}
	return ;
}

void	init_signals(int startorend)
{
	struct termios			tty_attrs_new;
	static struct termios	tty_attrs_old;

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

void	init(t_mini *mini, char **env)
{
	mini->exit = 0;
	mini->env = ft_env_copy(env);
	init_signals(0);
}

void	ft_free_matrix(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

int	main(int argc, char *argv[], char **env)
{
	t_mini		mini;

	(void)argc;
	(void)argv;
	init(&mini, env);
	while (mini.exit == 0)
	{
		get_command(&mini);
	}
	init_signals(1);
	//printf("%s", ft_get_env_var(&mini, "$ciao"));
	return (exit_status);
}
