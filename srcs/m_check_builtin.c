/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_check_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 10:09:36 by nle-bret          #+#    #+#             */
/*   Updated: 2016/11/07 10:09:39 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*m_get_builtin(char *cmd, int *i)
{
	int		j;
	int		token;
	int		token2;
	char	*builtin;

	j = 0;
	token = 0;
	token2 = 0;
	builtin = ft_strnew(ft_strlen(cmd));
	while (cmd[*i])
	{
		if (token != 1 && token2 != 1 && cmd[*i] == ' ')
			break ;
		if (cmd[*i] == '"' && token2 != 1)
			token++;
		else if (cmd[*i] == '\'' && token != 1)
			token2++;
		else
			builtin[j++] = cmd[*i];
		(*i)++;
	}
	builtin[j] = '\0';
	if (builtin != NULL && (ft_strlen(builtin) == 0))
		ft_strdel(&builtin);
	return (builtin);
}

int		m_check_builtin2(t_app *app, char *cmd, char *builtin)
{
	int		ret;

	ret = 0;
	if (ft_strcmp(builtin, "echo") == 0 && (ret = 1))
		m_run_echo(app, cmd);
	else if (ft_strcmp(builtin, "env") == 0 && (ret = 1))
		m_run_env(app, cmd);
	else if (ft_strcmp(builtin, "setenv") == 0 && (ret = 1))
		m_run_setenv(app, cmd);
	else if (ft_strcmp(builtin, "unsetenv") == 0 && (ret = 1))
		m_run_unsetenv(app, cmd);
	else if (ft_strcmp(builtin, "cd") == 0 && (ret = 1))
		m_run_cd(app, cmd);
	return (ret);
}

int		m_check_builtin(t_app *app, char *cmd)
{
	int		ret;
	char	*builtin;
	int		i;

	i = 0;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		i++;
	builtin = m_get_builtin(cmd, &i);
	if (builtin == NULL)
		return (-1);
	if (ft_strcmp(builtin, "exit") == 0)
	{
		m_free_all(app);
		ft_strdel(&builtin);
		m_free_char_lst(&app->lst_cmd);
		exit(0);
	}
	else
		ret = m_check_builtin2(app, cmd, builtin);
	ft_strdel(&builtin);
	return (ret);
}
