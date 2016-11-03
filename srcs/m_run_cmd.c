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

char 	*m_get_cmd_path(t_app *app, char *cmd)
{
	char 	*path;
	t_list	*l;

	l = NULL;
	if (app->path_node != NULL) {
		l = ((t_env *) app->path_node->content)->lst_value;
		//ft_lstprint(l, NULL);
	}
	if (cmd)
		;
	path = NULL;
	return (path);
}

char 	*m_get_cmd_arg(char *cmd)
{
	char 	*arg;

	if (cmd)
		;
	arg = NULL;
	return (arg);
}

void	m_run_cmd(t_app *app, char *cmd)
{
	int		val;
	char 	*path;
	char 	*arg;

	if (m_check_builtin(app, cmd) != 0)
		return;
	path = m_get_cmd_path(app, cmd);
	printf("Path cmd: %s\n", path);
	arg = m_get_cmd_arg(cmd);
	val = execve(path, &arg, app->env);
	if (val == -1)
		ft_putendl_fd("Error execve", 2);
}