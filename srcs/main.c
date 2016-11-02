#include "minishell.h"

pid_t	m_new_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		printf("Error pid\n");
	return pid;
}

void	m_run_cmd(char *path, char **argv, char **env)
{
	int		val;

	printf("Path: [%s]\n", path);
	val = execve(path, argv, env);
	if (val == -1)
		printf("Error execve\n");
}

int		main(int ac, char **av)
{
	pid_t	pid;
	char 	*argv[] = { "ls", "-1", ".", NULL };


	pid = m_new_process();
	if (pid == 0)
		printf("________ Parent process: [%d] in child\n", pid);
	if (pid > 0)
		printf("________ Child process: [%d] in Parent\n", pid);

	if (ac > 1 && pid == 0) {
		m_run_cmd(av[1], argv, NULL);
		sleep(10);
	}
	if (pid > 0)
		wait(&pid);
	printf("______________________ LOL _______________\n");

	return 0;
}