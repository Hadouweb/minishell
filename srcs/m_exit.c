#include "minishell.h"

static void	m_special_exit(char *nb)
{
	int  intnb;

	intnb = 0;
	if (nb)
	{
		intnb = ft_atoi(nb);
		if (intnb > 255)
			intnb = 0;
	}
	exit(intnb);
}

void		m_run_exit(t_app *app, char *cmd, char *builtin)
{
	m_split_cmd_echo(app, cmd);
	if (ft_lstsize(app->param) == 2)
		m_special_exit(app->param->next->content);
	else if (ft_lstsize(app->param) == 1)
		exit(0);
	else
	{
		ft_putstr_fd("exit: Expression Syntax.\n", 2);
		m_free_char_lst(&app->param);
		return ;
	}
	m_free_all(app);
	ft_strdel(&builtin);
	m_free_char_lst(&app->lst_cmd);
}
