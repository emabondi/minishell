
#include "minishell.h"

char	**ft_env_copy(char **env)
{
	int		i;
	char **copy;

	i = 0;
	copy = (char **)malloc(sizeof(char *) * ft_len_matrix(env) + 1);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "SHLVL=", 6))
			copy[i] = ft_shlvl_update(env[i]);
		else
			copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char	*ft_shlvl_update(char *env)
{
	int		i;
	char	*d;
	char	*lvl;

	lvl = ft_substr(env, 6, ft_strlen(env));
	i = ft_atoi(lvl);
	free(lvl);
	lvl = ft_itoa(i + 1);
	d = ft_strjoin("SHLVL=", lvl);
	free(lvl);
	return (d);
}

void	ft_swap(t_mini *mini, long long o, long long i)
{
	char	*temp;
	int		j;

	temp = NULL;
	j = 0;
	while (j < o - 1 - i)
	{
		if (ft_strncmp (mini->export[j], \
			mini->export[j+1], ft_strlen (mini->export[j])) > 0)
		{
			temp = mini->export[j];
			mini->export[j] = mini->export[j+1];
			mini->export[j+1] = temp;
		}
	j++;
	}
}

char	**ft_export(t_mini *mini)
{
	int		i;
	int		o;

	i = 0;
	o = 0;
	mini->export = (char **) malloc \
		(sizeof(char *) * ft_len_matrix(mini->env) + 1);
	while (mini->env[i])
	{
		mini->export[i] = ft_strdup(mini->env[i]);
		i++;
		o++;
	}
	mini->export[i] = NULL;
	i = 0;
	while (i < o)
	{
		ft_swap(mini, o, i);
		i++;
	}
	return (mini->export);
}
