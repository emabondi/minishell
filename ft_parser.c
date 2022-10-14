/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:30:10 by atarsi            #+#    #+#             */
/*   Updated: 2022/10/14 18:08:18 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_parser(char *str)
{
	int	i;
	
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[0] == '|')
		ft_putstr_fd("synt_error", 0);
}




