/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 11:52:05 by nle-bret          #+#    #+#             */
/*   Updated: 2016/11/04 11:52:10 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_error_malloc(char *str)
{
	if (str != NULL)
		ft_putendl_fd(str, 2);
	else
		ft_putendl_fd("Error malloc", 2);
	exit(1);
}

void	m_error(char *str, char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	if (file != NULL)
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(file, 2);
	}
	ft_putstr_fd("\n", 2);
}

void	m_error2(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

void	m_error3(char *str1, char *str2, char *str3)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str1, 2);
	if (str2 != NULL)
	{
		ft_putstr_fd(str2, 2);
		if (str3 != NULL)
			ft_putstr_fd(str3, 2);
	}
	ft_putstr_fd("\n", 2);
}

void	m_error_access(char *cmd, int code)
{
	if (code == -1)
		m_error("permission denied: ", cmd);
	else
		m_error("command not found:", cmd);
}
