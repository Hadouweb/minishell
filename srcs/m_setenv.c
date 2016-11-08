#include "minishell.h"

void	m_add_env(t_app *app)
{
	char 	*key;
	char 	*value;
	t_env	env;

	ft_bzero(&env, sizeof(t_env));
	key = m_get_key_param(app);
	value = m_get_value_param(app);
	if (key)
	{
		env.key = key;
		if (value)
			env.value = value;
		ft_lstpush_back(&app->lst_env, (void*)&env, sizeof(t_env));
	}
}

int 	m_replace_env(t_app *app)
{
	t_list	*l;
	char 	*key;
	char 	*value;
	char 	*tmp;
	int 	ret;

	ret = 0;
	l = app->lst_env;
	key = m_get_key_param(app);
	value = m_get_value_param(app);
	if (ft_strchr(key, '=') || ft_strchr(value, '='))
	{
		m_error2("the character '=' is not allowed");
		ft_strdel(&key);
		ft_strdel(&value);
		ret = -1;
	}
	else if (key)
	{
		while (l && ft_strcmp(((t_env*)l->content)->key, key) != 0)
			l = l->next;
		if (l && value)
		{
			tmp = ((t_env*)l->content)->value;
			((t_env*)l->content)->value = value;
			ft_strdel(&tmp);
			ret = 1;
		}
		else
			ft_strdel(&value);
		ft_strdel(&key);
	}
	return (ret);
}

char 	*m_get_key_param(t_app *app)
{
	t_list	*l;
	char 	*key;

	l = app->param;
	key = NULL;
	if (l && l->next)
	{
		if ((char*)l->next->content)
			key = ft_strdup((char *) l->next->content);
	}
	return (key);
}

char 	*m_get_value_param(t_app *app)
{
	t_list	*l;
	char 	*value;

	l = app->param;
	value = NULL;
	if (l && l->next && l->next->next)
	{
		if ((char*)l->next->next->content)
			value = ft_strdup((char *) l->next->next->content);
	}
	return (value);
}

void	m_run_setenv(t_app *app, char *cmd)
{
	m_split_cmd_with_del_quote(app, cmd);
	if (ft_lstsize(app->param) > 3)
		ft_putstr_fd("setenv: Too many arguments.\n", 2);
	else
	{
		if (m_replace_env(app) == 0)
			m_add_env(app);
		m_set_env_from_lst(app, &app->lst_env);
	}
	m_free_char_lst(&app->param);
}