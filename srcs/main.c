#include "minishell.h"

void	m_run_cmd(char *path, char **argv, char **env)
{
	int		val;

	printf("Path: [%s]\n", path);
	val = execve(path, argv, env);
	if (val == -1)
		printf("Error execve\n");
}

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
		*cmd = ft_strjoin(*cmd, buf);
		if (token_break)
			break;
	}
	printf("Buf: [%s]\n", *cmd);
	return ret;
}

int		main(int ac, char **av, char **envp)
{
	t_app	app;
	//pid_t	pid;
	//pid_t	pid2;

	ft_bzero(&app, sizeof(t_app));
	if (av[1] && ac && envp)
		;
	m_set_envp(&app, envp);
	m_free_lst_envp(&app);
	//char *cmd;

	/*while (1)
	{
		cmd = ft_strdup("");
		ft_putstr("$> ");
		m_read_cmd(&cmd);
		ft_strdel(&cmd);
	}*/

	//sleep(10);
	return 0;
}