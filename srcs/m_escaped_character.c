/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_escaped_character.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 07:15:48 by nle-bret          #+#    #+#             */
/*   Updated: 2016/11/04 07:15:53 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		m_word_size_cmd(char *cmd)
{
	int		i;
	int		token;
	int		token2;

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
	return (i);
}

int		m_set_escaped_character2(char *new_str, char *str)
{
	int		i;

	i = 0;
	if (str[1] == 'n' && (i += 2))
		new_str[0] = '\n';
	else if (str[1] == 'v' && (i += 2))
		new_str[0] = '\v';
	else if (str[1] == 'a' && (i += 2))
		new_str[0] = '\a';
	else if (str[1] == 'b' && (i += 2))
		new_str[0] = '\b';
	else if (str[1] == 'r' && (i += 2))
		new_str[0] = '\r';
	else if (str[1] == 'f' && (i += 2))
		new_str[0] = '\f';
	else if (str[1] == 't' && (i += 2))
		new_str[0] = '\t';
	return (i);
}

int		m_set_escaped_character(char *new_str, char *str, int mode)
{
	int		i;

	i = 0;
	if (str[1])
	{
		if (str[1] == '\\' && (i += 2))
			new_str[0] = '\\';
		else if (str[1] == '"' && mode == 1 && ++i)
			new_str[0] = '"';
		else if (str[1] == '\'' && mode == 2 && ++i)
			new_str[0] = '\'';
		else
			i += m_set_escaped_character2(new_str, str);
	}
	return (i);
}

char	*m_format_param(char *str, char *new_str, int max, int mode)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (str[i] && i < max)
	{
		if (str[i] == '\\' && (i + 1) < max && mode != 2)
		{
			if (mode == 0 && str[i + 1] != '\\')
				i++;
			else
			{
				k = m_set_escaped_character(&new_str[j], &str[i], mode);
				j += (k > 0) ? k : 0;
				i += k;
			}
		}
		if ((str[i] == '"' && mode != 1) || (str[i] == '\'' && mode != 2) ||
			mode == 0 || (str[i] != '"' && str[i] != '\''))
			new_str[j++] = str[i];
		i++;
	}
	return (new_str);
}

char	*m_format_init_param(char *str, int max)
{
	int		mode;
	char	*new_str;
	int		last_char;

	mode = 0;
	if (str[0] == '"')
		mode = 1;
	if (str[0] == '\'')
		mode = 2;
	new_str = ft_strnew(max);
	last_char = ft_strlen(new_str) - 1;
	if (last_char < 0)
		last_char = 0;
	new_str[last_char] = '\0';
	return (m_format_param(str, new_str, max, mode));
}

void	m_set_cmd(t_app *app, char *cmd)
{
	char	*cmd_inc;
	int		inc;
	char	*word;
	int		i;

	cmd_inc = cmd;
	i = 0;
	word = NULL;
	while (cmd_inc[i])
	{
		while (cmd_inc[i] == ' ' || cmd_inc[i] == '\t')
			i++;
		inc = m_word_size_cmd(&cmd_inc[i]);
		if (inc > 0)
			word = m_format_init_param(&cmd_inc[i], inc);
		i += inc;
		if (word != NULL && ft_strlen(word) > 0)
			ft_lstpush_back(&app->param, (void*)word, ft_strlen(word) + 1);
		ft_strdel(&word);
	}
}
