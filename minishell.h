/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 21:20:23 by ebondi            #+#    #+#             */
/*   Updated: 2022/12/10 21:22:17 by ebondi           ###   ########.fr       */
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
# include <dirent.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_minishell
{
	int		exit;
	char	**env;
	char	**export;
	char	**cmds;
}		t_mini;

int	g_exit_status;

void	init(t_mini *mini, char **envp);
void	sig_handler(int signal);
void	sig_handler_father(int signal);

char	**ft_env_copy(char **env);
char	*ft_get_env_var(t_mini *mini, char *str);
int		ft_len_matrix(char **matrix);

char	*expand_env_var(t_mini *mini, char *str);
char	*expand_env_var2(t_mini *mini, char *str, int i);
char	*expand_env_var3(char *initial_str, char *var);
char	*ft_whats_exit_status(char *str, int i);
void	expand_env_var_helper(char *str, int *i);

int		ft_isspace(int c);
int		ft_parse_error(int token);
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
void	builtin_echo(char **cmd);

//command
void	get_command(t_mini *mini);
void	execute_commands(t_mini *mini, char *cmd_i);
void	execute_commands2(t_mini *mini, char **cmd);

//syntax check
int		ft_check_quotes(char *str);
int		ft_check_pipe(char *str);
int		ft_check_pipe2(char *str);
int		ft_isalnum_mod(char **cmd);
int		ft_check_redi(char *str);

//builtin
char	**ft_smart_split(char *s, char c);
void	builtin_exit(t_mini *mini, char **cmd);
void	builtin_exit2(t_mini *mini, char **cmd);
int		str_is_digit(char *str);
void	builtin_env(t_mini *mini);
void	builtin_export(t_mini *mini, char **cmd);
void	builtin_cd(t_mini *mini, char **cmd);

//external_command
void	ft_ext_cmd(t_mini *mini, char **cmd);
int		ft_forkamelo_tutto(t_mini *mini, char *path, char **cmd);
int		ft_execve_error(char *path);

//pipe
int		ft_pipe(t_mini *mini);
void	ft_every_pipe(t_mini *mini, char *cmd_i, int *pid, int *tmp);
void	ft_last_pipe(t_mini *mini, char *cmd_i, int *pid, int *tmp);
void	ft_last_pipe_help(t_mini *mini, char *cmd_i, int *tmp);

//quotes
char	**ft_quotes(char **cmd);
char	*ft_quotes2(char *cmd, int *flag, char quote, int b);
char	*ft_delete_quotes(char	*cmd, char quote);

//redirection
char	*ft_redirection(char *cmd);
char	*ft_redirection2(char *cmd, int start);
char	*ft_rd_arg(char *cmd, int *j, int *z);
char	*ft_redirection2(char *cmd, int start);
char	*ft_redirection(char *cmd);
char	*ft_cut_sub(char *src, int start, int start2);
int		ft_input_rd(char *str);
void	ft_heredoc(char *sub);
int		ft_output_rd(char *str, int type);

#endif