#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

int		getdiff(void)
{
	FILE *fp;
	char buff[255];

	fp = fopen("diff", "r");
	fscanf(fp, "%s", buff);
	fclose(fp);

	return (ft_strlen(buff));
}

void	cmd(char *cmd, char *param)
{
	char str1[1024];
	char str2[1024];
	char str_cmd[1024];


	sprintf(str_cmd, "echo '%s%s' > test_cmd", cmd, param);
	system(str_cmd);
	sprintf(str1, "csh < test_cmd 1> output1 2> outputerr1");
	sprintf(str2, "../minishell < test_cmd 1> output2 2> outputerr2");

	//printf("%s\n", str1);
	//printf("%s\n", str2);

	system(str1);
	system(str2);
	system("cat outputerr1 >> output1");
	system("cat outputerr2 >> output2");
	system("diff output1 output2 > diff");
	if (getdiff() > 0) {
		printf("\033[031m[ Error    ]\033[0m minishell < %s\n", str_cmd);
		system("cat diff");
		exit(1);
	} else
		printf("\033[032m[ Success  ]\033[0m minishell < %s\n", str_cmd);
}

void	test0(void)
{
	printf("\033[035m****************** test0 ******************\033[0m\n");
	//cmd("", "echo lol; exit;");
	//cmd("", "echo -n end; exit;");
	//cmd("", "echo -n \"end\"; exit;");
	//cmd("", "echo \"lol\"; exit;");
	//cmd("", "echo \"lol\tlol\"; exit;");
	//cmd("", "echo 'lol  \t lol'; exit;");
	//cmd("", "cd 'lol  \t lol'; exit;");
	//cmd("", "unsetenv PATH; ls; env; exit;");
	//cmd("", "unsetenv HOME; cd; pwd; exit;");
}

int		main(void)
{
	system("make -C ../");
	test0();
	return (0);
}