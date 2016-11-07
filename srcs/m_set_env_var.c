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
			if (((t_env*)l->content)->value)
				value = ft_strdup(((t_env*)l->content)->value);
			break;
		}
		l = l->next;
	}
	if (value == NULL)
		value = ft_strnew(1);
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
	value_var = m_find_env_var(app, var);
	new_str = ft_strjoin_free_s2(ft_strjoin(str_1, value_var), str_2);
	ft_strdel(&value_var);
	ft_strdel(&var);
	return (new_str);
}

void	m_set_env_var(t_app *app, char **cmd)
{
	int 	i;
	int 	loop;
	char 	*tmp;
	char 	*str_1;

	i = 0;
	loop = 1;
	while (loop)
	{
		loop = 0;
		tmp = *cmd;
		while ((*cmd)[i])
		{
			if ((*cmd)[i] == '$' && i - 1 > 0 && (*cmd)[i - 1] != '\\')
			{
				str_1 = ft_strndup(*cmd, i);
				*cmd = m_set_var(app, &(*cmd)[i], str_1);
				ft_strdel(&tmp);
				ft_strdel(&str_1);
				loop = 1;
				break;
			}
			i++;
		}
	}
}