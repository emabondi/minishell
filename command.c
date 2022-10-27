/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:29:28 by ebondi            #+#    #+#             */
/*   Updated: 2022/10/27 11:37:39 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_commands(t_mini *mini)
{
	int		i;
	char	**cmd;

	i = 0;
	while (mini->cmds[i])
	{
		cmd = ft_smart_split(mini->cmds[i], ' ');
		if (cmd[i] != '\0' && ft_strncmp(cmd[i], "exit", 4) == 0 && \
			ft_strlen (cmd[i]) == 4)
			builtin_exit(mini);
		else if (ft_strncmp(cmd[i], "env", 3) == 0 && \
			ft_strlen(cmd[i]) == 3)
			builtin_env(mini);
		else if (ft_strncmp(cmd[i], "export", 6) == 0 && \
			ft_strlen(cmd[i]) == 6)
			builtin_export(mini);
		//else if (ft_strncmp(cmd[i], "echo", 4) == 0 && \
		//	ft_strlen(cmd[i]) == 4)
		//	builtin_echo(mini);
		//else if (ft_strncmp(cmd[i], "cd", 2) == 0 && \
		//	ft_strlen(cmd[i]) == 2)
		//	builtin_cd(mini);
		//else if (ft_strncmp(cmd[i], "pwd", 3) == 0 && \
		//	ft_strlen(cmd[i]) == 3)
		//	builtin_cd(mini);
		//else if (ft_strncmp(cmd[i], "unset", 5) == 0 && \
		//	ft_strlen(cmd[i]) == 5)
		//	builtin_unset(mini);
		//else
			exit_status = ft_ext_cmd(cmd, mini);
			i++;
	}
	return (1);
}

void	get_command(t_mini *mini)
{
	char	*buff;
	int		p;
	int		i;

	i = -1;
	p = mini->exit;
	buff = readline("minisburo:");
	if (buff != NULL && ft_strlen(buff) > 0)
	{
		if (!ft_check_pipe(buff, mini) || !ft_check_quotes(buff, mini))
			return ;
		add_history(buff);
		buff = expand_env_var(mini, buff);
		mini->cmds = ft_smart_split(buff, '|');
		if (!execute_commands(mini))
			return ;
		while (mini->cmds[++i] != NULL)
			printf("%s\n", mini->cmds[i]);
	}
	if (buff == NULL /*|| (buff[0] != '\0' && (!ft_strncmp(buff, "exit", 4) && ft_strlen(buff) == 4))*/)
	{
		ft_putendl_fd("exit", 1);
		mini->exit = 1;
		free(buff);
		return ;
	}
	free(buff);
}
