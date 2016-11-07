#include "minishell.h"

void	m_print_env(t_app *app)
{
	int 	i;
	char 	**env;

	i = 0;
	ft_free_tab(app->env);
	app->env = NULL;
	m_set_env_from_lst(app);
	env = app->env;
	while (env && env[i])
	{
		ft_putendl(env[i]);
		i++;
	}
}

void	m_check_flag_env(t_app *app)
{
	t_list	*l;
	int		find;
	char	*str;
	int		i;

	l = app->param->next;
	while (l)
	{
		find = 0;
		i = 1;
		str = (char*)l->content;
		if (str && str[0] && str[0] == '-' && ft_strlen(str) > 1)
		{
			while (str[i] && str[i] == 'i')
				i++;
			if (i > 1 && str[i] == '\0' && ++find)
				app->env_flag |= ENV_OPT_I;
		}
		if (!find)
			break ;
		l = l->next;
	}
	app->env_arg = l;
}

void	m_run_cmd_with_special_env(t_app *app)
{
	t_list	*l;
	char 	*str2;
	char 	*cmd;

	l = app->env_arg;
	if (l)
		cmd = ft_strdup((char*)l->content);
	while (l && l->next)
	{
		cmd = ft_strjoin(cmd, " ");
		str2 = (char*)l->next->content;
		cmd = ft_strjoin_free_s1(cmd, str2);
		l = l->next;
	}
	m_free_char_lst(&app->param);
	app->env_arg = NULL;
	app->env_flag = 0;
	m_run_cmd(app, &cmd);
}

void	m_run_env(t_app *app, char *cmd)
{
	if (ft_strcmp(cmd, "env") == 0)
		m_print_env(app);
	else
	{
		m_split_cmd_with_del_quote(app, cmd);
		m_check_flag_env(app);
		if (app->env_flag & ENV_OPT_I)
		{
			if (ft_lstsize(app->env_arg) >= 0)
			{
				ft_free_tab(app->env);
				app->env = NULL;
				m_run_cmd_with_special_env(app);
			}
		}
		//ft_lstprint(app->param, NULL);
	}
}