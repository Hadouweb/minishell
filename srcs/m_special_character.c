/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_special_character.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 22:32:42 by nle-bret          #+#    #+#             */
/*   Updated: 2016/11/08 22:32:43 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		m_set_special_character2(char *new_str, char *str)
{
	int		i;

	i = 0;
	if (str[1] == 'r' && (i = 2))
		new_str[0] = '\r';
	else if (str[1] == 'f' && (i = 2))
		new_str[0] = '\f';
	else if (str[1] == 't' && (i = 2))
		new_str[0] = '\t';
	else if (str[1] == 'c' && (i = 1))
		new_str[0] = '\0';
	else if (str[1] == '0' && (i = 5))
		new_str[0] = m_set_octacl_special_char(&str[1]);
	return (i);
}

int		m_set_special_character(char *new_str, char *str)
{
	int		i;

	i = 0;
	if (str[1])
	{
		if (str[1] == '\\' && (i = 2))
			new_str[0] = '\\';
		else if (str[1] == 'n' && (i = 2))
			new_str[0] = '\n';
		else if (str[1] == 'v' && (i = 2))
			new_str[0] = '\v';
		else if (str[1] == 'a' && (i = 2))
			new_str[0] = '\a';
		else if (str[1] == 'b' && (i = 2))
			new_str[0] = '\b';
		else
			i = m_set_special_character2(new_str, str);
	}
	return (i);
}
