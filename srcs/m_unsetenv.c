#include "minishell.h"

t_env	m_copy_node_env(t_list *n)
{
	t_env	env;
	t_list	*lst_value;
	t_list	*l;

	lst_value = NULL;
	ft_bzero(&env, sizeof(t_env));
	if (((t_env*)n->content)->key)
		env.key = ft_strdup(((t_env*)n->content)->key);
	if (((t_env*)n->content)->value)
		env.value = ft_strdup(((t_env*)n->content)->value);
	if (((t_env*)n->content)->lst_value)
	{
		l = ((t_env*)n->content)->lst_value;
		while (l)
		{
			ft_lstpush_back(&lst_value, (char *) l->content, l->content_size);
			l = l->next;
		}
		env.lst_value = lst_value;
	}
	return (env);
}

void	m_delete_env(t_app *app, char *key)
{
	t_list	*l;
	t_list	*new_lst_env;
	t_env	env;

	l = app->lst_env;
	new_lst_env = NULL;
	if (key)
	{
		while (l)
		{
			if (ft_strcmp(((t_env*)l->content)->key, key) != 0)
			{
				env = m_copy_node_env(l);
				ft_lstpush_back(&new_lst_env, &env, sizeof(t_env));
			}
			l = l->next;
		}
		m_free_lst_envp(&app->lst_env);
		app->lst_env = new_lst_env;
		ft_free_tab(app->env);
		app->env = NULL;
		m_set_env_from_lst(app, &app->lst_env);
	}
}

void	m_run_unsetenv(t_app *app, char *cmd)
{
	t_list	*l;

	m_split_cmd_with_del_quote(app, cmd);
	l = app->param;
	if (l)
		l = l->next;
	while (l)
	{
		m_delete_env(app, (char*)l->content);
		l = l->next;
	}
	m_free_char_lst(&app->param);
}