/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:40:27 by nle-bret          #+#    #+#             */
/*   Updated: 2016/11/08 14:40:31 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_check_flag_cd(t_app *app)
{
	t_list	*l;
	int		find;
	char	*str;

	l = app->param->next;
	while (l)
	{
		find = 0;
		str = (char*)l->content;
		if (ft_strcmp(str, "-") == 0 && ++find)
			app->cd_flag |= CD_OPT_MIN;
		if (ft_strcmp(str, "-L") == 0 && ++find)
			app->cd_flag |= CD_OPT_L;
		if (ft_strcmp(str, "-P") == 0 && ++find)
			app->cd_flag |= CD_OPT_P;
		if ((ft_strcmp(str, "-PL") == 0 ||
			 ft_strcmp(str, "-LP") == 0))
		{
			app->cd_flag |= CD_OPT_P;
			app->cd_flag |= CD_OPT_L;
		}
		if (!find)
			break ;
		l = l->next;
	}
	app->cd_arg = l;
}

void	m_run_chdir(t_app *app, char *path)
{
	int		error;
	char	buf[1024];
	char	*tmp;
	char	*oldpwd;

	error = m_check_access_cd(path);
	printf("path : [%s\n]", path);
	if (error == 0 && chdir(path) == 0)
	{
		path = getcwd(buf, 1023);
		if (path)
		{
			tmp = ft_strdup(path);
			oldpwd = ft_strdup(m_get_value_env_by_key(app, "PWD"));
			m_set_env_value_by_key(&app->lst_env, "PWD", tmp);
			if (oldpwd)
			{
				m_set_env_value_by_key(&app->lst_env, "OLDPWD", oldpwd);
				ft_strdel(&oldpwd);
			}
			ft_strdel(&tmp);
		}
	}
	else
		m_error_cd(error, path);
}

void	m_cd_home(t_app *app)
{
	char	*home_dir;

	home_dir = m_get_value_env_by_key(app, "HOME");
	if (home_dir)
		m_run_chdir(app, home_dir);
	else
		m_error2("cd: HOME not set");
}

void	m_cd_oldpwd(t_app *app)
{
	char	*old_dir;

	old_dir = m_get_value_env_by_key(app, "OLDPWD");
	if (old_dir)
		m_run_chdir(app, old_dir);
	else
		m_error2("cd: OLDPWD not set");
}

void	m_run_cd(t_app *app, char *cmd)
{
	char	*path_cmd;

	m_split_cmd_with_del_quote(app, cmd);
	m_check_flag_cd(app);
	if (app->cd_arg)
	{
		path_cmd = (char*)app->cd_arg->content;
		m_check_path(app, path_cmd);
	}
	else if (app->cd_flag & CD_OPT_MIN)
		m_cd_oldpwd(app);
	else
		m_cd_home(app);
	m_free_char_lst(&app->param);
	app->cd_flag = 0;
	app->cd_arg = NULL;
}
