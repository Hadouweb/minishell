#include "minishell.h"

char 	*m_find_env_var(t_app *app, char *var)
{
	t_list	*l;
	char 	*value;

	value = NULL;
	l = app->lst_env;
	while (l)
	{
		if (ft_strcmp(((t_env*)l->content)->key, var) == 0)
		{
			value = ft_strdup(((t_env*)l->content)->value);
			break;
		}
		l = l->next;
	}
	if (value == NULL)
		value = ft_strdup("");

	ft_lstprint(app->lst_env, m_debug_content_env);
	return (value);
}

char	*m_set_var(t_app *app, char *cmd, char *str_1)
{
	int 	i;
	char 	*var;
	char 	*value_var;
	char 	*new_str;
	char 	*str_2;

	i = 1;
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '$'
		&& cmd[i] != '/' && cmd[i] != '.')
		i++;
	var = ft_strndup(cmd + 1, i - 1);
	str_2 = ft_strsub(cmd, i, ft_strlen(&cmd[i]));

	printf("str_1: [%s]\n", str_1);
	printf("var: [%s]\n", var);
	printf("str_2: [%s]\n", str_2);

	value_var = m_find_env_var(app, var);


	str_1 = ft_strjoin(str_1, value_var);
	new_str = ft_strjoin(str_1, str_2);
	return (new_str);
}

void	m_set_env_var(t_app *app, char *cmd)
{
	int 	i;
	int 	loop;
	char 	*str_1;

	i = 0;
	loop = 1;
	while (loop)
	{
		loop = 0;
		while (cmd[i])
		{
			if (cmd[i] == '$')
			{
				str_1 = ft_strndup(cmd, i);
				cmd = m_set_var(app, &cmd[i], str_1);
				printf("cmd: [%s]\n", cmd);
				loop = 1;
				break;
			}
			i++;
		}
	}
}