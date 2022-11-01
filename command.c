/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:29:28 by ebondi            #+#    #+#             */
/*   Updated: 2022/10/31 17:49:57 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_commands(t_mini *mini)
{
	int		i;
	//int		j;
	char	**cmd;

	i = 0;
	while (mini->cmds[i])
	{
		cmd = ft_smart_split(mini->cmds[i], ' ');
		if (cmd[0][0] != '\0' && ft_strncmp(cmd[0], "exit", 4) == 0 && \
			ft_strlen (cmd[0]) == 4)
			builtin_exit(mini);
		else if (ft_strncmp(cmd[0], "env", 3) == 0 && \
			ft_strlen(cmd[0]) == 3)
			builtin_env(mini);
		else if (ft_strncmp(cmd[0], "export", 6) == 0 && \
			ft_strlen(cmd[0]) == 6)
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
		else if (ft_strncmp(cmd[0], "unset", 5) == 0 && \
			ft_strlen(cmd[0]) == 5)
			builtin_unset(mini, cmd);
		else
			ft_ext_cmd(mini, cmd);
		//j = -1;
		//while (cmd[++j])
		//	printf("%s\n", cmd[j]);
		ft_free_matrix(cmd);
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
		ft_free_matrix(mini->cmds);
	}
	if (buff == NULL /*|| (buff[0] != '\0' && (!ft_strncmp(buff, "exit", 4) && ft_strlen(buff) == 4))*/)
	{
		// ft_putend_fd("exit", 1);
		mini->exit = 1;
		free(buff);
		return ;
	}
	free(buff);
}
