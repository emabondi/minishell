/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:53:47 by atarsi            #+#    #+#             */
/*   Updated: 2022/11/08 17:51:27 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pipe()
{
    int     fd[100];
    pid_t   pid;
    char    buf;
    
    if (pipe(fd) == -1)
    {
        perror();
        exit(0);
    }
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(0);
    }
    else if (pid == 0)
    {
        close (fd[1]);
        while (read(fd[0], buf, 1) > 0)
            write (1, buf, 1);
        close(fd[0]);
        exit (0);
    }
    else
        close (fd[0]);
        write (1, "ciao\n", 5);
        close (fd[1]);
        wait(NULL);
        exit(0);
}