/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 11:31:41 by nle-bret          #+#    #+#             */
/*   Updated: 2016/11/06 11:31:45 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		m_get_size_sub_word(char *str)
{
	int		i;
	int		token1;
	int		token2;

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

char	*m_get_sub_word(char **str)
{
	char	*sub_word;
	int		size_sub_word;

	while (**str == ' ' || **str == '\t')
		(*str)++;
	size_sub_word = m_get_size_sub_word(*str);
	sub_word = ft_strndup(&(**str), size_sub_word);
	return (sub_word);
}

int		m_set_octacl_special_char(char *str)
{
	char	*str_o;
	int		ret;

	str_o = ft_strndup(&str[1], 3);
	ret = ft_atoi_base(str_o, 8);
	ft_strdel(&str_o);
	return (ret);
}

void	m_check_flag_echo(t_app *app)
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
			while (str[i] && str[i] == 'n')
				i++;
			if (i > 1 && str[i] == '\0' && ++find)
				app->echo_flag |= ECHO_OPT_N;
		}
		if (!find)
			break ;
		l = l->next;
	}
	app->echo_arg = l;
}

void	m_run_echo(t_app *app, char *cmd)
{
	char	*tmp;
	char	*str;

	m_split_cmd_echo(app, cmd);
	m_check_flag_echo(app);
	tmp = m_join_echo_arg(app);
	if (tmp)
	{
		str = m_get_backslash_echo(tmp);
		ft_putstr(str);
		ft_strdel(&str);
		ft_strdel(&tmp);
	}
	m_free_char_lst(&app->param);
	app->echo_arg = NULL;
	app->echo_flag = 0;
}
