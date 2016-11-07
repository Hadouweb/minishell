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
		if (ft_strcmp(str, "-L") == 0 && ++find)
			app->cd_flag |= CD_OPT_L;
		if (ft_strcmp(str, "-P") == 0 && ++find)
			app->cd_flag |= CD_OPT_P;
		if ((ft_strcmp(str, "-PL") == 0 ||
				ft_strcmp(str, "-LP") == 0) && ++find)
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
	char 	buf[1024];

	error = m_check_access_cd(path);
	if (error == 0)
	{
		if (chdir(path) == 0)
		{
			path = getcwd(buf, 1023);
			if (path)
			{
				m_set_env_value_by_key(app, "PWD", ft_strdup(path));
			}
		}
	}
	else
		m_error_cd(error, path);
}

void	m_check_path(t_app *app, char *path_cmd)
{
	char 	*curpath;
	char 	*pwd;
	char 	*tmp;

	if (path_cmd)
	{
		curpath = ft_strdup(path_cmd);
		if (curpath[0] != '/')
		{
			pwd = m_get_value_env_by_key(app, "PWD");
			if (pwd)
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

void	m_cd_home(t_app *app)
{
	char 	*home_dir;

	home_dir = m_get_value_env_by_key(app, "HOME");
	if (home_dir)
		m_run_chdir(app, home_dir);
	else
		m_error2("cd: HOME not set");
}

void	m_run_cd(t_app *app, char *cmd)
{
	char 	*path_cmd;

	m_split_cmd_with_del_quote(app, cmd);
	m_check_flag_cd(app);
	if (app->cd_arg)
	{
		path_cmd = (char*)app->cd_arg->content;
		m_check_path(app, path_cmd);
	}
	else
		m_cd_home(app);
	m_free_char_lst(&app->param);
	app->cd_flag = 0;
	app->cd_arg = NULL;
}