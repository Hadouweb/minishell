/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 22:34:24 by nle-bret          #+#    #+#             */
/*   Updated: 2016/11/08 22:34:26 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_print_env(t_app *app)
{
	int		i;
	char	**env;

	i = 0;
	env = app->env;
	while (env && env[i])
	{
		ft_putendl(env[i]);
		i++;
	}
}

void	m_check_flag_env(t_app *app)
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
			while (str[i] && str[i] == 'i')
				i++;
			if (i > 1 && str[i] == '\0' && ++find)
				app->env_flag |= ENV_OPT_I;
		}
		if (!find)
			break ;
		l = l->next;
	}
	app->env_arg = l;
}

void	m_run_cmd_with_special_env(t_app *app)
{
	t_list	*l;
	char	*str2;
	char	*cmd;

	l = app->env_arg;
	if (l)
	{
		cmd = ft_strdup((char*)l->content);
		while (l && l->next)
		{
			cmd = ft_strjoin_free_s1(cmd, " ");
			str2 = (char*)l->next->content;
			cmd = ft_strjoin_free_s1(cmd, str2);
			l = l->next;
		}
		m_free_char_lst(&app->param);
		app->env_arg = NULL;
		app->env_flag = 0;
		m_run_cmd(app, &cmd);
		ft_strdel(&cmd);
	}
	else
		m_print_env(app);
	m_set_env_from_lst(app, &app->lst_env);
}

void	m_set_new_env(t_app *app)
{
	t_list	*l;
	char	**split;
	int		find;

	l = app->env_arg;
	if (app->env_flag == 0)
		m_copy_lst(&app->lst_env, &app->lst_env_tmp);
	while (l)
	{
		find = 0;
		if (ft_strrchr((char*)l->content, '=') != NULL)
		{
			find = 1;
			split = ft_strsplit((char*)l->content, '=');
			if (split && split[0])
				m_set_env_value_by_key(&app->lst_env_tmp, split[0], split[1]);
			ft_free_tab(split);
		}
		if (!find)
			break ;
		l = l->next;
	}
	app->env_arg = l;
}

void	m_run_env(t_app *app, char *cmd)
{
	if (ft_strcmp(cmd, "env") == 0)
		m_print_env(app);
	else
	{
		m_split_cmd_with_del_quote(app, cmd);
		m_check_flag_env(app);
		m_set_new_env(app);
		ft_free_tab(app->env);
		app->env = NULL;
		if (ft_lstsize(app->lst_env_tmp) > 0 || app->env_flag & ENV_OPT_I)
		{
			m_set_env_from_lst(app, &app->lst_env_tmp);
			m_free_lst_envp(&app->lst_env_tmp);
		}
		else
			m_set_env_from_lst(app, &app->lst_env);
		m_run_cmd_with_special_env(app);
	}
	m_free_char_lst(&app->param);
	app->env_flag = 0;
}
