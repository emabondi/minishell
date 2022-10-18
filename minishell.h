/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 21:20:23 by ebondi            #+#    #+#             */
/*   Updated: 2022/10/18 19:48:00 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <termios.h>

typedef struct s_minishell
{
	int		exit;
	char	**env;
	char	**export;
}		t_mini;

int	exit_status;

void	init(t_mini *mini, char **envp);
void	sig_handler(int signal);
void	get_command(t_mini *mini);
char	**ft_env_copy(char **env);
char	*ft_get_env_var(t_mini *mini, char *str);
int		ft_len_matrix(char **matrix);
void	prova(char *str);
char	*expand_env_var(t_mini *mini, char *str);
char	*expand_env_var2(t_mini *mini, char *str, int i);
char	*expand_env_var3(char *initial_str, char *var);
int		ft_isspace(int c);
int		confront_env_var(char *env_line, char *str);
char	**ft_export(t_mini *mini);
void	ft_swap(t_mini *mini, long long o, long long i);
void	ft_free_matrix(char **env);

//syntax check

void	ft_check_s_quotes(char *str);
void	ft_check_d_quotes(char *str);
void	ft_check_parser(char *str);

#endif