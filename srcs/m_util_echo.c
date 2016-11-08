/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_util_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 22:33:06 by nle-bret          #+#    #+#             */
/*   Updated: 2016/11/08 22:33:08 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_split_cmd_echo(t_app *app, char *cmd)
{
	char	*sub_word;
	int		len;

	while (*cmd)
	{
		sub_word = m_get_sub_word(&cmd);
		len = ft_strlen(sub_word);
		ft_lstpush_back(&app->param, (void*)sub_word, len + 1);
		cmd += len;
		ft_strdel(&sub_word);
	}
}

char	*m_get_backslash_echo(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = ft_strnew(ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '\\')
		{
			k = m_set_special_character(&new_str[j], &str[i]);
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

char	*m_del_special_join_echo_arg(char *str)
{
	char	*new_str;
	char	*tmp;

	if (str && (str[0] == '"' || str[0] == '\''))
	{
		tmp = ft_del_char(str, str[0]);
		new_str = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	else
		new_str = ft_strdup(str);
	return (new_str);
}

char	*m_join_echo_arg(t_app *app)
{
	t_list	*l;
	char	*str;
	char	*str2;

	l = app->echo_arg;
	str = NULL;
	if (l)
	{
		str = m_del_special_join_echo_arg((char *)l->content);
		while (l && l->next)
		{
			str = ft_strjoin_free_s1(str, " ");
			str2 = m_del_special_join_echo_arg((char *)l->next->content);
			str = ft_strjoin_free_s2(str, str2);
			l = l->next;
		}
	}
	if (str && !(app->echo_flag & ECHO_OPT_N))
		str = ft_strjoin_free_s1(str, "\n");
	return (str);
}
