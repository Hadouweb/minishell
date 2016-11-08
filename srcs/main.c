/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 11:58:37 by nle-bret          #+#    #+#             */
/*   Updated: 2016/11/04 11:58:38 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_pid = 0;

int		m_read_cmd(char **cmd)
{
	int		ret;
	char	buf[11];
	int		token_break;

	token_break = 0;
	while ((ret = read(0, &buf, 10)) != -1)
	{
		buf[ret] = '\0';
		if (buf[ret - 1] == '\n')
		{
			buf[ret - 1] = '\0';
			token_break = 1;
		}
		*cmd = ft_strjoin_free_s1(*cmd, buf);
		if (token_break)
			break ;
	}
	return (ret);
}

void	m_separate_cmd(t_app *app, char **cmd)
{
	t_list	*l;

	if (*cmd && ft_strlen(*cmd) > 0)
	{
		app->lst_cmd = ft_lstsplit(*cmd, ';');
		ft_strdel(&(*cmd));
		l = app->lst_cmd;
		while (l)
		{
			if (app->env == NULL)
				m_set_env_from_lst(app, &app->lst_env);
			m_run_cmd(app, (char **) &l->content);
			l = l->next;
		}
		m_free_char_lst(&app->lst_cmd);
	}
}

void	m_signal_handler(int val)
{
	if (val)
		;
	if (g_pid == 0)
		ft_putstr("\n$> ");
	else
		ft_putchar('\n');
}

int		main(int ac, char **av, char **envp)
{
	t_app	app;
	char	*cmd;

	if (av && ac)
		;
	ft_bzero(&app, sizeof(t_app));
	m_set_envp(&app, envp);
	m_set_shlvl(&app);
	signal(SIGINT, m_signal_handler);
	while (1)
	{
		cmd = ft_strdup("");
		ft_putstr("$> ");
		m_read_cmd(&cmd);
		m_separate_cmd(&app, &cmd);
	}
	m_free_all(&app);
	return (0);
}
