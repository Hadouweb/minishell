#include "minishell.h"

int 	m_word_size_cmd(char *cmd)
{
	int 	i;
	int 	token;

	token = 0;
	i = 0;
	while (cmd[i])
	{
		if (token == 2)
			return (i);
		if ((cmd[i] == ' ' || cmd[i] == '\t') && token == 0)
			return (i);
		if (cmd[i] == '"' && !(cmd[i - 1] && cmd[i - 1] == '\\'))
			token++;
		i++;
	}
	return i;
}

void	m_set_escaped_character(char *new_str, char *str, int *i, int max)
{
	printf("%s\n", str);
	if (*i < max && str[1])
	{
		printf("%c %c\n", str[0], str[1]);
		if (str[1] == '\\') {
			new_str[0] = '\\';
			(*i)++;
		} else if (str[1] == '"') {
			new_str[0] = '"';
			(*i)++;
		}
	}
}

char	*m_format_param(char *str, int max)
{
	int 	i;
	int 	j;
	char 	*new_str;

	printf("%d %s\n", max, str);

	i = 0;
	j = 0;
	new_str = ft_strnew(max);
	while(str[i] && i < max)
	{
		printf("a [%c] %d\n", str[i], i);
		if (str[i] == '\\') {
			m_set_escaped_character(&new_str[j], &str[i], &i, max);
			j++;
		}
		else {
			new_str[j] = str[i];
			j++;
		}
		printf("b [%c] %d\n", str[i], i);
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	m_set_cmd(t_app *app, char *cmd)
{
	char 	*cmd_inc;
	int 	inc;
	char 	*word;
	int 	i;

	cmd_inc = cmd;
	i = 0;
	word = NULL;
	while (cmd_inc[i])
	{
		while (cmd_inc[i] == ' ' || cmd_inc[i] == '\t')
			i++;
		inc = m_word_size_cmd(&cmd_inc[i]);
		if (inc > 0)
			word = m_format_param(&cmd_inc[i], inc);
		i += inc;
		if (word != NULL)
		{
			ft_lstpush_back(&app->param, word, ft_strlen(word));
			ft_strdel(&word);
		}
	}
	ft_lstprint(app->param, NULL);
}