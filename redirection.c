/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:24:09 by atarsi            #+#    #+#             */
/*   Updated: 2022/11/18 19:30:21 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
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
if (!ft_strcmp(cmd[i], "<", 1) && ft_strlen(cmd[i]) == 1)
if (!ft_strcmp(cmd[i], "<<", 2) && ft_strlen(cmd[i]) == 2)
*/

int ft_input_rd(char *str)
{
    int fd;

    ft_putstr_fd("stampa2:", 1);
    ft_putstr_fd(str, 1);
    fd = open(str, O_RDONLY, S_IRWXU);
    if (fd == -1)
    {
        printf("%s:No such file or directory", str); // putstr? in stderr?
        return (-1);
    }
    dup2(fd, 0);
    close(fd);
    free(str);
    return (0);
}

int ft_redirection(t_mini *mini)
{
    int i;
    int j;

    i = 0;
    while (mini->cmds[i])
    {
        j = 0;
        while (mini->cmds[i][j])
        {
            //printf("stampa:%s \n", mini->cmds[i]);
            if (!ft_strncmp(mini->cmds[i] + j, "<", 1) /*&& ft_strlen(mini->cmds[i]) == 1*/)
                ft_input_rd(mini->cmds[i] + j + 1);
            /*else if (!ft_strcmp(cmd[i], "<<", 2) && ft_strlen(cmd[i]) == 2)

            else if (!ft_strcmp(cmd[i], ">", 1) && ft_strlen(cmd[i]) == 1)

            else if (!ft_strcmp(cmd[i], ">>", 2) && ft_strlen(cmd[i]) == 2)*/
            j++;        
        }
        i++;
    }
    return (0);
}