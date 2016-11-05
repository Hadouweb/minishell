#include "minishell.h"

int 	m_get_size_sub_word(char *str)
{
	int 	i;
	int 	token1;
	int 	token2;

	i = 0;
	token1 = 0;
	token2 = 0;
	while (str[i])
	{
		if (token1 == 2 || token2 == 2)
			break ;
		if ((str[i] == ' ' || str[i] == '\t') && token1 == 0 && token2 == 0)
			break ;
		else if (str[i] == '"' && token2 != 1)
			token1++;
		else if (str[i] == '\'' && token1 != 1)
			token2++;
		i++;
	}
	return (i);
}

char 	*m_get_sub_word(char **str)
{
	int 	i;
	int 	token1;
	int 	token2;
	char 	*sub_word;
	int 	size_sub_word;

	i = 0;
	token1 = 0;
	token2 = 0;

	while (**str == ' ' || **str == '\t')
		(*str)++;

	size_sub_word = m_get_size_sub_word(*str);
	sub_word = ft_strndup(&(**str), size_sub_word);

	return (sub_word);
}

void	m_split_cmd_echo(t_app *app, char *cmd)
{
	char	*sub_word;
	int 	len;

	while (*cmd)
	{
		sub_word = m_get_sub_word(&cmd);
		len = ft_strlen(sub_word);
		ft_lstpush_back(&app->param, (void*)sub_word, len + 1);
		cmd += len;
		ft_strdel(&sub_word);
	}
}

void	m_check_flag(t_app *app)
{
	t_list	*l;
	int 	find;
	char 	*str;

	l = app->param;
	l = l->next;
	while (l)
	{
		find = 0;
		str = (char*)l->content;
		if (ft_strcmp(str, "-n") == 0 && ++find)
			app->echo_flag |= ECHO_OPT_N;
		if (ft_strcmp(str, "-e") == 0 && ++find)
			app->echo_flag |= ECHO_OPT_EMIN;
		if ((ft_strcmp(str, "-ne") == 0 || ft_strcmp(str, "-en") == 0) && ++find)
		{
			app->echo_flag |= ECHO_OPT_N;
			app->echo_flag |= ECHO_OPT_EMIN;
		}
		if (!find)
			break;
		l = l->next;
	}
	app->echo_arg = l;
}

void	m_set_arg_echo(t_list *lst)
{
	t_list	*l;
	char 	*str;
	char 	*tmp;

	l = lst;
	ft_lstprint(lst, NULL);
	while (l)
	{
		str = (char*)l->content;
		if (str && (str[0] == '"' || str[0] == '\''))
		{
			tmp = (char*)l->content;
			l->content = (void *) ft_del_char(str, str[0]);
			ft_strdel(&tmp);
		}
		l = l->next;
	}
}

void	m_print_echo_arg(t_app *app)
{
	t_list	*l;

	l = app->echo_arg;
	while (l)
	{
		ft_putstr((char*)l->content);
		ft_putchar(' ');
		l = l->next;
	}
	if (!(app->echo_flag & ECHO_OPT_N))
		ft_putchar('\n');
}

void	m_run_echo(t_app *app, char *cmd)
{
	m_split_cmd_echo(app, cmd);
	m_check_flag(app);

	if (!(app->echo_flag & ECHO_OPT_EMIN))
	{
		m_set_arg_echo(app->echo_arg);
		m_print_echo_arg(app);
	}

	m_free_char_lst(&app->param);
	app->echo_arg = NULL;
	app->echo_flag = 0;
}