#include "minishell.h"

void	ft_swap(t_mini *mini, int o, int i)
{
	char			*temp;
	int		j;

	temp = NULL;
	j = 0;
	while (j<o-1-i)
	{
		if (ft_strncmp(mini->export[j], mini->export[j+1], ft_strlen(mini->export[j])) > 0)
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

	mini->export = (char **)malloc(sizeof(char *) * ft_len_matrix(mini->env) + 1);

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
