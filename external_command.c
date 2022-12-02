/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:36:59 by atarsi            #+#    #+#             */
/*   Updated: 2022/12/02 15:04:02 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execve_error(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minisburo: ", 2);
	ft_putstr_fd(path, 2);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", 2);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", 2);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", 2);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", 2);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = 127;
	else
		ret = 126;
	if (folder)
		closedir(folder);
	if (fd > 0)
		close (fd);
	return (ret);
}

int	ft_forkamelo_tutto(t_mini *mini, char *path, char **cmd)
{
	int		ret;
	pid_t	pid;

	ret = 1;
	pid = fork();
	// cmd[1] = NULL;
	if (pid == 0)
	{
		if (ft_strchr(path, '/') != NULL)
			execve(path, cmd, mini->env);
		ret = ft_execve_error(path);
		exit (ret);
	}	
	else
	{
		waitpid(pid, &ret, 0);
		if (WIFEXITED(ret))
			exit_status = WEXITSTATUS(ret);
	}
	return (ret);
}

char	*ft_get_path(t_mini *mini)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], "PATH=", 5) == 0)
			path = ft_strdup(ft_strchr(mini->env[i], '=') + 1);
		i++;
	}
	return (path);
}

int	ft_check_access(char **pos_path, char **cmd, int *i)
{
	char	*temp;

	while (pos_path[*i])
	{
		temp = ft_strjoin(pos_path[*i], "/");
		free (pos_path[*i]);
		pos_path[*i] = ft_strjoin(temp, cmd[0]);
		if (access(pos_path[*i], R_OK) == 0)
		{
			free (temp);
			return (1);
		}
		(*i)++;
		free (temp);
	}
	return (0);
}

void	ft_ext_cmd(t_mini *mini, char **cmd)
{
	char	*path;
	char	**pos_path;
	int		i;

	path = ft_get_path(mini);
	if (path == NULL)
	{
		ft_putstr_fd("minisburo: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		return ;
	}
	pos_path = ft_split(path, ':');
	i = 0;
	if (ft_check_access(pos_path, cmd, &i))
		ft_forkamelo_tutto(mini, pos_path[i], cmd);
	else
		ft_forkamelo_tutto(mini, cmd[0], cmd);
	free (path);
	ft_free_matrix(pos_path);
}
