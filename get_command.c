/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:29:28 by ebondi            #+#    #+#             */
/*   Updated: 2022/10/13 12:33:54 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_command(t_mini *mini)
{
	char	*buff;
	int		p;

	p = mini->exit;
	buff = readline("minisburo:");
	if (buff == NULL || (buff[0] != '\0' && (!ft_strncmp(buff, "exit", ft_strlen(buff)))))
	{
		ft_putendl_fd("exit", 1);
		mini->exit = 1;
	}
}