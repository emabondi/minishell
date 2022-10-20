/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:24:38 by ebondi            #+#    #+#             */
/*   Updated: 2022/10/20 20:44:53 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(t_mini *mini)
{
	ft_putendl_fd("exit", 1);
	mini->exit = 1;
	return ;
}

void	builtin_env(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->env[i])
	{
		printf("%s", mini->env[i]);
		i++;
		printf("\n");
	}
}

void	builtin_export(t_mini *mini)
{
	int	i;

	i = 0;
	mini->export = ft_export(mini);
	while (mini->env[i])
	{
		printf("declare -x %s", mini->export[i]);
		i++;
		printf("\n");
	}
	ft_free_matrix(mini->export);
}
