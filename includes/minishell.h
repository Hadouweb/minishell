#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include "libft.h"

typedef	struct 		s_env
{
	char 			*key;
	char 			*value;
	t_list			*lst_value;
}					t_env;

typedef struct		s_app
{
	t_list			*lst_env;
	t_list			*path_node;
	t_list			*param;
	pid_t 			pid;
	char 			**env;
}					t_app;

void	m_set_envp(t_app *app, char **envp);
void	m_debug_content_env(void *content);
void	m_free_lst_envp(t_app *app);
void	m_set_env_from_lst(t_app *app);
void	m_debug_env(char **env);
void	m_error_malloc(char *str);
void	m_free_env_from_lst(t_app *app);
void	m_free_all(t_app *app);
int		m_check_builtin(t_app *app, char *cmd);
void	m_run_cmd(t_app *app, char *cmd);
char 	*m_get_cmd_path(t_app *app, char *cmd);
char 	**m_get_cmd_arg(char *cmd);
void	m_error(char *str, char *file);
void	m_error_access(char *cmd, int code);
void	m_set_cmd(t_app *app, char *cmd);

#endif
