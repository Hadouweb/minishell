/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_util.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 11:58:17 by nle-bret          #+#    #+#             */
/*   Updated: 2016/11/04 11:58:20 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_split_cmd_with_del_quote(t_app *app, char *cmd)
{
	char	*sub_word;
	char	*tmp;
	int		len;

	while (*cmd)
	{
		len = 0;
		sub_word = m_get_sub_word(&cmd);
		if (sub_word && (sub_word[0] == '"' || sub_word[0] == '\''))
		{
			tmp = sub_word;
			sub_word = ft_del_char(sub_word, sub_word[0]);
			len += 2;
			ft_strdel(&tmp);
		}
		len += ft_strlen(sub_word);
		ft_lstpush_back(&app->param, (void*)sub_word, len + 1);
		cmd += len;
		ft_strdel(&sub_word);
	}
}

char 	*m_get_value_env_by_key(t_app *app, char *key)
{
	t_list	*l;
	t_env	*env;

	l = app->lst_env;
	if (key)
	{
		while(l)
		{
			env = (t_env*)l->content;
			if (env && env->key && env->value && ft_strcmp(env->key, key) == 0)
				return (env->value);
			l = l->next;
		}
	}
	return (NULL);
}