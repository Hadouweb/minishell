#include "minishell.h"

void	m_run_echo(t_app *app, char *cmd)
{
	if (app && cmd)
		;
	m_set_cmd(app, cmd);
	ft_lstprint(app->param, NULL);
}