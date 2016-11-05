/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_free_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 11:52:52 by nle-bret          #+#    #+#             */
/*   Updated: 2016/11/04 11:52:53 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_free_lst_envp_value(t_env *env)
{
	t_list	*tmp;
	t_list	*l_value;
	char	*val;

	l_value = env->lst_value;
	while (l_value)
	{
		val = (char*)l_value->content;
		ft_strdel(&val);
		tmp = l_value;
		l_value = l_value->next;
		free(tmp);
	}
}

void	m_free_lst_envp(t_app *app)
{
	t_list	*l;
	t_list	*tmp;
	t_env	*env;

	l = app->lst_env;
	while (l)
	{
		env = (t_env*)l->content;
		ft_strdel(&env->key);
		ft_strdel(&env->value);
		if (env->lst_value != NULL)
			m_free_lst_envp_value(env);
		tmp = l;
		l = l->next;
		free(tmp);
		free(env);
	}
	app->lst_env = NULL;
}

void	m_free_env_from_lst(t_app *app)
{
	int		i;

	i = 0;
	while (app->env[i] != NULL)
	{
		ft_strdel(&app->env[i]);
		i++;
	}
	free(app->env);
	app->env = NULL;
}

void	m_free_param_lst(t_app *app)
{
	t_list	*l;
	t_list	*tmp;

	l = app->param;
	while (l)
	{
		ft_strdel((char**)&l->content);
		tmp = l;
		l = l->next;
		free(tmp);
	}
	app->param = NULL;
}

void	m_free_char_lst(t_list **lst)
{
	t_list	*l;
	t_list	*tmp;

	l = *lst;
	while (l)
	{
		ft_strdel((char**)&l->content);
		tmp = l;
		l = l->next;
		free(tmp);
	}
	*lst = NULL;
}

void	m_free_all(t_app *app)
{
	m_free_param_lst(app);
	m_free_lst_envp(app);
	m_free_env_from_lst(app);
}
