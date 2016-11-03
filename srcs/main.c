#include "minishell.h"

/*void	m_run_cmd(t_app *app, char *path, char **argv)
{
	int		val;

	printf("Path: [%s]\n", path);
	val = execve(path, argv, env);
	if (val == -1)
		printf("Error execve\n");
}*/

int 	m_read_cmd(char **cmd)
{
	int 	ret;
	char 	buf[11];
	int 	token_break;

	token_break = 0;
	while ((ret = read(0, &buf, 10)) != -1)
	{
		buf[ret] = '\0';
		if (buf[ret - 1] == '\n') {
			buf[ret - 1] = '\0';
			token_break = 1;
		}
		*cmd = ft_strjoin_free_s1(*cmd, buf);
		if (token_break)
			break;
	}
	return ret;
}

void	m_check_builtin(t_app *app, char *cmd)
{
	if (ft_strcmp(cmd, "exit") == 0) {
		m_free_lst_envp(app);
		exit(0);
	}
}

int		main(int ac, char **av, char **envp)
{
	t_app	app;
	//char	*cmd;

	if (av && ac)
		;
	ft_bzero(&app, sizeof(t_app));
	m_set_envp(&app, envp);
	m_set_env_from_lst(&app);
	m_debug_env(app.env);

	/*while (1)
	{
		cmd = ft_strdup("");
		ft_putstr("$> ");
		m_read_cmd(&cmd);
		//printf("Buf: [%s]\n", cmd);
		m_check_builtin(&app, cmd);
		ft_strdel(&cmd);
	}*/
	m_free_lst_envp(&app);
	m_free_env_from_lst(&app);
	return 0;
}