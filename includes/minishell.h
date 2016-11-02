#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include "libft.h"

typedef	struct 		s_env
{
	char 			*key;
	char 			*value;
	t_list			*lst_value;
}					t_env;

typedef struct		s_app
{
	t_list			*lst_env;
}					t_app;

void	m_set_envp(t_app *app, char **envp);
void	m_debug_content_env(void *content);
void	m_free_lst_envp(t_app *app);

#endif
