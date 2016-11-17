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
		//system("cat diff");
		//exit(1);
	} else
		printf("\033[032m[ Success  ]\033[0m minishell < %s\n", str_cmd);
}

void	test0(void)
{
	printf("\033[035m****************** test0 ******************\033[0m\n");
	cmd("", "echo lol; exit;");
	cmd("", "echo -n end; exit;");
	cmd("", "echo -n \"end\"; exit;");
	cmd("", "echo \"lol\"; exit;");
	cmd("", "echo \"lol\\tlol\"; exit;");
	cmd("", "echo 'lol  \\t lol'; exit;");
	cmd("", "echo \"abc\\tdef\" 'abc\\tdef' abc\\tdef; exit;");
	cmd("", "echo \"abc\\vdef\" 'abc\\vdef' abc\\vdef; exit;");
	cmd("", "echo \"abc\\adef\" 'abc\\adef' abc\\adef; exit;");
	cmd("", "echo \"abc\\rdef\" 'abc\\rdef' abc\\rdef; exit;");
	cmd("", "echo \"abc\\ndef\" 'abc\\ndef' abc\\ndef; exit;");
	cmd("", "echo \"abc\\bdef\" 'abc\\bdef' abc\\bdef; exit;");
	cmd("", "echo \"abc\\fdef\" 'abc\\fdef' abc\\fdef; exit;");
	cmd("", "echo \"abc\\0123def\" 'abc\\0123def' abc\\0123def; exit;");
	cmd("", "echo \"abc\\255def\" 'abc\\255def' abc\\255def; exit;");
	cmd("", "echo \"abc\\040def\" 'abc\\040def' abc\\040def; exit;");
	cmd("", "echo \"abc\\0100def\" 'abc\\0100def' abc\\0100def; exit;");
	cmd("", "echo \"abc\\0def\" 'abc\\0def' abc\\0def; exit;");
	cmd("", "echo -n \"abc\\bdef\" 'abc\\bdef' abc\\bdef; exit;");
	cmd("", "echo -n \"abc\\fdef\" 'abc\\fdef' abc\\fdef; exit;");
	cmd("", "echo -n \"abc\\0123def\" 'abc\\0123def' abc\\0123def; exit;");
	cmd("", "echo \"lol  \t ok\" 'lol  \t ok' lol  \t ok mdr \"  voila ok \""
			"'   hey \t coucou' \" it's not finish éêèë '\"; exit;");
}

void	test1(void)
{
	printf("\033[035m****************** test1 ******************\033[0m\n");
	cmd("", "cd lol; pwd; exit;");
	cmd("", "cd /etc; pwd; exit;");
	cmd("", "cd; pwd; exit;");
	cmd("", "cd .; pwd; exit;");
	cmd("", "cd ..; pwd; exit;");
	cmd("", "cd ../..; pwd; exit;");
	cmd("", "cd $HOME; pwd; exit;");
	cmd("", "cd ../.; pwd; exit;");
	cmd("", "cd /etc/..; pwd; exit;");
	cmd("", "cd $HOME/..; pwd; exit;");
	cmd("", "mkdir tst; cd tst; rm -rf ./tst; pwd; cd ..; pwd; cd; exit;");
	cmd("", "rm -rf ./tst; exit;");
	cmd("", "mkdir tst2; cd tst2; rm -rf tst2; pwd; cd ..; pwd; cd /; rm -rf tst2; exit;");
	cmd("", "rm -rf ./tst2; exit;");
	cmd("", "unsetenv PATH; cd; pwd; cd ../; pwd; exit");
	cmd("", "unsetenv PATH; cd -; exit");
	cmd("", "cd ..; pwd; cd -; pwd; exit");
}

void	test2(void)
{
	printf("\033[035m****************** test2 ******************\033[0m\n");
	cmd("", "env -i env; exit;");
	cmd("", "env -i ls ..; exit;");
	cmd("", "env -i env -i env; exit;");
	cmd("", "env -i cd; exit;");
	cmd("", "env PATH=lol; cd; pwd; exit;");
	cmd("", "env HOME=/; cd; pwd; exit;");
	cmd("", "env -i HOME=/; cd; pwd; exit;");
	cmd("", "env -i PATH=$PATH; ls; exit;");
	cmd("", "env -i SHLVL=$SHLVL env; exit;");
	cmd("", "env -i SHLVL=$SHLVL PATH=lol test=oui test=lol; exit;");
}

void	test3(void)
{
	printf("\033[035m****************** test3 ******************\033[0m\n");
	cmd("", "setenv env env; env; exit;");
	cmd("", "setenv lol lol; setenv lol mdr; env; exit;");
	cmd("", "setenv $PATH $PATH; env; exit;");
	cmd("", "setenv PATH $PATH; env; exit;");
	cmd("", "setenv SHLVL $SHLVL; env; exit;");
	cmd("", "setenv SHLVL $SHLVL; setenv SHLVL $OLDPWD; env; exit;");
	cmd("", "env -i setenv SHLVL $SHLVL; setenv SHLVL $PWD; env; exit;");
}

void	test4(void)
{
	printf("\033[035m****************** test4 ******************\033[0m\n");
	cmd("", "unsetenv env env; env; exit;");
	cmd("", "unsetenv env -i; env; exit;");
	cmd("", "unsetenv PATH; env; exit;");
	cmd("", "unsetenv PATH SHLVL; env; exit;");
	cmd("", "env -i unsetenv PATH SHLVL; env; exit;");
}

void	test5(void)
{
	printf("\033[035m****************** test5 ******************\033[0m\n");
	cmd("", "mkdir tst3; chmod 000 tst3; cd tst3; exit;");
	cmd("", "unsetenv HOME; cd; exit;");
	cmd("", "unsetenv HOME; setenv HOME $HOME; echo $HOME; exit;");
}

int		main(void)
{
	system("make -C ../");
	test0();
	test1();
	test2();
	test3();
	test4();
	test5();
	return (0);
}