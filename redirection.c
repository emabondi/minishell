/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolaiac <ccolaiac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:24:09 by atarsi            #+#    #+#             */
/*   Updated: 2022/11/21 14:11:10 by ccolaiac         ###   ########.fr       */
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

int	ft_input_rd(char *str)
{
	int	fd;

	ft_putstr_fd("stampa2:", 1);
	ft_putstr_fd(str, 1);
	fd = open(str, O_RDONLY, S_IRWXU);
	if (fd == -1)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	dup2(fd, 0);
	close(fd);
	return (0);
}

void	ft_redirection2(char *cmd, int start)
{
	int		j;
	int		z;
	char	*sub;

	j = start;
	while (cmd[j] == '<' || cmd[j] == '>')
		j++;
	while (cmd[j] == ' ')
		j++;
	z = 0;
	if (cmd[j] == '\"')
	{
		j++;
		while (cmd[z + j] != '\"')
			z++;
	}
	else if (cmd[j] == '\'')
	{
		j++;
		while (cmd[z + j] != '\'')
			z++;
	}
	else
		while (cmd[z + j] && cmd[z + j] != ' ' )
			z++;
	sub = ft_substr(cmd, j, z);
	printf("sub:%shh\n", sub);
	//printf("stampa:%s \n", mini->cmds[i]);
	if (cmd[start] == '<' && (cmd[start + 1] != '\0' && cmd[start + 1] != '<'))
		ft_input_rd(sub);
    /*else if (!ft_strcmp(cmd[i], "<<", 2) && ft_strlen(cmd[i]) == 2)
    else if (!ft_strcmp(cmd[i], ">", 1) && ft_strlen(cmd[i]) == 1)
    else if (!ft_strcmp(cmd[i], ">>", 2) && ft_strlen(cmd[i]) == 2)*/
	// free (sub);
	
}

int ft_redirection(char *cmd)
{
    int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\"')
				i++;
			i++;
		}
		if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'')
				i++;
			i++;
		}
		if (cmd[i] == '<' || cmd[i] == '>')
			ft_redirection2(cmd, i);  
    	i++;
    }
    return (0);
}