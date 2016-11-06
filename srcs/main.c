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

int		main(int ac, char **av, char **envp)
{
	t_app	app;
	char	*cmd;

	if (av && ac)
		;
	ft_bzero(&app, sizeof(t_app));
	m_set_envp(&app, envp);
	m_set_env_from_lst(&app);
	while (1)
	{
		cmd = ft_strdup("");
		ft_putstr("$> ");
		m_read_cmd(&cmd);
		m_run_cmd(&app, cmd);
		ft_strdel(&cmd);
	}
	m_free_all(&app);
	return (0);
}
