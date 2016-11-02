#include "minishell.h"

t_env	m_get_env_struct(char *env)
{
	t_env	tenv;
	char 	**split;

	split = ft_strsplit(env, '=');
	tenv.key = ft_strdup(split[0]);
	tenv.value = ft_strdup(split[1]);
	ft_free_tab(split);
	tenv.lst_value = NULL;
	//if (ft_strcmp(tenv.key, "PATH") == 0)
	//	tenv.lst_value = ft_lstsplit(tenv.value, ':');
	return (tenv);
}

void	m_set_envp(t_app *app, char **envp)
{
	int 	i;
	t_env	env;

	i = 0;
	while (envp[i] != NULL)
	{
		env = m_get_env_struct(envp[i]);
		ft_lstpush_back(&app->lst_env, (void*)&env, sizeof(t_env));
		i++;
	}

	ft_lstprint(app->lst_env, m_debug_content_env);
}