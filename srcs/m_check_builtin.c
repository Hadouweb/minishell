#include "minishell.h"

char 	*m_get_builtin(char *cmd, int *i)
{
	int 	j;
	int 	token;
	int 	token2;
	char 	*builtin;

	j = 0;
	token = 0;
	token2 = 0;
	builtin = ft_strnew(ft_strlen(cmd));
	while (cmd[*i] == ' ' || cmd[*i] == '\t')
		(*i)++;
	while (cmd[*i])
	{
		if (token != 1 && token2 != 1 && cmd[*i] == ' ')
			break ;
		if (cmd[*i] == '"' && token2 != 1)
			token++;
		else if (cmd[*i] == '\'' && token != 1)
			token2++;
		else {
			builtin[j] = cmd[*i];
			j++;
		}
		(*i)++;
	}
	builtin[j] = '\0';
	if (builtin != NULL && (ft_strlen(builtin) == 0))
		ft_strdel(&builtin);
	return (builtin);
}

int		m_check_builtin(t_app *app, char *cmd)
{
	int		ret;
	char 	*builtin;
	//char 	*param;
	int 	i;

	ret = 0;
	i = 0;
	builtin = m_get_builtin(cmd, &i);
	//param = ft_strdup((cmd - builtin));
	//printf("[%s]\n", builtin);
	if (builtin == NULL)
		return (-1);
	if (ft_strcmp(builtin, "exit") == 0 && (ret = 1))
	{
		m_free_all(app);
		ft_strdel(&cmd);
		ft_strdel(&builtin);
		exit(0);
	}
	else if (ft_strcmp(builtin, "echo\0") == 0 && (ret = 1))
	{
		m_run_echo(app, cmd);
	}
	ft_strdel(&builtin);
	return (ret);
}