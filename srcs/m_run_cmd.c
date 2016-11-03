#include "minishell.h"

int		m_check_builtin(t_app *app, char *cmd)
{
	int 	ret;

	ret = 0;
	if (ft_strcmp(cmd, "exit") == 0 && (ret = 1))
	{
		m_free_all(app);
		exit(0);
	}
	return ret;
}

int 	m_check_access(char *full_path)
{
	if (access(full_path, X_OK) == -1 && access(full_path, F_OK) == 0)
		return (-1);
	else if(access(full_path, X_OK | F_OK) == 0)
		return (0);
	return (-10);
}

char 	*m_get_cmd_path(t_app *app, char *cmd)
{
	char 	*full_path;
	char 	*path;
	t_list	*l;
	int 	check_access;
	int 	cmp_access;

	l = NULL;
	check_access = -100;
	if (app->path_node != NULL)
		l = ((t_env *) app->path_node->content)->lst_value;
	while(l)
	{
		path = (char*)l->content;
		full_path = ft_strjoin_free_s1(ft_strjoin(path, "/"), cmd);
		cmp_access = m_check_access(full_path);
		check_access = (cmp_access > check_access) ? cmp_access : check_access;
		if(check_access == 0)
			return (full_path);
		ft_strdel(&full_path);
		l = l->next;
	}
	m_error_access(cmd, check_access);
	return (NULL);
}

char 	**m_get_cmd_arg(char *cmd)
{
	char 	**arg;

	if (cmd)
		;
	arg = NULL;
	return (arg);
}

void	m_run_cmd(t_app *app, char *cmd)
{
	int		val;
	char 	*path;
	char 	**arg;

	if (m_check_builtin(app, cmd) != 0)
		return;
	m_set_cmd(app, cmd);
	path = m_get_cmd_path(app, cmd);
	//arg = m_get_cmd_arg(cmd);
	if (path != NULL)
	{
		val = execve(path, arg, app->env);
		if (val == -1)
			ft_putendl_fd("Error execve", 2);
	}
}