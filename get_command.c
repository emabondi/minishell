/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:29:28 by ebondi            #+#    #+#             */
/*   Updated: 2022/10/12 16:01:30 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_command(t_mini *mini)
{
	char	*buff;
	int		p;

	p = mini->exit;
	buff = readline("minisburo:");
	if (buff && (!ft_strncmp(buff, "exit", ft_strlen(buff))))
	{
		ft_putendl_fd("exit", 1);
		mini->exit = 1;
	}
 
}