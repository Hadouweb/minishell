#include "minishell.h"

int 	m_word_size_cmd(char *cmd)
{
	int 	i;
	int 	token;

	token = 0;
	i = 0;
	while (cmd[i])
	{
		if ((cmd[i] == ' ' || cmd[i] == '\t') && token == 0)
			return (i);
		if (cmd[i] == '"')
			token++;
		if (token == 2)
			return (i + 1);
		i++;
	}
	return i;
}

void	m_set_cmd(t_app *app, char *cmd)
{
	char 	*cmd_inc;
	int 	inc;
	char 	*word;
	int 	i;

	inc = 0;
	cmd_inc = cmd;
	i = 0;
	word = NULL;
	while (cmd_inc[i])
	{
		while (cmd_inc[i] == ' ' || cmd_inc[i] == '\t')
			i++;
		inc += i;
		inc = m_word_size_cmd(&cmd_inc[inc]);
		if (inc > 0)
			word = ft_strndup(cmd_inc, inc);
		i += inc;
		printf("%d %d %s\n", i, inc, word);
		if (word != NULL)
		{
			ft_lstpush_back(&app->param, word, ft_strlen(word));
			ft_strdel(&word);
		}
	}
	ft_lstprint(app->param, NULL);
}