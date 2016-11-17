/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_run_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 11:54:31 by nle-bret          #+#    #+#             */
/*   Updated: 2016/11/04 11:54:56 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		m_check_access(char *full_path)
{
	if (access(full_path, X_OK) == -1 && access(full_path, F_OK) == 0)
		return (-1);
	else if (access(full_path, X_OK | F_OK) == 0)
		return (0);
	return (-10);
}

char	*m_get_cmd_path(t_app *app, char *cmd)
{
	char	*full_path;
	t_list	*l;
	int		check_access;
	int		cmp_access;

	l = NULL;
	check_access = -100;
	m_set_path_node(app);
	if (app->path_node != NULL)
		l = ((t_env *)app->path_node->content)->lst_value;
	if (cmd && (cmd[0] == '/' || cmd[0] == '.'))
		return (ft_strdup(cmd));
	while (l)
	{
		full_path = ft_strjoin_free_s1(ft_strjoin((char*)l->content, "/"), cmd);
		cmp_access = m_check_access(full_path);
		check_access = (cmp_access > check_access) ? cmp_access : check_access;
		if (check_access == 0)
			return (full_path);
		ft_strdel(&full_path);
		l = l->next;
	}
	m_error_access(cmd, check_access);
	return (NULL);
}

char	**m_get_cmd_arg(t_app *app)
{
	t_list	*l;
	char	**cmd_arg;

	l = app->param;
	cmd_arg = (char**)ft_lsttotab(l);
	return (cmd_arg);
}

void	m_exec_cmd(t_app *app, char *cmd_bin, char **cmd_arg, char **env)
{
	int		val;

	app->pid = fork();
	g_pid = app->pid;
	if (app->pid > 0)
	{
		wait(&app->pid);
		m_set_env_value_by_key(&app->lst_env, "_", cmd_bin);
		g_pid = 0;
	}
	else if (app->pid == 0)
	{
		val = execve(cmd_bin, cmd_arg, env);
		if (val == -1)
		{
			ft_putendl_fd("Error execve", 2);
			exit(0);
		}
	}
}

void	m_run_cmd(t_app *app, char **cmd)
{
	char	*path;
	char	*cmd_bin;
	char	**cmd_arg;

	if (ft_strlen(*cmd) > 0)
	{
		m_set_env_var(app, cmd);
		if (m_check_builtin(app, *cmd) != 0)
			return ;
		m_split_cmd_with_del_quote(app, *cmd);
		cmd_bin = (char *)app->param->content;
		path = m_get_cmd_path(app, cmd_bin);
		cmd_arg = m_get_cmd_arg(app);
		if (path != NULL)
		{
			m_exec_cmd(app, path, cmd_arg, app->env);
			ft_strdel(&path);
		}
		ft_free_tab(cmd_arg);
		m_free_char_lst(&app->param);
	}
}
