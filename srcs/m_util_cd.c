/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_util_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 22:17:42 by nle-bret          #+#    #+#             */
/*   Updated: 2016/11/08 22:17:45 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_check_path(t_app *app, char *path_cmd)
{
	char	*curpath;
	char	*pwd;
	char	*tmp;

	if (path_cmd && (curpath = ft_strdup(path_cmd)))
	{
		if (curpath[0] != '/' && curpath[0] != '.' &&
			(pwd = m_get_value_env_by_key(app, "PWD")) != NULL)
		{
			if (pwd[ft_strlen(pwd) - 1] != '/')
			{
				tmp = curpath;
				curpath = ft_strjoin_free_s1(ft_strjoin(pwd, "/"), curpath);
			}
			else
			{
				tmp = curpath;
				curpath = ft_strjoin(pwd, curpath);
			}
			ft_strdel(&tmp);
		}
		m_run_chdir(app, curpath);
		ft_strdel(&curpath);
	}
}

int		m_check_access_cd(char *path)
{
	if (access(path, X_OK) == -1)
		return (-2);
	if (access(path, F_OK) == -1)
		return (-1);
	return (0);
}

void	m_error_cd(int error, char *path)
{
	if (error == -1)
		m_error3("cd: ", path, " : No such file or directory");
	if (error == -2)
		m_error3("cd: ", path, " : Permission denied");
}
