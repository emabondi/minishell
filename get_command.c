/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:29:28 by ebondi            #+#    #+#             */
/*   Updated: 2022/10/15 19:46:03 by ebondi           ###   ########.fr       */
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

void	get_command(t_mini *mini)
{
	char	*buff;
	int		p;
	int		i;

	i = 0;
	p = mini->exit;
	buff = readline("minisburo:");
	if (buff != NULL && ft_strlen(buff) > 0)
	{
		ft_check_parser(buff);
		add_history(buff);
		buff = expand_env_var(mini, buff);
		printf("%s\n", buff);
	}
	if (buff == NULL || (buff[0] != '\0' && (!ft_strncmp(buff, "exit", 4) && ft_strlen(buff) == 4)))
	{
		ft_putendl_fd("exit", 1);
		mini->exit = 1;
		free(buff);
		return ;
	}
	if (!ft_strncmp(buff, "env", 3) && ft_strlen(buff) == 3)
	{
		while (mini->env[i])
		{
			printf("%s", mini->env[i]);
			i++;
			printf("\n");
		}
	}
	free(buff);
}
