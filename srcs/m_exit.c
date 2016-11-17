/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 13:57:40 by nle-bret          #+#    #+#             */
/*   Updated: 2016/11/17 13:57:42 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	m_special_exit(t_app *app, char *nb, char *builtin)
{
	int	intnb;

	intnb = 0;
	if (nb)
	{
		intnb = ft_atoi(nb);
		if (intnb > 255)
			intnb = 0;
	}
	m_free_all(app);
	ft_strdel(&builtin);
	m_free_char_lst(&app->lst_cmd);
	exit(intnb);
}

void		m_run_exit(t_app *app, char *cmd, char *builtin)
{
	m_split_cmd_echo(app, cmd);
	if (ft_lstsize(app->param) == 2)
		m_special_exit(app, app->param->next->content, builtin);
	else if (ft_lstsize(app->param) == 1)
	{
		m_free_all(app);
		ft_strdel(&builtin);
		m_free_char_lst(&app->lst_cmd);
		exit(0);
	}
	else
	{
		ft_putstr_fd("exit: Expression Syntax.\n", 2);
		m_free_char_lst(&app->param);
		return ;
	}
}
