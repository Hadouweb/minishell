#include "minishell.h"

int		m_check_builtin(t_app *app, char *cmd)
{
	int		ret;

	ret = 0;
	ft_strdel(&cmd);
	ft_lstprint(app->param, NULL);
	cmd = (char*)app->param->content;
	if (ft_strcmp(cmd, "exit") == 0 && (ret = 1))
	{
		m_free_all(app);
		exit(0);
	}
	return (ret);
}