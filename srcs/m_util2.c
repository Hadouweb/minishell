/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_util2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 11:58:17 by nle-bret          #+#    #+#             */
/*   Updated: 2016/11/04 11:58:20 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_set_shlvl(t_app *app)
{
	char	*value;
	char	*new_value;
	int		shlvl;

	shlvl = 1;
	value = m_get_value_env_by_key(app, "SHLVL");
	if (value)
	{
		shlvl = ft_atoi(value);
		shlvl++;
	}
	new_value = ft_itoa(shlvl);
	m_set_env_value_by_key(&app->lst_env, "SHLVL", new_value);
	ft_strdel(&new_value);
}

void	m_set_pwd(t_app *app)
{
	char	*value;
	char	*new_value;
	char	buf[1024];

	value = m_get_value_env_by_key(app, "PWD");
	if (value == NULL)
	{
		new_value = getcwd(buf, 1023);
		m_set_env_value_by_key(&app->lst_env, "PWD", new_value);
	}
}

void	m_copy_lst(t_list **lst_src, t_list **lst_dst)
{
	t_list	*l;
	t_env	env;

	l = *lst_src;
	while (l)
	{
		env = m_copy_node_env(l);
		ft_lstpush_back(lst_dst, &env, sizeof(t_env));
		l = l->next;
	}
}

int		m_secure_egal_char(char **key, char **value)
{
	int		ret;

	ret = 0;
	if (ft_strchr(*key, '=') || ft_strchr(*value, '='))
	{
		m_error2("the character '=' is not allowed");
		ft_strdel(key);
		ft_strdel(value);
		ret = -1;
	}
	return (ret);
}

void	m_check_setenv_path(t_app *app)
{
	t_list	*l;

	l = app->param;
	if (l && l->next)
		l = l->next;
	if (l && l->content)
	{
		if (ft_strcmp((char *)l->content, "PATH") == 0)
			m_set_path_node(app);
	}
}
