#include "minishell.h"

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
	//pid_t	pid;


	if (av[1] && ac && envp)
		;
	//pid = fork();
	/*if (pid == 0)
	{
		printf("In Child\n");
		if (ac > 1)
		{
			char buff[256];
			char *path = "/bin/env";
			printf("%d\n", chdir("/Users/nle-bret/projects/"));
			char *apath = getcwd(buff, 256);
			printf("%s\n", apath);
			printf("%d\n", access(path, R_OK));
			printf("%d\n", access(path, W_OK));
			printf("%d\n", access(path, X_OK));
			printf("%d\n", access(path, F_OK));
			if (access(path, X_OK) != -1)
				execve(path, av, NULL);
		}
	}
	if (pid > 0)
	{*/


	char *cmd;

	while (1)
	{
		cmd = ft_strdup("");
		ft_putstr("$> ");
		m_read_cmd(&cmd);
		ft_strdel(&cmd);
	}
		//ft_strdel(&line);


		//for (char **env = envp; *env; ++env)
		//	printf("%s\n", *env);
		//wait(&pid);
	//}
	return 0;
}