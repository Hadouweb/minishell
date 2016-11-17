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
			cmd += 2;
			ft_strdel(&tmp);
		}
		len += ft_strlen(sub_word);
		ft_lstpush_back(&app->param, sub_word, len + 1);
		cmd += len;
		ft_strdel(&sub_word);
	}
}

int		m_replace_env_by_key(t_list **lst, char *key, char *value)
{
	t_list	*l;
	char	*tmp;
	t_env	*env;

	l = *lst;
	if (key && value)
	{
		while (l && ft_strcmp(((t_env*)l->content)->key, key) != 0)
		{
			env = (t_env*)l->content;
			if (ft_strcmp(env->key, key) == 0)
				break ;
			l = l->next;
		}
		if (l && value)
		{
			tmp = ((t_env*)l->content)->value;
			((t_env*)l->content)->value = ft_strdup(value);
			ft_strdel(&tmp);
			return (1);
		}
	}
	return (0);
}

void	m_add_env_by_key(t_list **lst, char *key, char *value)
{
	t_env	env;

	ft_bzero(&env, sizeof(t_env));
	if (key)
	{
		env.key = ft_strdup(key);
		if (value)
			env.value = ft_strdup(value);
		else
			env.value = ft_strdup("");
		ft_lstpush_back(lst, (void*)&env, sizeof(t_env));
	}
}

void	m_set_env_value_by_key(t_list **lst, char *key, char *value)
{
	if (m_replace_env_by_key(lst, key, value) == 0)
		m_add_env_by_key(lst, key, value);
}

char	*m_get_value_env_by_key(t_app *app, char *key)
{
	t_list	*l;
	t_env	*env;

	l = app->lst_env;
	if (key)
	{
		while (l)
		{
			env = (t_env*)l->content;
			if (env && env->key && env->value && ft_strcmp(env->key, key) == 0)
				return (env->value);
			l = l->next;
		}
	}
	return (NULL);
}
