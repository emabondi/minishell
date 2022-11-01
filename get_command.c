/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:29:28 by ebondi            #+#    #+#             */
/*   Updated: 2022/10/15 21:11:57 by ebondi           ###   ########.fr       */
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
	if (!ft_strncmp(buff, "export", 6) && ft_strlen(buff) == 6)
	{
		mini->export = ft_export(mini);
		while (mini->env[i])
		{
			printf("declare -x %s", mini->export[i]);
			i++;
			printf("\n");
		}
		ft_free_matrix(mini->export);
	}
	free(buff);
}
