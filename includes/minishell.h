/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 11:47:53 by nle-bret          #+#    #+#             */
/*   Updated: 2016/11/04 11:48:11 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include "libft.h"
# include <signal.h>

# define ECHO_OPT_N 0x01

# define ENV_OPT_I 0x01

# define CD_OPT_L 0x01
# define CD_OPT_P 0x02

int		g_pid;

typedef	struct		s_env
{
	char			*key;
	char			*value;
	t_list			*lst_value;
}					t_env;

typedef struct		s_app
{
	t_list			*lst_env;
	t_list			*path_node;
	t_list			*param;
	t_list			*echo_arg;
	t_list			*env_arg;
	t_list			*cd_arg;
	t_list			*lst_cmd;
	pid_t			pid;
	char			**env;
	unsigned char	echo_flag;
	unsigned char	env_flag;
	unsigned char	cd_flag;
}					t_app;

void	m_set_envp(t_app *app, char **envp);
void	m_debug_content_env(void *content);
void	m_free_lst_envp(t_app *app);
void	m_set_env_from_lst(t_app *app);
void	m_debug_env(char **env);
void	m_error_malloc(char *str);
void	m_free_all(t_app *app);
int		m_check_builtin(t_app *app, char *cmd);
void	m_run_cmd(t_app *app, char **cmd);
char	*m_get_cmd_path(t_app *app, char *cmd);
char	**m_get_cmd_arg(t_app *app);
void	m_error(char *str, char *file);
void	m_error_access(char *cmd, int code);
void	m_set_cmd(t_app *app, char *cmd);
void	m_exec_cmd(t_app *app, char *path, char **cmd_arg, char **env);
void	m_run_echo(t_app *app, char *cmd);
void	m_check_flag_echo(t_app *app);
void	m_free_char_lst(t_list **lst);
int		m_set_special_character(char *new_str, char *str);
void	m_split_cmd_echo(t_app *app, char *cmd);
char	*m_get_sub_word(char **str);
void	m_split_cmd_with_del_quote(t_app *app, char *cmd);
void	m_set_env_var(t_app *app, char **cmd);
void	m_run_env(t_app *app, char *cmd);
void	m_run_setenv(t_app *app, char *cmd);
char 	*m_get_key_param(t_app *app);
char 	*m_get_value_param(t_app *app);
void	m_error2(char *str);
void	m_run_unsetenv(t_app *app, char *cmd);
void	m_run_cd(t_app *app, char *cmd);
char 	*m_get_value_env_by_key(t_app *app, char *key);
void	m_error3(char *str1, char *str2, char *str3);

#endif
