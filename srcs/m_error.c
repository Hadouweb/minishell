#include "minishell.h"

void	m_error_malloc(char *str)
{
	if (str != NULL)
		ft_putendl_fd(str, 2);
	else
		ft_putendl_fd("Error malloc", 2);
	exit(1);
}