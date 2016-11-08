#include "minishell.h"

void	m_debug_content_env(void *content)
{
	t_env	*env;
	t_list	*l;

	env = (t_env*)content;
	l = env->lst_value;
	ft_putstr(env->key);
	ft_putchar(' ');
	ft_putstr(env->value);
	if (l)
		ft_putchar('\n');
	while (l)
	{
		ft_putchar('\t');
		ft_putendl((char*)l->content);
		l = l->next;
	}
}

void	m_debug_env(char **env)
{
	int 	i;

	i = 0;
	if (env == NULL)
		return ;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}