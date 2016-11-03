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

void	m_error_access(char *cmd, int code)
{
	if (code == -1)
		m_error("permission denied: ", cmd);
	else
		m_error("command not found:", cmd);
}