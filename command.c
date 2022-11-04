/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolaiac <ccolaiac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:29:28 by ebondi            #+#    #+#             */
/*   Updated: 2022/11/04 19:14:41 by ccolaiac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_delete_quotes(char	*cmd, char quote)
{
	int		i;
	int		k;
	char	*new;

	i = 0;
	while (cmd[i])
	{
		new = malloc(sizeof(char) * ft_strlen(cmd) - 1);
		k = 0;
		while (cmd[i])
		{
			if (cmd[i] != quote)
			{
				new[k] = cmd[i];
				k++;
			}
			i++;
		}
		new[k] = 0;
	}
	free(cmd);
	return (new);
}

char	*ft_quotes2(char *cmd, int *flag, char quote, int b)
{
	if (*flag == b)
		*flag = 0;
	else
		*flag = b;
	return (ft_delete_quotes(cmd, quote));
}

char	**ft_quotes(char **cmd)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	flag = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '\'' && flag != 2)
			{
				cmd[i] = ft_quotes2(cmd[i], &flag, '\'', 1);
			}
			else if (cmd[i][j] == '\"' && flag != 1)
			{
				cmd[i] = ft_quotes2(cmd[i], &flag, '\"', 2);
			}
			j++;
		}
		i++;
	}
	return (cmd);
}

int	execute_commands(t_mini *mini)
{
	int		i;
	//int		j;
	char	**cmd;

	i = 0;
	while (mini->cmds[i])
	{
		cmd = ft_smart_split(mini->cmds[i], ' ');
		cmd = ft_quotes(cmd);
		if (cmd[0][0] != '\0' && ft_strncmp(cmd[0], "exit", 4) == 0 && \
			ft_strlen (cmd[0]) == 4)
			builtin_exit(mini);
		else if (ft_strncmp(cmd[0], "env", 3) == 0 && \
			ft_strlen(cmd[0]) == 3)
			builtin_env(mini);
		else if (ft_strncmp(cmd[0], "export", 6) == 0 && \
			ft_strlen(cmd[0]) == 6)
			builtin_export(mini, cmd);
		else if (ft_strncmp(cmd[i], "echo", 4) == 0 && \
			ft_strlen(cmd[i]) == 4)
			builtin_echo(cmd);
		else if (ft_strncmp(cmd[i], "cd", 2) == 0 && \
			ft_strlen(cmd[i]) == 2)
			builtin_cd(mini, cmd);
		else if (ft_strncmp(cmd[i], "pwd", 3) == 0 && \
			ft_strlen(cmd[i]) == 3)
			builtin_pwd(mini);
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
