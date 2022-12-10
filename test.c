/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolaiac <ccolaiac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 17:32:42 by ccolaiac          #+#    #+#             */
/*   Updated: 2022/12/10 17:32:47 by ccolaiac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

int	main(void)
{
	ft_putendl_fd("env", 1);
	sleep (1);
	ft_putendl_fd("export", 1);
	sleep (1);
	ft_putendl_fd("$HOME", 1);
	sleep (1);
	ft_putendl_fd(" a$USERv", 1);
	sleep (1);
	ft_putendl_fd("a$USER$$", 1);
	sleep (1);
}
