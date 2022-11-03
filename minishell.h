/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 21:20:23 by ebondi            #+#    #+#             */
/*   Updated: 2022/11/03 15:07:30 by ebondi           ###   ########.fr       */
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
	char	**cmds;
}		t_mini;

int	exit_status;

void	init(t_mini *mini, char **envp);
void	sig_handler(int signal);

char	**ft_env_copy(char **env);
char	*ft_get_env_var(t_mini *mini, char *str);
int		ft_len_matrix(char **matrix);
char	*expand_env_var(t_mini *mini, char *str);
char	*expand_env_var2(t_mini *mini, char *str, int i);
char	*expand_env_var3(char *initial_str, char *var);
int		ft_isspace(int c);
int		confront_env_var(char *env_line, char *str);
char	**ft_export(t_mini *mini);
void	ft_swap(t_mini *mini, int o, int i);
void	ft_free_matrix(char **env);
char	*ft_shlvl_update(char *env);
void	ft_shlvl_increment(char *argv[], t_mini *mini);
char	*ft_shlvl_extractor(t_mini *mini);
void	builtin_unset(t_mini *mini, char **cmd);
char	**builtin_unset2(t_mini *mini, char **env, char *str);
void	builtin_pwd(t_mini *mini);
char	*ft_get_env_value(char **env, char *str);
void	ft_export_insert(t_mini *mini, char **env, char *key, char *value);
void	ft_export_two(t_mini *mini, char *key, char *value, int i);
void	ft_only_export(t_mini *mini);

//command
void	get_command(t_mini *mini);

//syntax check
int		ft_check_quotes(char *str, t_mini *mini);
int		ft_check_pipe(char *str, t_mini *mini);

char	**ft_smart_split(char *s, char c);
void	builtin_exit(t_mini *mini);
void	builtin_env(t_mini *mini);
void	builtin_export(t_mini *mini, char **cmd);

int		ft_ext_cmd(t_mini *mini, char **cmd);
char	*ft_get_path(t_mini *mini);
int		ft_forkamelo_tutto(t_mini *mini, char *path, char **cmd);
void	builtin_cd(t_mini *mini, char **cmd);

#endif