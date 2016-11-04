#include "minishell.h"

int 	m_word_size_cmd(char *cmd)
{
	int 	i;
	int 	token;
	int 	token2;

	token = 0;
	token2 = 0;
	i = 0;
	while (cmd[i])
	{
		if (token == 2 || token2 == 2)
			return (i);
		if ((cmd[i] == ' ' || cmd[i] == '\t') && token == 0 && token2 == 0)
			return (i);
		if (cmd[i] == '"' && !(i - 1 > 0 && cmd[i - 1] && cmd[i - 1] == '\\'))
			token++;
		if (cmd[i] == '\'' && !(i - 1 > 0 && cmd[i - 1] && cmd[i - 1] == '\\'))
			token2++;
		i++;
	}
	return i;
}

int		m_set_escaped_character(char *new_str, char *str, int mode)
{
	int	i;
	//printf("%s\n", str);
	i = 0;
	if (str[1])
	{
		//printf("%c %c\n", str[0], str[1]);
		if (str[1] == '\\') {
			new_str[0] = '\\';
			i += 2;
		}
		else if (str[1] == '"' && mode == 1) {
			new_str[0] = '"';
			i++;
		}
		else if (str[1] == '\'' && mode == 2) {
			new_str[0] = '\'';
			i++;
		}
		else if (str[1] == 'n') {
			new_str[0] = '\n';
			i += 2;
		}
		else if (str[1] == 'v') {
			new_str[0] = '\v';
			i += 2;
		}
		else if (str[1] == 'a') {
			new_str[0] = '\a';
			i += 2;
		}
		else if (str[1] == 'b') {
			new_str[0] = '\b';
			i += 2;
		}
		else if (str[1] == 'r') {
			new_str[0] = '\r';
			i += 2;
		}
		else if (str[1] == 'f') {
			new_str[0] = '\f';
			i += 2;
		}
		else if (str[1] == 't') {
			new_str[0] = '\t';
			i += 2;
		}
	}
	return (i);
}

char	*m_format_param(char *str, int max)
{
	int 	i;
	int 	j;
	char 	*new_str;
	int 	mode;
	int 	k;

	printf("%s\n", str);

	i = 0;
	j = 0;
	new_str = ft_strnew(max);
	mode = 0;
	if (str[0] == '"')
		mode = 1;
	if (str[0] == '\'')
		mode = 2;
	while(str[i] && i < max)
	{
		//printf("a [%c] %d\n", str[i], i);
		if (str[i] == '\\' && (i + 1) < max && mode != 2) {
			if (mode == 0 && str[i + 1] != '\\')
				i++;
			else {
				k = m_set_escaped_character(&new_str[j], &str[i], mode);
				printf("%d\n", i);
				if (k > 0)
					j++;
				i += k;
			}
		}
		if (
			(str[i] == '"' && mode != 1) ||
			(str[i] == '\'' && mode != 2) ||
			mode == 0 ||
			(str[i] != '"' && str[i] != '\''))
		{
			new_str[j] = str[i];
			j++;
		}
		//printf("b [%c] %d\n", str[i], i);
		i++;
	}
	new_str[j] = '\0';
	if (ft_strlen(new_str) == 0)
		ft_strdel(&new_str);
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
			ft_lstpush_back(&app->param, (void*)word, ft_strlen(word) + 1);
			ft_strdel(&word);
		}
	}
	ft_lstprint(app->param, NULL);
}