#include "minishell.h"

void	m_free_lst_envp(t_app *app)
{
	t_list	*l;
	t_list	*l_value;
	t_list	*tmp;
	t_env	*env;
	char 	*val;

	l = app->lst_env;
	while(l)
	{
		env = (t_env*)l->content;
		ft_strdel(&env->key);
		ft_strdel(&env->value);
		if (env->lst_value != NULL)
		{
			l_value = env->lst_value;
			while(l_value)
			{
				val = (char*)l_value->content;
				ft_strdel(&val);
				tmp = l_value;
				l_value = l_value->next;
				free(tmp);
			}
			free(env->lst_value);
		}
		tmp = l;
		l = l->next;
		free(tmp);
	}
}