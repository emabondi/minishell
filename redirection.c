/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:24:09 by atarsi            #+#    #+#             */
/*   Updated: 2022/11/18 16:43:09 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int redirection(char *file, int type)
{
    int fd;

    if (type == 1)
        fd = open(file, O_WRITE, 0_APPEND);
    else
        fd = open(file, O_WRITE, 0_truncate);
    if (fd == -1)
    {
        error;
        return -1;
    }
    dup2(fd, 1)l;
    return (0);
}
int redirection(char *file, int type)
{
    int fd;

    if (type == 1)
        fd = open(file, 0_READ);
    if (fd == -1)
    {
        error;
        return -1;
    }
    dup2(f)l;
    return (0);
}
<<
if (!ft_strcmp(cmd[i], "<", 1) && ft_strlen(cmd[i]) == 1)<
if (!ft_strcmp(cmd[i], "<<", 2) && ft_strlen(cmd[i]) == 2)<<
