/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolaiac <ccolaiac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:00:12 by ccolaiac          #+#    #+#             */
/*   Updated: 2022/12/10 18:18:13 by ccolaiac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_rd_arg(char *cmd, int *j, int *z)
{
	char	*sub;

	while (cmd[*j] == '<' || cmd[*j] == '>' || cmd[*j] == ' ')
		(*j)++;
	if (cmd[*j] == '\"')
	{
		(*j)++;
		while (cmd[*z + *j] != '\"')
			(*z)++;
		sub = ft_substr(cmd, *j, (*z)++);
	}
	else if (cmd[*j] == '\'')
	{
		(*j)++;
		while (cmd[*z + *j] != '\'')
			(*z)++;
		sub = ft_substr(cmd, *j, (*z)++);
	}
	else
	{
		while (cmd[*z + *j] && cmd[*z + *j] != ' ' )
			(*z)++;
		sub = ft_substr(cmd, *j, *z);
	}
	return (sub);
}

char	*ft_redirection2(char *cmd, int start)
{
	int		j;
	int		z;
	char	*sub;
	char	*new_cmd;

	j = start;
	z = 0;
	sub = ft_rd_arg(cmd, &j, &z);
	new_cmd = ft_cut_sub(cmd, start, j + z);
	if (cmd[start] == '<' && (cmd[start + 1] != '\0' && cmd[start + 1] != '<'))
		ft_input_rd(sub);
	else if ((cmd[start] == '<' && (cmd[start + 1] != '\0' && \
			cmd[start + 1] == '<')))
		ft_heredoc(sub);
	else if (cmd[start] == '>' && (cmd[start + 1] != '\0' && \
			cmd[start + 1] != '>'))
		ft_output_rd(sub, 0);
	else if (cmd[start] == '>' && (cmd[start + 1] != '\0' && \
			cmd[start + 1] == '>'))
		ft_output_rd(sub, 1);
	free (sub);
	free (cmd);
	return (new_cmd);
}

void	ft_redirection_help(char *new_cmd, int i)
{
	while (new_cmd[i])
	{
		if (new_cmd[i] == '\"')
		{
			i++;
			while (new_cmd[i] != '\"')
				i++;
			i++;
		}
		if (new_cmd[i] == '\'')
		{
			i++;
			while (new_cmd[i] != '\'')
				i++;
			i++;
		}
		if (new_cmd[i] == '<' || new_cmd[i] == '>')
			new_cmd = ft_redirection2(new_cmd, i);
		else
			i++;
	}
}

char	*ft_redirection(char *cmd)
{
	int		i;
	char	*new_cmd;

	i = 0;
	new_cmd = ft_strdup(cmd);
	ft_redirection_help(new_cmd, i);
	free (cmd);
	return (new_cmd);
}
