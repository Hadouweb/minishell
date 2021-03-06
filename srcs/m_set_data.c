/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_set_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 11:57:02 by nle-bret          #+#    #+#             */
/*   Updated: 2016/11/04 11:57:03 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	m_get_env_struct(char *env)
{
	t_env	tenv;
	char	**split;

	ft_bzero(&tenv, sizeof(t_env));
	split = ft_strsplit(env, '=');
	if (split)
	{
		if (split[0])
			tenv.key = ft_strdup(split[0]);
		if (split[1])
			tenv.value = ft_strdup(split[1]);
		ft_free_tab(split);
		tenv.lst_value = NULL;
		if (tenv.key && tenv.value && ft_strcmp(tenv.key, "PATH") == 0)
			tenv.lst_value = ft_lstsplit(tenv.value, ':');
	}
	return (tenv);
}

void	m_set_envp(t_app *app, char **envp)
{
	int		i;
	t_env	env;

	i = 0;
	while (envp[i] != NULL)
	{
		env = m_get_env_struct(envp[i]);
		ft_lstpush_back(&app->lst_env, (void*)&env, sizeof(t_env));
		i++;
	}
	m_set_path_node(app);
}

void	m_set_path_node(t_app *app)
{
	t_list	*l;
	t_env	*env;

	l = app->lst_env;
	app->path_node = NULL;
	while (l)
	{
		env = (t_env*)l->content;
		if (ft_strcmp(env->key, "PATH") == 0 && (env->value != NULL))
		{
			if (env->lst_value == NULL)
				env->lst_value = ft_lstsplit(env->value, ':');
			app->path_node = l;
			break ;
		}
		l = l->next;
	}
}

void	m_set_env_from_lst(t_app *app, t_list **lst)
{
	int		nb_env;
	t_list	*l;
	t_env	*env;
	int		i;

	i = 0;
	l = *lst;
	ft_free_tab(app->env);
	nb_env = ft_lstsize(l);
	if ((app->env = (char**)ft_memalloc((nb_env + 1) * sizeof(char*))) == NULL)
		m_error_malloc("m_set_env_from_lst");
	while (l)
	{
		env = (t_env*)l->content;
		app->env[i] = ft_strjoin(env->key, "=");
		if (env->value)
			app->env[i] = ft_strjoin_free_s1(app->env[i], env->value);
		l = l->next;
		i++;
	}
	app->env[i] = NULL;
}
