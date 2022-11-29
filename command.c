/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:29:28 by ebondi            #+#    #+#             */
/*   Updated: 2022/11/29 12:17:20 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_commands(t_mini *mini, char *cmd_i)
{
	char	**cmd;

	cmd = ft_smart_split(cmd_i, ' ');
	cmd = ft_quotes(cmd);
	if (cmd[0] == NULL)
		return (0);
	else if (cmd[0][0] != '\0' && ft_strncmp(cmd[0], "exit", 4) == 0 && \
		ft_strlen (cmd[0]) == 4)
		builtin_exit(mini, cmd);
	else if (ft_strncmp(cmd[0], "env\n", 4) == 0 && \
		ft_strlen(cmd[0]) == 3)
		builtin_env(mini);
	else if (ft_strncmp(cmd[0], "export", 6) == 0 && \
		ft_strlen(cmd[0]) == 6)
		builtin_export(mini, cmd);
	else if (ft_strncmp(cmd[0], "echo", 4) == 0 && \
		ft_strlen(cmd[0]) == 4)
		builtin_echo(cmd);
	else if (ft_strncmp(cmd[0], "cd", 2) == 0 && \
		ft_strlen(cmd[0]) == 2)
		builtin_cd(mini, cmd);
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0 && \
		ft_strlen(cmd[0]) == 3)
		builtin_pwd(mini);
	else if (ft_strncmp(cmd[0], "unset", 5) == 0 && \
		ft_strlen(cmd[0]) == 5)
		builtin_unset(mini, cmd);
	else
		ft_ext_cmd(mini, cmd);
	ft_free_matrix(cmd);
	return (0);
}

void	get_command(t_mini *mini)
{
	char	*buff;
	//char	**cmd;
	int		std_in_out[2];

	buff = readline("minisburo:");
	if (buff == NULL /*|| (buff[0] != '\0' && (!ft_strncmp(buff, "exit", 4) && ft_strlen(buff) == 4))*/)
	{
		ft_putstr_fd("\e[A\e[K", 1);
		ft_putstr_fd("minisburo: exit\n", 1);
		mini->exit = 1;
		free(buff);
		return ;
	}
	if (buff != NULL && ft_strlen(buff) > 0)
	{
		add_history(buff);
		if (!ft_check_pipe(buff) || !ft_check_quotes(buff))
			return ;
		buff = expand_env_var(mini, buff);
		mini->cmds = ft_smart_split(buff, '|');
		//printf("%s", mini->cmds[0]);
		free(buff);
		if (mini->cmds[1] == NULL)
		{
			std_in_out[0] = dup(0);
			std_in_out[1] = dup(1);
			mini->cmds[0] = ft_redirection(mini->cmds[0]);
			//ft_putstr_fd(mini->cmds[0], 1);
			//cmd = ft_smart_split(mini->cmds[0], ' '); // magari sistemare
			//printf("%s\n %s\n %s\n", cmd[0], cmd[1], cmd[2]);
			//cmd = ft_quotes(cmd);
			//printf("%s\n %s\n %s\n", cmd[0], cmd[1], cmd[2]);
			execute_commands(mini, mini->cmds[0]);
			dup2(std_in_out[0], 0);
			dup2(std_in_out[1], 1);
			//ft_free_matrix(cmd);
		}
		else
			ft_pipe(mini);
		ft_free_matrix(mini->cmds);
	}
}
