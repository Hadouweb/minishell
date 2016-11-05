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
	int 	i;

	l = app->param;
	l = l->next;
	while (l)
	{
		find = 0;
		i = 2;
		str = (char*)l->content;
		if (str && str[0])
		{
			if (ft_strcmp(str, "-n") == 0 && ++find)
				app->echo_flag |= ECHO_OPT_N;
			else
			{
				while (str[i] && str[i] == 'n')
					i++;
				if (i > 2 && str[i] == '\0' && ++find)
					app->echo_flag |= ECHO_OPT_N;
			}
		}
		if (!find)
			break;
		l = l->next;
	}
	app->echo_arg = l;
}

int 	m_set_octacl_special_char(char *str)
{
	char 	*str_o;
	int 	ret;

	str_o = ft_strndup(&str[1], 3);
	ret = ft_atoi_base(str_o, 8);
	ft_strdel(&str_o);
	return (ret);
}

int		m_set_escaped_character(char *new_str, char *str)
{
	int		i;

	i = 0;
	if (str[1])
	{
		if (str[1] == '\\' && (i = 2))
			new_str[0] = '\\';
		else if (str[1] == 'n' && (i = 2))
			new_str[0] = '\n';
		else if (str[1] == 'v' && (i = 2))
			new_str[0] = '\v';
		else if (str[1] == 'a' && (i = 2))
			new_str[0] = '\a';
		else if (str[1] == 'b' && (i = 2))
			new_str[0] = '\b';
		else if (str[1] == 'r' && (i = 2))
			new_str[0] = '\r';
		else if (str[1] == 'f' && (i = 2))
			new_str[0] = '\f';
		else if (str[1] == 't' && (i = 2))
			new_str[0] = '\t';
		else if (str[1] == 'c' && (i = 1))
			new_str[0] = '\0';
		else if (str[1] == '0' && (i = 5))
			new_str[0] = m_set_octacl_special_char(&str[1]);
	}
	return (i);
}

char 	*m_get_str_special_backslash(char *str)
{
	int 	i;
	int 	j;
	int 	k;
	char 	*new_str;

	i = 0;
	j = 0;
	k = 0;
	//printf("str: [%s]\n", str);
	str = ft_del_char(str, str[0]);
	//printf("str2: [%s]\n", str);
	new_str = ft_strnew(ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '\\')
		{
			k = m_set_escaped_character(&new_str[j], &str[i]);
			j += (k > 0) ? 1 : 0;
			i += k;
		}
		if (str[i])
		{
			new_str[j] = str[i];
			j++;
			i++;
		}
		//printf("_ str: [%s](%d) | new_str: [%s](%d)\n", &str[i], i, new_str, j);
	}
	new_str[j] = '\0';
	//printf("new_str: [%s]\n", new_str);
	return (new_str);
}

char	*m_get_backslash_echo(char *str)
{
	int 	i;
	int 	j;
	int 	k;
	char 	*new_str;

	i = 0;
	j = 0;
	k = 0;
	new_str = ft_strnew(ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '\\')
		{
			k = m_set_escaped_character(&new_str[j], &str[i]);
			j += (k > 0) ? 1 : 0;
			i += k;
		}
		if (str[i])
		{
			new_str[j] = str[i];
			j++;
			i++;
		}
	}
	new_str[j] = '\0';
	return (new_str);
}

char 	*m_del_special_join_echo_arg(char *str)
{
	char 	*new_str;
	char 	*tmp;

	tmp = ft_del_char(str, str[0]);
	new_str = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (new_str);
}

char	*m_join_echo_arg(t_app *app)
{
	t_list	*l;
	char 	*str;
	char 	*str2;

	l = app->echo_arg;
	str = NULL;
	str2 = NULL;
	if (l)
	{
		str = (char *) l->content;
		if (str && (str[0] == '"' || str[0] == '\''))
			str = m_del_special_join_echo_arg((char *) l->content);
		else
			str = ft_strdup((char *) l->content);
		while (l && l->next)
		{
			str = ft_strjoin_free_s1(str, " ");
			str2 = (char *) l->next->content;
			if (str2 && (str2[0] == '"' || str2[0] == '\''))
				str2 = m_del_special_join_echo_arg((char *) l->next->content);
			else
				str2 = ft_strdup((char *) l->next->content);
			str = ft_strjoin_free_s2(str, str2);
			l = l->next;
		}
	}
	if (str && !(app->echo_flag & ECHO_OPT_N))
		str = ft_strjoin_free_s1(str, "\n");
	return (str);
}

void	m_run_echo(t_app *app, char *cmd)
{
	char 	*tmp;
	char 	*str;

	m_split_cmd_echo(app, cmd);
	m_check_flag(app);
	tmp = m_join_echo_arg(app);
	if (tmp)
	{
		//m_set_arg_echo(app->echo_arg);
		str = m_get_backslash_echo(tmp);
		ft_putstr(str);
		ft_strdel(&str);
		ft_strdel(&tmp);
	}


	//m_set_arg_echo(app->echo_arg);
	//m_print_echo_arg(app);

	m_free_char_lst(&app->param);
	app->echo_arg = NULL;
	app->echo_flag = 0;
}