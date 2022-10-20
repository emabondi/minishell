/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:29:28 by ebondi            #+#    #+#             */
/*   Updated: 2022/10/20 20:47:43 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len_matrix(char **matrix)
{
	int i;

	i = 0;
	while (matrix[i])
	{
		i++;
	}
	return (i);
}

char	**ft_env_copy(char **env)
{
	char	**env_copy;
	int		i;

	i = 0;
	env_copy = (char **)malloc(sizeof(char *) * ft_len_matrix(env) + 1);
	while (env[i])
	{
		env_copy[i] = ft_strdup(env[i]);
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

int	execute_commands(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->cmds[i])
	{
		if (mini->cmds[i][0] != '\0' && \
			(!ft_strncmp(mini->cmds[i], "exit", 4) && \
				ft_strlen(mini->cmds[i]) == 4))
			builtin_exit(mini);
		if (!ft_strncmp(mini->cmds[i], "env", 3) &&\
			ft_strlen(mini->cmds[i]) == 3)
			builtin_env(mini);
		if (!ft_strncmp(mini->cmds[i], "export", 6) && ft_strlen(mini->cmds[i]) == 6)
			builtin_export(mini);
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
		if(!execute_commands(mini))
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
