#include "minishell.h"

char 	*m_get_builtin(char *cmd)
{
	int 	i;
	int 	j;
	int 	token;
	int 	token2;
	char 	*builtin;

	i = 0;
	j = 0;
	token = 0;
	token2 = 0;
	builtin = ft_strnew(ft_strlen(cmd));
	while (cmd[i])
	{
		if (token == 2 || token2 == 2)
			;
		if (cmd[i] == '"')
			token++;
		else if (cmd[i] == '\'')
			token2++;
		else {
			builtin[j] = cmd[i];
			j++;
		}
		i++;
	}
	builtin[j] = '\0';
	if (builtin == NULL || ft_strlen(builtin) == 0)
		return (NULL);
	return (builtin);
}

int		m_check_builtin(t_app *app, char *cmd)
{
	int		ret;
	char 	*builtin;

	ret = 0;

	builtin = m_get_builtin(cmd);

	int i = 0;
	while (builtin[i])
	{
		printf("|%c| ", builtin[i]);
		i++;
	}
	printf("\n");
	printf("[%s] %d\n", builtin, ft_strcmp(cmd, "exit"));
	if (ft_strcmp(cmd, "exit") == 0 && (ret = 1))
	{
		m_free_all(app);
		exit(0);
	}
	return (ret);
}