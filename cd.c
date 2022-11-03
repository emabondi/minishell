#include "minishell.h"

void	ft_update_env(t_mini *mini)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = ft_strdup(ft_get_env_value(mini->env, "PWD"));
	while (mini->env[i])
	{
		if (!ft_strncmp(mini->env[i], "PWD=", 4))
		{
			free(mini->env[i]);
			tmp2 = getcwd(NULL, 0);
			mini->env[i] = ft_strjoin("PWD=", tmp2);
			free(tmp2);
		}
		if (!ft_strncmp(mini->env[i], "OLDPWD=", 7))
		{
			free(mini->env[i]);
			mini->env[i] = ft_strjoin("OLDPWD=", tmp);
		}
		i++;
	}
	free(tmp);
}

char	*ft_get_dir(t_mini *mini, char *cmd)
{
	char	*dir;
	char	*tmp;

	dir = NULL;
	if (cmd[0] == '-')
		dir = ft_strdup(ft_get_env_value(mini->env, "OLDPWD"));
	else if (cmd[0] == '~')
	{
		tmp = ft_strjoin(ft_get_env_value(mini->env, "HOME"), "/");
		dir = ft_strjoin(tmp, cmd + 1);
		free(tmp);
	}
	else if (cmd[0] == '/')
		dir = ft_strdup(cmd);
	else
	{
		tmp = ft_strjoin("/", cmd);
		dir = ft_strjoin(ft_get_env_value(mini->env, "PWD"), tmp);
		free(tmp);
	}
	return (dir);
}

void	builtin_cd(t_mini *mini, char **cmd)
{
	char	*dir;

	if (!cmd[1])
	{
		chdir(ft_get_env_value(mini->env, "HOME"));
		ft_update_env(mini);
		exit_status = 0;
	}
	else
	{
		dir = ft_get_dir(mini, cmd[1]);
		if (!dir)
			chdir(ft_get_env_value(mini->env, "HOME"));
		else if (chdir(dir))
		{
			exit_status = 1;
			ft_putstr_fd("cd: no such file or directory: ", 2);
			ft_putendl_fd(cmd[1], 2);
		}
		else
			ft_update_env(mini);
		free (dir);
	}
}